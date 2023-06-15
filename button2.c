#define _XTAL_FREQ 20000000

#include <xc.h>

// CONFIG
#pragma config FOSC = EC        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF       // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

int state = 1;
unsigned char dem = 0;
unsigned char a;

void setup(){
    TRISC = 0; // OUTPUT
    TRISB= 0xff ; // INput   
    PORTC=0x01;
    WPUB=0XFF;
      
}
void led(){

    if(RB1==0&&state==0)
    { 
             dem++;
        state=1;
//             PORTC=0xaa;
     
    }
    if(RB1==1)
    {
         state=0;
//            PORTC=0xFF;
   
        
    }
    if ( dem >7){
        dem = 1;
    }
    if ( dem <= 7 ) {
        
   a = 0x01 << dem;
     a = ~a;
     PORTC=a;
    }
}
void main(void)
{
 
   
     setup();
    ANSEL=ANSELH=0x00;
       nRBPU=0;
       WPUB=0XFF;
    TRISD= 0;
    PORTD= 0xff;    
        while(1){
       
        led();
    }
}