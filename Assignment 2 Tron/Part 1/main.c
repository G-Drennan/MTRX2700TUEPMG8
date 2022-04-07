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

//output var
char *string = "Interrupts Activate!!!\r\n";
char *currentOutputCounter = 0x00;

//intput var
char inputArray[64];
char currentInputChar = ' ';   
int arrInCounter = 0x00;  
 
// instantiate the serial port parameters
//   note: the complexity is hidden in the c file
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
  currentInputChar = *(serial_port->DataRegister);
  //store current input in the arr
  inputArray[arrInCounter] = currentInputChar;
  arrInCounter++;   
}

interrupt VectorNumber_Vsci1 void SerialInterruptHandler(){
  //output
  if (*(SCI1.StatusRegister) & SCI1SR1_TDRE_MASK && *currentOutputCounter != 0x00) {
    SerialOutputChar(*(currentOutputCounter++), &SCI1);
  }
  //input
  else if(*(SCI1.StatusRegister) & SCI1SR1_RDRF_MASK){ 
       SerialInputChar(&SCI1);   
  } 
  else if (*currentOutputCounter == 0x00){
    
    // string is finished, stop the transmit interrupt from firing
    *(SCI1.ControlRegister2) &= ~SCI1CR2_TCIE_MASK;
  }
}         

void main(void){  
 SerialInitialiseBasic(&SCI1);  

  EnableInterrupts
  
  //output  start                                            
  currentOutputCounter = &string[0];
    
    // enable the transmit mask 
  *(SCI1.ControlRegister2) |= SCI1CR2_TCIE_MASK;
    
    // interrupts are enabled, only send the first char then the interrupts will send the rest one at a time
  SerialOutputChar(*(currentOutputCounter++), &SCI1);
    
  while (*currentOutputCounter != 0x00) {
      // waiting in here until the string has completed sending
  } 
  
  while(1){}    

}  