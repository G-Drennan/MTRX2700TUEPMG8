#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    

//output var
char *string = "Interrupts Activate!!!\r\n";
char *current_character = 0x00; 

//intput var
#define ARRSAPCE 64
char inputArray[ARRSAPCE];
char currentChar = ' ';   
int arrCounter = 0; 
 
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
 
// instantiate the serial port parameters
//   note: the complexity is hidden in the c file
SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
 
// InitialiseSerial - Initialise the serial port SCI1
// Input: baudRate is tha baud rate in bits/sec
void SerialInitialiseBasic(SerialPort *serial_port) {
  
  *(serial_port->BaudHigh)=0;
  *(serial_port->BaudLow)=156;
  //input set up *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_RIE_MASK;    
  //output set up
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_TCIE_MASK|SCI1CR2_RIE_MASK;     
  *(serial_port->ControlRegister1) = 0x00;
}   
//struct string_Buufer  
void SerialOutputChar(char data, SerialPort *serial_port) {  
  
  int wait_counter = 0;
  while((*(serial_port->StatusRegister) & SCI1SR1_TDRE_MASK) == 0){
     if (wait_counter < 0xFE)
       wait_counter++;
  }
  
  *(serial_port->DataRegister) = data; 
}
 
void SerialInputChar(SerialPort *serial_port){
  currentChar = *(serial_port->DataRegister);   
}

void ClearArr(){
        //reset the arr counter
       int arrCounter = 0;    
       //clear array
       memset(inputArray, 0, ARRSAPCE);       
}

interrupt VectorNumber_Vsci1 void SerialInterruptHandler(){
  //output
  if (*(SCI1.StatusRegister) & SCI1SR1_TDRE_MASK && *current_character != 0x00) {
    SerialOutputChar(*(current_character++), &SCI1);
  }
  //input
  else if(*(SCI1.StatusRegister) & SCI1SR1_RDRF_MASK){ 
       SerialInputChar(&SCI1);
       if(currentChar == 13){
         //end of input 
        //ClearArr();
        //main(); 
       } 
       inputArray[arrCounter] = currentChar;
       arrCounter++;  
  } 
  else if (*current_character == 0x00){
    
    // string is finished, stop the transmit interrupt from firing
    *(SCI1.ControlRegister2) &= ~SCI1CR2_TCIE_MASK;
  }
}         

void main(void){  
 SerialInitialiseBasic(&SCI1);  

  EnableInterrupts
  //output                                              
  current_character = &string[0];
    
    // enable the transmit mask 
  *(SCI1.ControlRegister2) |= SCI1CR2_TCIE_MASK;
    
    // interrupts are enabled, only send the first char then the interrupts will send the rest one at a time
  SerialOutputChar(*(current_character++), &SCI1);
    
  while (*current_character != 0x00) {
      // waiting in here until the string has completed sending
  }
  
  while(1){}    

}    