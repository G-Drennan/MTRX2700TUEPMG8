#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h> 
#include "serial.h" 
 //SCI1 = 0b1100100; 
//struct string_Buufer  
void OutputChar(char data, SerialPort *serial_port) {  
  *(serial_port->DataRegister) = data;
}

interrupt 21 void GetOut(){ //data register has been transimited
  char d = 'd'; 

  OutputChar(d,&SCI1);             
  //SerialOutputString(&string_buffer[0], &SCI1);   
}      

//interrupt 21 void GetIn(); 

void main(void){  
 char s = 'S';
 //DisableInterrupts;   
 //SerialInitialise(BAUD_9600, &SCI0);
 SerialInitialise(BAUD_9600, &SCI1);
 
while((*((&SCI1)->StatusRegister) & SCI1SR1_TDRE_MASK) == 0){
  } 
 OutputChar(s,&SCI1);    
 //char string_buffer[64];

 // sprintf(&string_buffer[0],"HELLO WORLD!"); 

 //EnableInterrupts;       
 //GetOut();
 while(1){}  

}   
  
   