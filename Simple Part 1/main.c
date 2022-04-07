#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>   

// NOTE: these are stored as pointers because they 
//       are const values so we can't store them directly
//       in the struct
typedef struct SerialPort {  
  byte *BaudHigh;
  byte *BaudLow;
  byte *ControlRegister1;
  byte *ControlRegister2;
  byte *DataRegister;
  byte *StatusRegister;
} SerialPort;

// make two instances of the serial port (they are extern because
//   they are fixed values)
extern SerialPort SCI0, SCI1;
 
// instantiate the serial port parameters
//   note: the complexity is hidden in the c file
SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
SerialPort SCI0 = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};

// InitialiseSerial - Initialise the serial port SCI1
// Input: baudRate is tha baud rate in bits/sec
void SerialInitialiseBasic(SerialPort *serial_port) {
  
  *(serial_port->BaudHigh)=0;
  *(serial_port->BaudLow)=156; 
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|(SCI1CR2_TE_MASK|(SCI1CR2_TCIE_MASK|SCI1CR2_SCTIE_MASK)); 
  //*(serial_port->ControlRegister2) = 0b1100100;    
  *(serial_port->ControlRegister1) = 0x00;
}   
//struct string_Buufer  
void OutputChar(char data, SerialPort *serial_port) {  
  
  while((*(serial_port->StatusRegister) & SCI1SR1_TDRE_MASK) == 0){
  } 
   
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
 SerialInitialiseBasic(&SCI1);  
 
/*while((*((&SCI1)->StatusRegister) & SCI1SR1_TDRE_MASK) == 0){
  }*/  
 OutputChar(s,&SCI1);     //char string_buffer[64];  // sprintf(&string_buffer[0],"HELLO WORLD!"); 
 
 //EnableInterrupts;          
 //GetOut();
 for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */   

}    