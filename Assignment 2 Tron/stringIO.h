#ifndef STRING_IO
#define STRING_IO
 
#include "initialiseIO.h"
 

void SerialOutputChar(char data, SerialPort *serial_port, int *fpointer);

void SerialInputChar(SerialPort *serial_port, char *pointer, int arrInLocation);

#endif