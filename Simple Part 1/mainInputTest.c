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

//intput var
char inputArray[64];
char currentChar = ' ';   
int arrCounter = 0;   
 
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
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_TCIE_MASK;     
  *(serial_port->ControlRegister1) = 0x00;
} 

void SerialInputChar(SerialPort *serial_port){
  currentChar = *(serial_port->DataRegister);   
}

interrupt VectorNumber_Vsci1 void SerialInterruptHandler(){
  //input 
  if(*(SCI1.StatusRegister) & SCI1SR1_RDRF_MASK){ 
       SerialInputChar(&SCI1); 
       inputArray[arrCounter] = currentChar;
       arrCounter++;  
  } 
}         

//interrupt 21 void GetIn();  

void main(void){  
 SerialInitialiseBasic(&SCI1);  

  EnableInterrupts
  
  while(1){}    

}         

/*
#define SCI1CR2_SBK_MASK                1U //0
#define SCI1CR2_RWU_MASK                2U
#define SCI1CR2_RE_MASK                 4U
#define SCI1CR2_TE_MASK                 8U
#define SCI1CR2_ILIE_MASK               16U
#define SCI1CR2_RIE_MASK                32U
#define SCI1CR2_TCIE_MASK               64U
#define SCI1CR2_SCTIE_MASK              128U //7
*/         
  