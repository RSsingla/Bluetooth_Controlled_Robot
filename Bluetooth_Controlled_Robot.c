/* Project name		: Bluetooth_Controlled_Robot
// Designed By 		: Entrench Electronics
// Designed for		: Entrench Electronics
//                	  http://entrench.in

/* Program for "Controlling Robot By Android Application Using Bluetooth " 
______________________________________________________________________________ 

RX ----> TX (PD1)
TX ----> RX (PD0)
GND----> GND pin of th MCU

*/

#define F_CPU 12000000UL 					// define clock speed of the MCU
#include <avr/io.h> 						// include avr header file
#include <util/delay.h> 					// include delay header file
 
void USARTInit(unsigned int ubrr_value) 	// USART initialization 
{
/*
Baud rate = 9600
Data bits =8
Parity = None
Stop bits = 1
Flow Control = None
Transmission Mode = Asynchronous
USART Reciever = ON
USART Transmitter = ON
U2X = 0
UBRR value = 77

ATMega8 Calibrated Internal RC Oscilator Frequency = 12 MHz

*/

UBRRL = ubrr_value;    
UBRRH = 0;
UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
UCSRB=(1<<RXEN)|(1<<TXEN);     				// Enable Receiver & Transmitter
}

unsigned char USARTReadChar()  				// USART recieving function
{
 while(!(UCSRA & (1<<RXC)));      			// Wait till the receiving  is not completed.
 return UDR;            					// Return the received data
}

void USARTTransmitChar(unsigned char data) 	// USART transmitting function
{
 while(!(UCSRA & (1<<UDRE)));   			// Wait till the data  register is not Empty.
 UDR=data;          						// put the data to be transfer
}

void USART_StringTransmit(unsigned char s[])  // function for string transmit
{
 int i=0;
 while(s[i]!='\0')
 {
 USARTTransmitChar(s[i]);
 i++;
 }

}

void main() 								// main function
{
DDRB=0b00011111;  							// declare PB4 as a output Pin connected to Buzzer
unsigned char data;
USARTInit(77);   							// Baudrate


while(1)  									// infinite loop
  	 {   
	 data=USARTReadChar();   				// waiting to receive new data
     
     if((data=='W')||(data=='w'))
	 {
	  USART_StringTransmit(" Forward\n\r"); 	// string transmit
	  PORTB=0b00010010;							// Move Forward
	 }
     
	 else if((data=='A')||(data=='a'))
	 {
	  USART_StringTransmit(" Left Turn\n\r");	// string transmit
	  PORTB=0b00000010;							// Turning Left
	 }

     else if((data=='D')||(data=='d'))
	 {
	  USART_StringTransmit(" Right Turn\n\r");	// string transmit
	  PORTB=0b00010000;							// Turning Right
	 }

	 else if((data=='X')||(data=='x'))
	 {
	  USART_StringTransmit(" Backward\n\r");	// string transmit
	  PORTB=0b00001100;							// Move Backward
	 }

	 else if((data=='S')||(data=='s'))
	 {
	  USART_StringTransmit(" Stop\n\r");		// string transmit
	  PORTB=0b00000000;							// Stop
	 }

	 else
	 {
      USART_StringTransmit("Sorry!!  Invalid Data\n\r");
	  PORTB=0b00010000;							// Buzzer ON 
     }
 
    
	 }									   		// while closed 
	
	
} 									   	   		// main closed

