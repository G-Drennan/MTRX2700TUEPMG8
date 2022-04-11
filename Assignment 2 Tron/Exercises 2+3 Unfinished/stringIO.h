#ifndef STRING_IO
#define STRING_IO
 
#include "initialiseIO.h"
 
//Functions definitions
void SerialOutputChar(char data, SerialPort *serial_port, int *fpointer);

void SerialInputChar(SerialPort *serial_port, char *pointer, int arrInLocation);

int IsInTrue(SerialPort *serial_port);

int IsOutTrue(SerialPort *serial_port); 

#endif