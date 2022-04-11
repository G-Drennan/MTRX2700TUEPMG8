#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>   

// Struct for serial port variables, set as pointers as they can't be stored in teh struct.
typedef struct SerialPort { 
  byte *BaudHigh;
  byte *BaudLow;
  byte *ControlRegister1;
  byte *ControlRegister2;
  byte *DataRegister;
  byte *StatusRegister;   
} SerialPort;  

//output var 
char *string = "1234567890123456789012345678901234567890123456789012345678901234"; //string is used for output
char *currentOutputCounter = 0x00; //pointer to string

//intput var
char inputArray[64]; //where inputts are held
char currentInputChar = ' '; //holds the current inputted charater  
int arrInCounter = 0x00;  //used to move along the input arr as new input is placed in the serial port.
 
// Serial port parameters 
SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
 
// InitialiseSerial - Initialise the serial port
void SerialInitialiseBasic(SerialPort *serial_port) {
  //baud rate is BAUD_9600
  *(serial_port->BaudHigh)=0;
  *(serial_port->BaudLow)=156;   
  
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_TCIE_MASK|SCI1CR2_RIE_MASK;     
  *(serial_port->ControlRegister1) = 0x00;
}   

//output char data to the serial_port
void SerialOutputChar(char data, SerialPort *serial_port) {   
  *(serial_port->DataRegister) = data; 
}

//Take input from serial_port and store in inputArray 
void SerialInputChar(SerialPort *serial_port){
  currentInputChar = *(serial_port->DataRegister);
  //store current input in the arr
  inputArray[arrInCounter] = currentInputChar;
  arrInCounter++;
  //if a new line is created end the input interrupt.  
  if(currentInputChar==13){
       //turn interrupt off for input
         *(serial_port->ControlRegister2) &= ~SCI1CR2_RIE_MASK; 
  }    
}

//End the output to serial_port 
void endoutput(SerialPort *serial_port){

   *(serial_port->ControlRegister2) &= ~SCI1CR2_TCIE_MASK; 

}

//  outputs 1 if the form of serial port is output
int IsOutTrue(SerialPort *serial_port){
   int boo = *(serial_port->StatusRegister) & SCI1SR1_TDRE_MASK;
   return boo;
}

//  outputs 1 if the form of serial port is input
int IsInTrue(SerialPort *serial_port){
   int boo = *(serial_port->StatusRegister) & SCI1SR1_RDRF_MASK;
   return boo;
}

interrupt VectorNumber_Vsci1 void SerialInterruptHandler(){
  //output 
  if (IsOutTrue(&SCI1) && *currentOutputCounter != 0x00) {
    SerialOutputChar(*(currentOutputCounter++), &SCI1);
  }
  //input
  else if(IsInTrue(&SCI1)){ 
       SerialInputChar(&SCI1);
       
           
  }
  //end output
  else if (*currentOutputCounter == 0x00){
     // string is finished, stop the transmit interrupt from firing
    //turn interrupt off for output
     endoutput(&SCI1); 
  }
}

void outputSetUp(SerialPort *serial_port) {
 
    //output  start, store string in the counter                                            
    currentOutputCounter = &string[0];
    // enable the transmit mask 
  *(serial_port->ControlRegister2) |= SCI1CR2_TCIE_MASK; 
    
    // interrupts are enabled, only send the first char then the interrupts will send the rest one at a time
  SerialOutputChar(*(currentOutputCounter++), serial_port);  
    
  while (*currentOutputCounter != 0x00) {  
      // waiting in here until the string has completed sending
  }  
}

void main(void){  
  //Initialies the desired serial port 
  SerialInitialiseBasic(&SCI1);  

  EnableInterrupts
  
  //assign a new stirng to string to be outputted to the serial port. 
  string = "New String is shorter than the original I'm sure of it\r\n";  
  //Run the first output code to start output. 
  outputSetUp(&SCI1);
    
  while(1){}     

}   