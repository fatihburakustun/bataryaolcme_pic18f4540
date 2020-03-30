

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RB1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

#define   TRIS_seg1   TRISC.RC0
#define   TRIS_seg2   TRISC.RC1
#define   TRIS_seg3   TRISC.RC2
#define   TRIS_seg4   TRISC.RC4
#define   TRIS_led1  TRISA.RB2
#define   TRIS_led2  TRISA.RB5
#define   TRIS_led3  TRISA.RB0
#define   TRIS_led4  TRISA.RB1
#define   TRIS_led5  TRISA.RB4
#define   TRIS_PORTB      TRISB

#define  TRIS_adcpin      TRISA.RA0
#define  adcpin          PORTA.RA0
#define  TRIS_dot      TRISB.RB7
#define  dot          PORTB.RB7

#define seg1 PORTC.RC0
#define seg2 PORTC.RC1
#define seg3 PORTC.RC2
#define seg4 PORTC.RC4
#define led1  PORTA.RB2
#define led2  PORTA.RB5
#define led3  PORTA.RB0
#define led4  PORTA.RB1
#define led5  PORTA.RB4

/*void delay(unsigned long Delay)
{
    int i,j;
    for(i=0;i<Delay;i++)
        for(j=0;j<1000;j++);
}
  */
void  adc_init();
float  adc_value(void);
void convert(float);

unsigned int counter2;
unsigned char position = 0;
unsigned char k[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int digit1=0,digit2=0,digit3=0,digit4=0;

/*************************************timer0*******************************************/

void interrupt (void)
{
if(TMR0IF_bit == 1)
{
   counter2++;
   if(counter2>=1)
   {

   if(position ==0)
    {
    seg1=0;
    seg2=1;
    seg3=1;
    seg4=1;
    }
    if(position ==1)
    {
    seg1=1;
    seg2=0;
    seg3=1;
    seg4=1;
    }
    if(position==2)
    {
     dot=0;
    seg1=1;
    seg2=1;
    seg3=0;
    seg4=1;
    }
 if(position==3)
    {
    seg1=1;
    seg2=1;
    seg3=1;
    seg4=0;
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
ADCON1  = 0b00001111;      //all port is digital
 INTCON=0b11101000;
 INTCON2=0b00000000;              //GLOBLE INTRRUPT ENABLE
               //peripheral intrupt flag
T0CON  = 0b100000000;      //prescaler value put
                //interrupt enable                   //interrupt priority
TMR0   = 55536;            //start counter after this value

    ADCON1 = 0b00001110;     //select analog and digital i/p
    ADCON2 = 0b10001010;     //eqisation time holding cap time


TRIS_seg1   =0;
TRIS_seg2   =0;
TRIS_seg3   =0;
TRIS_seg4   =0;
TRIS_led1   = 0;
TRIS_led2   = 0;
TRIS_led3   =0;
TRIS_led4   =0;
TRIS_led5   =0;
TRIS_PORTB    = 0;
TRIS_adcpin    = 1;
TRIS_dot    = 0;
while(1)
{
     ADCON0 = 0b00000011;     //select adc channel
    ADCON1 = 0b00001110;     //select analog and digital i/p
    ADCON2 = 0b10001010;     //eqisation time holding cap time
    
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
while(GO/DONE==1);                   //higher bit data start conversion adc value
adc_data = (ADRESL)+(ADRESH<<8);     //Store 10-bit output
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