// CONFIG1
#define _XTAL_FREQ 8000000
#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
int count_2 = 0;
char data;
int i,j;
char UART_getChar(void);
void extract_data();
int index = 0;
int event_1 = 0, event_2 = 0;
int nghin,tram,  chuc,dv;
int time, number;
unsigned char LED[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
char data_receive[10];
char data_check[10];
int flag;
//void UART_sendChar(char val);
//void interrupt UART();
void LED_setup() {
    TRISB = 0; // 
    //  PORTA = 0;
    TRISD0 = 0;
    TRISD1 = 0;
    TRISD2 = 0;
    TRISD3 = 0;
    //TRISB= 0xff ; // INput 
    WPUB = 0XFF;
}
void segment() {
    if (time < 500) {
        time++;
    } else {
        //time = 0;
        number++;
        if (number > 5) {
            number = 1;
        }
        // time = 0;
    }
    switch (number) {
        case 1:
            RD0 = 0;
            RD1 = RD2 = RD3 = 1;
            PORTB = LED[nghin];
            break;
        case 2:
            RD1 = 0;
            RD0 = RD2 = RD3 = 1;
            PORTB = LED[tram];
            break;
        case 3:
            RD2 = 0;
            PORTB = LED[chuc];
            RD0 = RD1 = RD3 = 1;
            break;
        case 4:
            RD3 = 0;
            PORTB = LED[dv];
            RD0 = RD1 = RD2 = 1;
            break;
        case 5:
            RD0 = 1;
            RD1 = RD2 = RD3 = 1;
            PORTB = LED[nghin];
            break;
    }

}

void setup() {
    TRISB = 0X00;
    TXEN = 1;
    SYNC = 0;
    BRGH = 1;
    SPEN = 1;
    CREN = 1;
    //RCEN=1;
    SPBRG = 51;
    INTCON = 0X80;
    TRISCbits.TRISC6 = 0; // TX Pin set as output
    TRISCbits.TRISC7 = 1; // RX Pin set as input
    // set interupt
    RCIE = 1; // EUSART Receive Interrupt Enable bit
    TXIE = 1; //  EUSART Transmit Interrupt Enable bit
    GIE = 1;
    PEIE = 1;
}

void UART_sendChar(char val) {

    int count_2 = 0;
    count_2++;
    while (!TXIF) { //lam tre he thong khi bo dem TX dang trong

        if (count_2 > 200) {
            count_2 = 0;
            break;
        }

        // ghi gia tri truyen vao thanh ghi TXREG
    }
    TXREG = val;
}

char UART_getChar() {
    if (OERR) // check Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    int count = 0;
     //RCIF  USART Receive Interrupt Flag bit
    while (!RCIF) {
        count++;
        if (count > 20) {
            count = 0;
            break;
        }
    }// lam tre he thong khi bo dem RX dang trong
//    if (RCIF) {

        flag = 1;

    
    return RCREG;
}
void Check_data() {
    // index =0

    data_check[index] = UART_getChar();
    //if (flag == 1) {
        //UART_sendChar(index);
        //UART_sendChar(error);
        //UART_sendChar('A');
        if (data_check[index] == '!') {
            event_1 = 1;
            index = 0;
            //UART_sendChar('C');
        }
        if (data_check[1] == '@' && event_1 == 1) {
            event_1 = 2;
            
        }
        if (index < 6 && index > 1 && event_1 == 2) {
            if ((int) data_check[index] < 48 || (int) data_check[index] > 58) {
               
                index = 0;
                event_1 = 0;
            }
        }
        if (data_check[index] == 'A' && index == 6 && event_1 == 2) {//!@1234A 
            event_2 = 1;
            
        }
        index++;
        if (index > 6) {
            index = 0;
        }
       // flag = 0;
    //}
}
void extract_data() {
    if (event_2 == 1) {
        for (i = 0; i < 4; i++) {
            data_receive[i] = data_check[i + 2];
            UART_sendChar(data_receive[i]);

        }
        nghin = (int) data_receive[0] - 48;
        tram = (int) data_receive[1] - 48;
        chuc = (int) data_receive[2] - 48;
        dv = (int) data_receive[3] - 48;
        event_2 = 0;
        event_1 = 0;
        index = 0;
        
    }


}

void __interrupt() ISR(void) {
   
        //data = RCREG;
        TXREG = RCREG;
        Check_data();
//        while (!TRMT);
//        RCIF = 0;
//        
        //UART_sendChar('B');

    
}

void main() {
    LED_setup();
    setup();
    UART_sendChar('E');
    while (1) {
        extract_data();
        segment();
    }
}





