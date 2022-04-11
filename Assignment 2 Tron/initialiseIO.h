#ifndef SCI1_HEADER
#define SCI1_HEADER

//**********************************************//
//***Output register setup***//
//Structure for addressing serial port registers
typedef struct SerialPort { 
  byte *BaudHigh;
  byte *BaudLow;
  byte *ControlRegister1;
  byte *ControlRegister2;
  byte *DataRegister;
  byte *StatusRegister;  
} SerialPort;

//Define external SCI1
extern SerialPort SCI1;

void SerialInitialiseBasic(SerialPort *serial_port);

#endif