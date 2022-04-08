#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>   

//stuct to define the serial ports by
typedef struct SerialPort { 
  byte *BaudHigh;
  byte *BaudLow;
  byte *ControlRegister1;
  byte *ControlRegister2;
  byte *DataRegister;
  byte *StatusRegister; 
} SerialPort; 

//output var
char *string = "Interrupts Activate!!!\r\n";
char *currentOutputCounter = 0x00;

//intput var
char inputArray[64];
char currentInputChar = ' ';   
int arrInCounter = 0x00;  
 
// instantiate the serial port parameters
SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
 
// InitialiseSerial - Initialise the serial port SCI1
// Input: baudRate is tha baud rate in bits/sec
void SerialInitialiseBasic(SerialPort *serial_port) {
  //baud rate is BAUD_9600
  *(serial_port->BaudHigh)=0;
  *(serial_port->BaudLow)=156;   
  
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_TCIE_MASK|SCI1CR2_RIE_MASK;     
  *(serial_port->ControlRegister1) = 0x00;
}
  
void SerialOutputChar(char data, SerialPort *serial_port) {    
  //place char inot the serial port
  *(serial_port->DataRegister) = data; 
}
 
void SerialInputChar(SerialPort *serial_port){
  //retrive the inputted char from the serial port
  currentInputChar = *(serial_port->DataRegister);
  //store current input in the arr
  inputArray[arrInCounter] = currentInputChar;
  arrInCounter++;   
}

interrupt VectorNumber_Vsci1 void SerialInterruptHandler(){
  //output interrupt
  if (*(SCI1.StatusRegister) & SCI1SR1_TDRE_MASK && *currentOutputCounter != 0x00) {
    SerialOutputChar(*(currentOutputCounter++), &SCI1);
  }
  //input interrupt
  else if(*(SCI1.StatusRegister) & SCI1SR1_RDRF_MASK){ 
       SerialInputChar(&SCI1);
       //if a new line is created end the input interrupt. 
       if(currentInputChar==13){
         *(SCI1.ControlRegister2) &= ~SCI1CR2_RIE_MASK; 
       }
  } 
  else if (*currentOutputCounter == 0x00){
    
    // No more char, stop output interrupt
    *(SCI1.ControlRegister2) &= ~SCI1CR2_TCIE_MASK;
  } 
}         

void main(void){  
 SerialInitialiseBasic(&SCI1);  

  EnableInterrupts
  
  //output  start
  //chose a stirng to send                                            
  currentOutputCounter = &string[0];
    
  // enable the transmit mask for output 
  *(SCI1.ControlRegister2) |= SCI1CR2_TCIE_MASK;
  
  while(1){}    

}  
