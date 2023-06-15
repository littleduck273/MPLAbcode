// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#define _XTAL_FREQ 20000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
 unsigned char LED[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
 unsigned char counter=0;
 int state = 0;
 int state1 = 0;
int buttonState = 0; 
int nghin,tram,chuc,dv;
int arr[10] = { 1, 2, 3 ,4};
 static int x = 0 ;
 int giam;
 int demtime;
 int lasttime;
 int number = 0;
 int time = 0;
 void Tinh(int x)
{   nghin=x/1000;
    tram=(x%1000)/100;
    chuc=((x%1000)%100)/10;
    dv =((x%1000)%100)%10;
}
 
 
void setup(){
  TRISB= 0; // 
//  PORTA = 0;
  TRISD0 = 0; 
  TRISD1 = 0; 
  TRISD2 = 0; 
  TRISD3 = 0; 
  //TRISB= 0xff ; // INput 
  WPUB=0XFF;
  }


void segment(){
    if ( time < 500){
        time++;
    }
    else {
        number++;
        if ( number > 5){
            number = 1;
        }
    }
    switch(number){ 
        case 1:
    RD0 = 0;
    RD1 = RD2 =RD3 =1;
    PORTB = LED[nghin];
    break;
        case 2:
    RD1 = 0;
    RD0 = RD2 =RD3 =1;
    PORTB = LED[tram];
    break;
         case 3 :
    RD2 = 0;
    PORTB = LED[chuc];
    RD0 = RD1 =RD3 =1;
    break;
         case 4 :
    RD3 = 0;
    PORTB = LED[dv];
    RD0 = RD1 =RD2 =1;
    break;
        case 5: 
    RD0 = 1;
    RD1 = RD2 =RD3 =1;
    PORTB = LED[nghin];
    break;
}  
    
}


void main (void) {
     setup();
//     nghin = arr[0];
//     tram = arr[1];
//     chuc = arr[2];
//     dv = arr[3];
     ANSEL=ANSELH=0x00;
       nRBPU=0;
       WPUB=0XFF;
    while (1){
//      if(RB1==0&&state1 == 0)
//    {  state1=1;
//          x++;  
//          demtime++;
//          if ( demtime > 500 ){
//        
//             x++;
//            }
//             }
//     
//    
//      
//    if(RB1==1)
//    {
//         state1=0;
//         demtime = 0;
//    }
//      
//       giam = x;
//       if(RB2==0&&state==0)
//    {   state=1;
//          giam--;
//          x=giam;
//    }
//    if(RB2==1)
//    {
//         state=0;  
//    }
      
    if ( x > 9999)
    {
       x =0;
                }
        if ( x <0 )
    {
       x = 9999;
                }
       Tinh(6789);
       segment();

  }
}
