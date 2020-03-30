#line 1 "C:/Users/FatihBurak/Desktop/fatihburak/fatihburak/batarya/batarya/batarya .c"
#pragma config OSC = HS
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = ON
#pragma config BOREN = SBORDIS
#pragma config BORV = 3
#pragma config WDT = OFF
#pragma config WDTPS = 32768
#pragma config CCP2MX = PORTC
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = ON
#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config XINST = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTC = OFF
#pragma config WRTB = OFF
#pragma config WRTD = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
#line 91 "C:/Users/FatihBurak/Desktop/fatihburak/fatihburak/batarya/batarya/batarya .c"
void adc_init();
float adc_value(void);
void convert(float);

unsigned int counter2;
unsigned char position = 0;
unsigned char k[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int digit1=0,digit2=0,digit3=0,digit4=0;



void interrupt (void)
{
if(TMR0IF_bit == 1)
{
 counter2++;
 if(counter2>=1)
 {

 if(position ==0)
 {
  PORTC.RC0 =0;
  PORTC.RC1 =1;
  PORTC.RC2 =1;
  PORTC.RC4 =1;
 }
 if(position ==1)
 {
  PORTC.RC0 =1;
  PORTC.RC1 =0;
  PORTC.RC2 =1;
  PORTC.RC4 =1;
 }
 if(position==2)
 {
  PORTB.RB7 =0;
  PORTC.RC0 =1;
  PORTC.RC1 =1;
  PORTC.RC2 =0;
  PORTC.RC4 =1;
 }
 if(position==3)
 {
  PORTC.RC0 =1;
  PORTC.RC1 =1;
  PORTC.RC2 =1;
  PORTC.RC4 =0;
 }
 if(position == 0)
 PORTB = k[digit1];
 if(position == 1)
 PORTB = k[digit2];
 if(position == 2)
 {
 PORTB = k[digit3];
 PORTB&=~(0x80);
 }
 if(position == 3)
 PORTB = k[digit4];
 position++;
 if(position>=4)
 position = 0;
 counter2 =0;
 }
 TMR0=55536;
 TMR0IF_bit=0;
}
}


void main()
{
 float adcValue=0;
 float Value[40];
 int i=0;
ADCON1 = 0b00001111;
 INTCON=0b11101000;
 INTCON2=0b00000000;

T0CON = 0b100000000;

TMR0 = 55536;

 ADCON1 = 0b00001110;
 ADCON2 = 0b10001010;


 TRISC.RC0  =0;
 TRISC.RC1  =0;
 TRISC.RC2  =0;
 TRISC.RC4  =0;
 TRISA.RB2  = 0;
 TRISA.RB5  = 0;
 TRISA.RB0  =0;
 TRISA.RB1  =0;
 TRISA.RB4  =0;
 TRISB  = 0;
 TRISA.RA0  = 1;
 TRISB.RB7  = 0;
while(1)
{
 ADCON0 = 0b00000011;
 ADCON1 = 0b00001110;
 ADCON2 = 0b10001010;

 for(i=0;i<40;i++)
 {
 Value[i]=adc_value();
 adcValue+=Value[i];
 }
 adcValue=(float)adcValue/40.0;
 convert(adcValue);
 delay_ms(100);
}
}

float adc_value(void)
{
float adc_data=0;
while(GO/DONE==1);
adc_data = (ADRESL)+(ADRESH<<8);
adc_data =((adc_data/342.0)*5.0);
return adc_data;
}

 void convert(float f)
 {
 int d=(f*100);
 digit1=d%10;
 d=d/10;
 digit2=d%10;
 d=d/10;
 digit3=d%10;
 digit4=d/10;
 }
