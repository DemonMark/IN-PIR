#include <head.h>	
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom644p.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include <avr_compat.h>

#include "ip_arp_udp_tcp.h"
//#include "ip_arp_udp_tcp.c"
#include "enc28j60.h"
#include "timeout.h"
#include "net.h"

// network defines
static uint8_t mymac[6] = {0x44,0x4f,0x41,0x12,0xF2,0x12}; //MAC modulu PIR
static uint8_t myip[4] = {192,168,1,103}; //IP modulu PIR

static uint8_t mac_centr[6] = {0xb8,0x27,0xeb,0x35,0x5d,0x0b};//serwer RPi
static uint8_t dstip[4] = {192,168,1,2};

static uint8_t iphdr[9]={0x45,0,0,0x82,0,0,0x40,0,0x20}; //nag�owek w ip parametry
static uint16_t myport =1200; // listen port for udp
// how did I get the mac addr? Translate the first 0DOM0 numbers into ascii is: TUX
#define BUFFER_SIZE 1450
static uint8_t buf[BUFFER_SIZE+1]; 
//static uint8_t pakiet[BUFFER_SIZE+1]; 
 
uint16_t plen;
uint8_t i=0;
uint8_t cmd_pos=0;
uint8_t payloadlen=0;
//static uint8_t str[30];


volatile int z=0;  
char cmdval,led,led_delay;
char dane[26];
int reset_time=0;

//-------------------------------------------------------------------------
int main(void){

 uint8_t temp[25];
 uint8_t stan[25];

for(int i=0;i<=25;++i){
	stan[i]=0;  
	temp[i]=0;
	}

SystemInit();
/*initialize enc28j60*/
enc28j60Init(mymac);
// 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
// enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
enc28j60PhyWrite(PHLCON,0x476);
//delay_ms(20); 
init_ip_arp_udp_tcp(mymac,myip,80);
reset_time=0;

while(1){ 

//----------------------------------------------------------------------------	
	if(reset_time==306) //co 5sek 16MHz/1024 /T0=255
	{
		cbi(PORTD,PD0); //SCK low
	}
	if(reset_time==307)
	{
		sbi(PORTD,PD0);
	}	
	if(reset_time>=308)
	{
		reset_time = 0;
		enc28j60Init(mymac);
		// 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
		// enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
		enc28j60PhyWrite(PHLCON,0x476);
		init_ip_arp_udp_tcp(mymac,myip,80);
		reset_time = 0;
		zmiana = 1;
	} 
//--------------------------------------------------------------------------
	if(led==1){led_delay=0;cbi(PORTD,PD3);}
	if(led_delay>=5){sbi(PORTD,PD3);}	
		led=0;	
//--------------------------------------------------------------------------
	if(!(In1)){    
		stan[1]=0x01;
   	    if(temp[1]==0){
			zmiana=1;
			temp[1]=1;
			}
		}
   	else{ 
        stan[1]=0x00;
		if(temp[1]==1){
			zmiana=1;
			temp[1]=0;
			}
		}
	if(!(In2)){    
		stan[2]=0x01;
   	    if(temp[2]==0){
			zmiana=1;
			temp[2]=1;
			}
		}
	else{ 
        stan[2]=0x00;
		if(temp[2]==1){
			zmiana=1;
			temp[2]=0;
			}
		}
	if(!(In3)){    
		stan[3]=0x01;
		if(temp[3]==0){
			zmiana=1;
			temp[3]=1;
			}
		}
   	else{ 
        stan[3]=0x00;
		if(temp[3]==1){
			zmiana=1;
			temp[3]=0;
			}
		}
    if(!(In4)){    
		stan[4]=0x01;
		if(temp[4]==0){
			zmiana=1;
			temp[4]=1;
			}
		}
    else{ 
	    stan[4]=0x00;
	    if(temp[4]==1){
			zmiana=1;
			temp[4]=0;
			}
		}
    if(!(In5)){    
        stan[5]=0x01;
	    if(temp[5]==0){
			zmiana=1;
			temp[5]=1;
			}
		}
    else{ 
	    stan[5]=0x00;
	    if(temp[5]==1){
			zmiana=1;
			temp[5]=0;
			}
		}
    if(!(In6)){    
        stan[6]=0x01;
	    if(temp[6]==0){
			zmiana=1;
			temp[6]=1;
			}
		}
	else{ 
	    stan[6]=0x00;
	    if(temp[6]==1){
			zmiana=1;
			temp[6]=0;
			}
		}
    if(!(In7)){    
        stan[7]=0x01;
	    if(temp[7]==0){
			zmiana=1;
			temp[7]=1;
			}
		}
	else{ 
	    stan[7]=0x00;
	    if(temp[7]==1){
			zmiana=1;
			temp[7]=0;
			}
		}
    if(!(In8)){    
        stan[8]=0x01;
	    if(temp[8]==0){
			zmiana=1;
			temp[8]=1;
			}
		}
	else{ 
	    stan[8]=0x00;
	    if(temp[8]==1){
			zmiana=1;
			temp[8]=0;
			}
		}
    if(!(In9)){    
        stan[9]=0x01;
	    if(temp[9]==0){
			zmiana=1;
			temp[9]=1;
			}
		}
	else{ 
	    stan[9]=0x00;
	    if(temp[9]==1){
			zmiana=1;
			temp[9]=0;
			}
		}
    if(!(In10)){    
        stan[10]=0x01;
	    if(temp[10]==0){
			zmiana=1;
			temp[10]=1;
			}
		}
	else{ 
	    stan[10]=0x00;
	    if(temp[10]==1){
			zmiana=1;
			temp[10]=0;
			}
		}
	if(!(In11)){    
        stan[11]=0x01;
	    if(temp[11]==0){
			zmiana=1;
			temp[11]=1;
			}
		}
	else{ 
	    stan[11]=0x00;
	    if(temp[11]==1){
			zmiana=1;
			temp[11]=0;
			}
		}
    if(!(In12)){    
        stan[12]=0x01;
	    if(temp[12]==0){
			zmiana=1;
			temp[12]=1;
			}
		}
	else{ 
	    stan[12]=0x00;
	    if(temp[12]==1){
			zmiana=1;
			temp[12]=0;
			}
		}
    if(!(In13)){    
        stan[13]=0x01;
	    if(temp[13]==0){
			zmiana=1;
			temp[13]=1;
			}
		}
	else{ 
	    stan[13]=0x00;
	    if(temp[13]==1){
			zmiana=1;
			temp[13]=0;
			}
		}
    if(!(In14)){    
        stan[14]=0x01;
	    if(temp[14]==0){
			zmiana=1;
			temp[14]=1;
			}
		}
	else{ 
	    stan[14]=0x00;
	    if(temp[14]==1){
			zmiana=1;
			temp[14]=0;
			}
		}
    if(!(In15)){    
        stan[15]=0x01;
	    if(temp[15]==0){
			zmiana=1;
			temp[15]=1;
			}
		}
	else{ 
	    stan[15]=0x00;
	    if(temp[15]==1){
			zmiana=1;
			temp[15]=0;
			}
		} 
    if(!(In16)){    
        stan[16]=0x01;
	    if(temp[16]==0){
			zmiana=1;
			temp[16]=1;
			}
		}
	else{ 
	    stan[16]=0x00;
	    if(temp[16]==1){
			zmiana=1;
			temp[16]=0;
			}
		}
	if(!(In17)){    
        stan[17]=0x01;
	    if(temp[17]==0){
			zmiana=1;
			temp[17]=1;
			}
		}
	else{ 
	    stan[17]=0x00;
	    if(temp[17]==1){
			zmiana=1;
			temp[17]=0;
			}
		}	
    if(!(In18)){    
        stan[18]=0x01;
	    if(temp[18]==0){
			zmiana=1;
			temp[18]=1;
			}
		}
	else{ 
	    stan[18]=0x00;
	    if(temp[18]==1){
			zmiana=1;
			temp[18]=0;
			}
		}
	if(!(In19)){    
        stan[19]=0x01;
	    if(temp[19]==0){
			zmiana=1;
			temp[19]=1;
			}
		}
	else{ 
	    stan[19]=0x00;
	    if(temp[19]==1){
			zmiana=1;
			temp[19]=0;
			}
		}
    if(!(In20)){    
        stan[20]=0x01;
	    if(temp[20]==0){
			zmiana=1;
			temp[20]=1;
			}
		}
	else{ 
	    stan[20]=0x00;
	    if(temp[20]==1){
		zmiana=1;
	    temp[20]=0;
	    }
   	}	
	if(!(In21)){    
        stan[21]=0x01;
	    if(temp[21]==0){
			zmiana=1;
			temp[21]=1;
			}
		}
	else{ 
	    stan[21]=0x00;
	    if(temp[21]==1){
			zmiana=1;
			temp[21]=0;
			}
		}	
    if(!(In22)){    
        stan[22]=0x01;
	    if(temp[22]==0){
			zmiana=1;
			temp[22]=1;
			}
		}
	else{ 
	    stan[22]=0x00;
	    if(temp[22]==1){
			zmiana=1;
			temp[22]=0;
			}
		}	
 	if(!(In23)){    
        stan[23]=0x01;
	    if(temp[23]==0){
			zmiana=1;
			temp[23]=1;
			}
		}
	else{ 
	    stan[23]=0x00;
	    if(temp[23]==1){
			zmiana=1;
			temp[23]=0;
			}
		}	
    if(!(In24)){    
        stan[24]=0x01;
	    if(temp[24]==0){
			zmiana=1;
			temp[24]=1;
			}
		}
	else{ 
	    stan[24]=0x00;
	    if(temp[24]==1){
			zloz_pakiet(stan);
			zmiana=1;
			temp[24]=0;
	    }
   	}	
	
	if(zmiana==1){zloz_pakiet(stan);led=1;}
//--------------------------------------Obs�uga enc---wysy�anie------------------------------------------------------------------
 	if(zmiana==1){

        i=0;
        while(i<6){
            buf[ETH_DST_MAC +i]=mymac[i]; // gw mac in local lan or host mac
            buf[ETH_SRC_MAC +i]=mac_centr[i];
            i++;
			}
        buf[ETH_TYPE_H_P] = ETHTYPE_IP_H_V;
        buf[ETH_TYPE_L_P] = ETHTYPE_IP_L_V;
		memcpy(buf+IP_P,iphdr,9);
        // total length field in the IP header must be set:
        buf[IP_TOTLEN_H_P]=0;
        // done in transmit: buf[IP_TOTLEN_L_P]=IP_HEADER_LEN+UDP_HEADER_LEN+datalen;
        buf[IP_PROTO_P]=IP_PROTO_UDP_V;
        i=0;
        while(i<4){
            buf[IP_DST_P+i]=myip[i];
            buf[IP_SRC_P+i]=dstip[i];
            i++;
			}
        // done in transmit: fill_ip_hdr_checksum(buf);
		buf[UDP_SRC_PORT_H_P]=4;
		buf[UDP_SRC_PORT_L_P]=0xb0;
		buf[UDP_DST_PORT_H_P]=4;
		buf[UDP_DST_PORT_H_P]=0xb0;
        buf[UDP_LEN_H_P]=0;
        // done in transmit: buf[UDP_LEN_L_P]=UDP_HEADER_LEN+datalen;
        // zero the checksum
        buf[UDP_CHECKSUM_H_P]=0;
        buf[UDP_CHECKSUM_L_P]=0;
		//zloz_pakiet(kod,alarm,ruch,drzwi_wej);
		
		make_udp_reply_from_request(buf,dane,6,myport);		//by�o 9  ale minimum 64byte 41+ 23 pr�ba - 6 *******************************************************
		zmiana=0; // bylo na poczatku if
   }
 //----------------------------------Obs�uga enc---odbieranie-------------------------------------------------------------------  
    plen = enc28j60PacketReceive(BUFFER_SIZE, buf);
    if(plen==0){
         continue;
        }
	// arp is broadcast if unknown but a host may also
    // verify the mac address by sending it to 
    // a unicast address.
    if(eth_type_is_arp_and_my_ip(buf,plen)){    //odpowiedz na zapytranie arp jezeli moj ip 
        make_arp_answer_from_request(buf);
		continue;
        }
		
   // if(buf[IP_PROTO_P]==IP_PROTO_UDP_V){  //if do pakiet�w broadcastowych  z czasem
	//	memcpy(str1,buf+42,12);
	//	}
		
    // check if ip packets (icmp or udp) are for us:
    if(eth_type_is_ip_and_my_ip(buf,plen)==0){  //to jest siot co przepusza udp i ping
        continue;
        }
    if(buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V){
        // a ping packet, let's send pong
       make_echo_reply_from_request(buf,plen);
	   reset_time=0;
	   led=1;
       continue;
       }
//if (buf[IP_PROTO_P]==IP_PROTO_UDP_V&&buf[UDP_DST_PORT_H_P]==(MYUDPPORT>>8)&&buf[UDP_DST_PORT_L_P]==(MYUDPPORT&0xff)){
    if(buf[IP_PROTO_P]==IP_PROTO_UDP_V){   //  czy udp
	    // memcpy(str,buf+42,80);
	    //if (!(PIND & _BV(PD3))) {PORTD|=_BV(PD3);}
		//if (buf[42]==1) zmiana=1;
		reset_time=0;
		led=1;
		}
	}
}

uint16_t zloz_pakiet(uint8_t* stan){
dane[0]=0x3C;
dane[1]=0x49;
dane[2]=0x3E;
//strcpy(dane,"<I>");
/////////////////////////////////////////
if (stan[1]==0x00)	dane[3]|=0x01;
else				dane[3]&=~(0x01); 
if (stan[2]==0x00)	dane[3]|=0x02;
else				dane[3]&=~(0x02); 
if (stan[3]==0x00)	dane[3]|=0x04;
else				dane[3]&=~(0x04); 
if (stan[4]==0x00)	dane[3]|=0x08;
else				dane[3]&=~(0x08); 
if (stan[5]==0x00)	dane[3]|=0x10;
else				dane[3]&=~(0x10);
if (stan[6]==0x00)	dane[3]|=0x20;
else				dane[3]&=~(0x20);
if (stan[7]==0x00)	dane[3]|=0x40;
else				dane[3]&=~(0x40);
if (stan[8]==0x00)	dane[3]|=0x80;
else				dane[3]&=~(0x80);
if (stan[9]==0x00)	dane[4]|=0x01;
else				dane[4]&=~(0x01); 
if (stan[10]==0x00)	dane[4]|=0x02;
else					dane[4]&=~(0x02); 
if (stan[11]==0x00)	dane[4]|=0x04;
else					dane[4]&=~(0x04); 
if (stan[12]==0x00)	dane[4]|=0x08;
else					dane[4]&=~(0x08); 
if (stan[13]==0x00)	dane[4]|=0x10;
else					dane[4]&=~(0x10);
if (stan[14]==0x01)	dane[4]|=0x20;
else					dane[4]&=~(0x20);
if (stan[15]==0x01)	dane[4]|=0x40;
else					dane[4]&=~(0x40);
if (stan[16]==0x01)	dane[4]|=0x80;
else					dane[4]&=~(0x80);
if (stan[17]==0x01)	dane[5]|=0x01;
else					dane[5]&=~(0x01); 
if (stan[18]==0x01)	dane[5]|=0x02;
else					dane[5]&=~(0x02); 
if (stan[19]==0x01)	dane[5]|=0x04;
else					dane[5]&=~(0x04); 
if (stan[20]==0x01)	dane[5]|=0x08;
else					dane[5]&=~(0x08);
if (stan[21]==0x01)	dane[5]|=0x10;
else					dane[5]&=~(0x10);
if (stan[22]==0x01)	dane[5]|=0x20;
else					dane[5]&=~(0x20);
if (stan[23]==0x01)	dane[5]|=0x40;
else					dane[5]&=~(0x40);
if (stan[24]==0x01)	dane[5]|=0x80;
else					dane[5]&=~(0x80);
return (0);
}
//-------------------------------------------------------------------------------------------------------------
void SystemInit(void){
// initialize SPI interface
DDRB  |= 1<<PB5 | 1<<PB7; // mosi, sck output
cbi(DDRB,PINB6); // MISO is input
cbi(PORTB,PB5); // MOSI low
cbi(PORTB,PB7); // SCK low
DDRD |= 1<<PD0;
sbi(PORTD,PD0);
SetTimer0;	//deklaracja head.h
// master mode and Fosc/2 clock:
/*
SPCR = (1<<SPE)|(1<<MSTR);
SPSR |= (1<<SPI2X); 
*/
sei();

DDRC|=0X00;
PORTC |= 0Xff;
DDRA|=0X00;
PORTA |= 0Xff;
	
DDRD&=~(_BV(PD4)|_BV(PD5)|_BV(PD6)|_BV(PD7));
PORTD|=(_BV(PD4)|_BV(PD5)|_BV(PD6)|_BV(PD7));
	
DDRB&=~(_BV(PB0)|_BV(PB1)|_BV(PB2)|_BV(PB3));
PORTB|=(_BV(PB0)|_BV(PB1)|_BV(PB2)|_BV(PB3));
	
DDRD|=_BV(PD3);
//	PORTD|=_BV(PD3);
}
//---------------------------------------------------------------------------------
SIGNAL(SIG_OVERFLOW0)  //przerwanie wywolywane co 0.01632sek
{ 
	reset_time++; //deklaracje w head.h
	led_delay++;
}	
