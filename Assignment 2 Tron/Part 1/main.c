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
       //if a new line is created end the input interrupt. 
       if(currentInputChar==13){
       //turn interrupt off for input
         *(SCI1.ControlRegister2) &= ~SCI1CR2_RIE_MASK; 
       }    
  } 
  else if (*currentOutputCounter == 0x00){
    
    // string is finished, stop the transmit interrupt from firing
    //turn interrupt off for output 
    *(SCI1.ControlRegister2) &= ~SCI1CR2_TCIE_MASK;
  }
}

void outputSetUp(SerialPort *serial_port) {
     //Replacing SCI1 with serial_port causes the program to not work 
     // however the function has been set up with the serial port input for future uses and will need to be editied 
      
    //output  start, store string in the counter                                            
    currentOutputCounter = &string[0];
    // enable the transmit mask 
  *(SCI1.ControlRegister2) |= SCI1CR2_TCIE_MASK; 
    
    // interrupts are enabled, only send the first char then the interrupts will send the rest one at a time
  SerialOutputChar(*(currentOutputCounter++), &SCI1);  
    
  while (*currentOutputCounter != 0x00) { 
      // waiting in here until the string has completed sending
  }  
}

void main(void){  
 SerialInitialiseBasic(&SCI1);  

  EnableInterrupts
  
  //assign a new stirng to string to be outputted to the serial port. 
  string = "New String is longer than the original I'm sure of it\r\n";  
  //Run the first output code to start output. 
  outputSetUp(&SCI1);
    
  while(1){}     

}    