#include <mc9s12dp256.h>

#include "stringIO.h"
#include "initialiseIO.h"


//**********************************************//
//***Receiving and sending char functions***///

//Outputting string char function
//Takes a character as data and outputs it
void SerialOutputChar(char data, SerialPort *serial_port, int *fpointer){  
 
 //Output the data to the register
  *(serial_port->DataRegister) = data; 
  
  //If the input data was a newline, reset the writing flag to 0
  if (data == '\n'){
    *fpointer = 0;
  } 
}




//Receiving char from serial port function
//Takes a pointer to a location in a string 
void SerialInputChar(SerialPort *serial_port, char *pointer, int arrInLocation){

  //Store the incoming data to where the pointer points to
  pointer[arrInLocation] = *(serial_port->DataRegister);
     
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