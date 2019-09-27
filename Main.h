#include <16F877A.h>
#device ADC=16
#include <HC595.h>
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)
#use FIXED_IO( B_outputs=PIN_B1 )
#use FIXED_IO( D_outputs=PIN_D4,PIN_D3,PIN_D2,PIN_D1,PIN_D0 )
#define HC165_SO   PIN_B1
#define INPUT2   PIN_B2
#define MODE1   PIN_B4
#define MODE2   PIN_B5
#define HC595_SHCP   PIN_D0
#define HC595_DS   PIN_D1
#define HC595_STCP   PIN_D2
#define HC165_CLK   PIN_D3
#define HC165_SH   PIN_D4
#define LEDSTATUS   PIN_D7

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=RS485)

