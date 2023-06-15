
// CONFIG1
#define _XTAL_FREQ 8000000
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
#include<stdint.h>
// unsigned char Buffer_display[8] = { 0xFF,0xFF,0xFF,0xFF};
unsigned char matrix[8] = {0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00};
unsigned char matrix_2[8]={0x18, 0x3C, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66};
unsigned char matrix_display[8] = {0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00};
//{0X66,0X66,0X66,0X66,0X66,0X66,0X3C,0X18}  

//unsigned char matrix[]= {0X66,0X66,0X66,0X66,0X66,0X66,0X3C,0X18};
//unsigned char matrix[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// unsigned char matrix[]= {0XFF,0X01,0X00,0XFC,0XFC,0X00,0X01,0XFF };
int time = 0;
int number = -1;
int n = 2;
uint8_t show;
uint8_t display;
uint8_t data;
int i,j;
 uint8_t data_in[8];
 uint8_t data_out[8];
 int time_tick;
 int time_tick_2;
void setup() {
    TRISC = 0; // e
    //  PORTC = 0;
    PORTC = 0xff;
    TRISD0 = 0;
    TRISD1 = 0;
    TRISD2 = 0;
    TRISD3 = 0;
    TRISD4 = 0;
    TRISD5 = 0;
    TRISD6 = 0;
    TRISD7 = 0;

}

void led_matrix() {
    if (time < 20) {
        time++;
    } else {
        number++;
        time = 0;
    }
    if (number > 8) {
        number = 0;
    }
    switch (number) {
        case 0:
            PORTC = 0x00;
            RD0 = 0;
            RD1 = RD2 = RD3 = RD4 = RD5 = RD6 = RD7 = 1;
    
    PORTC = matrix[number];
    break;
    case 1:
    PORTC = 0x00;
    RD1 = 0;
    RD0 = RD2 = RD3 = RD4 = RD5 = RD6 = RD7 = 1;
    PORTC = matrix[number];
    //          
    break;

    case 2:
    PORTC = 0x00;
    RD2 = 0;
    RD0 = RD1 = RD3 = RD4 = RD5 = RD6 = RD7 = 1;
    PORTC = matrix[number];
    break;
    case 3:
    PORTC = 0x00;
    RD3 = 0;
    RD0 = RD1 = RD2 = RD4 = RD5 = RD6 = RD7 = 1;
    PORTC = matrix[number];

    break;
    case 4:
    PORTC = 0x00;
    RD4 = 0;
    RD0 = RD1 = RD2 = RD3 = RD5 = RD6 = RD7 = 1;
    PORTC = matrix[number];
    break;
    case 5:
    PORTC = 0x00;
    RD5 = 0;
    RD0 = RD1 = RD2 = RD3 = RD4 = RD6 = RD7 = 1;
    PORTC = matrix[number];
    break;
    case 6:
    PORTC = 0x00;
    RD6 = 0;
    RD0 = RD1 = RD2 = RD3 = RD4 = RD5 = RD7 = 1;
    PORTC = matrix[number];

    break;
    case 7:
    PORTC = 0x00;
    RD7 = 0;
    RD0 = RD1 = RD2 = RD3 = RD4 = RD5 = RD6 = 1;
    PORTC = matrix[number];
    break;
    case 8:
    PORTC = 0x00;
    //RD7 =0;
    RD0 = RD1 = RD2 = RD3 = RD4 = RD5 = RD6 = RD7 = 1;
    PORTC = matrix[number];
    break;
}
}

void dichChu(uint8_t data_in[8], uint8_t data_out[8]) {
    int i;
    for (i = 0; i < 8; i++) {
        
        data_out[i] = data_out[i] >> 1;
        show = 0x01 & (data_in[i] >> i);
        data_out[i] |= (show << 7);
        matrix[i] = data_out[i];
        // __delay_ms(200);
        // PORTC = display;
    }
}



void main() {
    ANSEL = ANSELH = 0x00;
    nRBPU = 0;
    WPUB = 0XFF;
    setup();
    while (1) {
//        
     //                time_tick++;
//                if (time_tick > 20000) {
//                    int i,j;
//                    for ( int j =0; j<7; j++){
//                        matrix_display [j] = matrix[j];
//                        dichChu(matrix_display[i],matrix[j]);
//                       //matrix[j] = matrix_display[j];
//                       }
//                      
//                    time_tick = 0;
//                }   
//        time_tick_2++;
//        if (time_tick_2 > 20000) {
//            for (int i = 0; i < 8; i++) {
//                data_in[i] = matrix[i];
//                data_out[i] = data_out[i] >> 1;
//                show = 0x01 & (data_in[i] >> i);
//                data_out[i] |= (show << 7);
//                display = data_out[i];
//            }
//            time_tick_2 = 0;
//        }
//        time_tick++;
//        if (time_tick > 20000) {
//            for (j = 0; j < 8; j++) {
////                data_out[j] = data_out[j] >> 1;
////                show = 0x01 & (data_in[j] >> i);
////                data_out[j] |= (show << 7);
////                matrix[j] = data_out[j];
//                matrix[j] = display;
//            }
//            time_tick = 0;
//        }
        //time_tick++;
//        if (time_tick > 20000) {
//            for (int i = 0; i < 8; i++) {
////                matrix[i] = data_out[i];
//                matrix[j] = data_out[j];
//            }
//        }
        //led_matrix();
        data = matrix_display[5];
                    for (int i = 0; i < 8; i++) {
                        display = display >> 1;
                        show = 0x01 & (data >> i);
                        display |= (show << 7);
                        //__delay_ms(500);
                        time_tick++;
                      if (time_tick > 20000) {  
                        PORTC = display;
                        time_tick = 0;
                    }
                    }  
    }
    return;
}
