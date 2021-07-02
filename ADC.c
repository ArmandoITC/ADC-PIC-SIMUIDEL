/*
 * File:   main.c
 * Author: arks3a@gmail.com
 *
 * Created on 7/2/2021 2:22:35 AM UTC
 * "Created in MPLAB Xpress"
 */
/// CONFIG
#pragma config FOSC = HS      // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF     // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF    // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF    // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF      // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF      // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF      // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF       // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 8000000
void ADC_Init()
{
  ADCON0 = 0x81;               //Turn ON ADC and Clock Selection
  ADCON1 = 0x80;               //All pins as Analog Input and setting Reference Voltages
}

unsigned int ADC_Read(unsigned char channel)
{
  if(channel > 7)              //Channel range is 0 ~ 7
    return 0;

  ADCON0 &= 0xC5;              //Clearing channel selection bits
  ADCON0 |= channel<<3;        //Setting channel selection bits
  __delay_ms(2);               //Acquisition time to charge hold capacitor
  GO_nDONE = 1;                //Initializes A/D conversion
  while(GO_nDONE); 
  unsigned int adc=ADRESH;
  adc=ADRESH<<8;
  adc=adc+ADRESL;
  return (adc); //Return result
}




void main(void) {
  unsigned int a;
  TRISA = 0xFF;                 //Analog pins as Input
  TRISB = 0x00;                 //Port B as Output
  TRISC = 0x00;                 //Port C as Output
  ADC_Init();                   //Initialize ADC

  do
  {
    a = ADC_Read(0);            //Read Analog Channel 0
    PORTC = a;                  //Write Lower bits to PORTB
    a=a>>8;
    PORTB=a;
    __delay_ms(100);            //Delay
  }while(1); 
    return;
}



