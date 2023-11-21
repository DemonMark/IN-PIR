#include <compat/deprecated.h>
#include <util/delay.h>

//----------------------------------------------------------------------------------


unsigned int t1,t2,t3;
int t;

#define SetTimer0 TCCR0B=0X05;TIMSK0|=_BV(TOIE1);


#define In4          PIND & _BV(PD6)
#define In3          PIND & _BV(PD7)
#define In2          PIND & _BV(PD4)
#define In1          PIND & _BV(PD5)

#define In8          PINC & _BV(PC2)
#define In7          PINC & _BV(PC3)
#define In6          PINC & _BV(PC0)
#define In5          PINC & _BV(PC1)


#define In12         PINC & _BV(PC6)
#define In11         PINC & _BV(PC7)
#define In10         PINC & _BV(PC4)
#define In9          PINC & _BV(PC5)

#define In16         PINA & _BV(PA5)
#define In15         PINA & _BV(PA4)
#define In14         PINA & _BV(PA7)
#define In13         PINA & _BV(PA6)

#define In20         PINA & _BV(PA1) 
#define In19         PINA & _BV(PA0)
#define In18         PINA & _BV(PA3)
#define In17         PINA & _BV(PA2)

#define In24         PINB & _BV(PB2)
#define In23         PINB & _BV(PB3)
#define In22         PINB & _BV(PB0)  
#define In21         PINB & _BV(PB1)
//----------------------------------------------------------------------

void SystemInit(void);
uint16_t zloz_pakiet(uint8_t*)	;


///////////////////////////////////////////////////////////main.c//////////////////////////////////////////////

uint8_t nats1,nats2,nats3,nats4,nats5;
unsigned int tha,ha,ta,ua,push,push2,push3,push4,push5,temp_d,temp_n,nat1,nat2,nat3,nat4,nat5,pilot_licz,p,przycisk;
char zrodlo1,zrodlo2,zrodlo3,zrodlo4,zrodlo5,swiatlo1,swiatlo2,swiatlo3,swiatlo4,swiatlo5,czujka,irda,klimat,d_n,push_up,push2_up,push3_up,push4_up,push5_up,push_down,zmiana; 
char temp_out_H,temp_out_L;
//string moje="A"; 

unsigned int temp_in,rh_in;
int stan1;

