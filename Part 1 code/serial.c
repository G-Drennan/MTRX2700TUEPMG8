#include <mc9s12dp256.h>        /* derivative information */
#include "serial.h"
 
// instantiate the serial port parameters
//   note: the complexity is hidden in the c file
SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
SerialPort SCI0 = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};

// InitialiseSerial - Initialise the serial port SCI1
// Input: baudRate is tha baud rate in bits/sec
void SerialInitialise(int baudRate, SerialPort *serial_port) {
  
  // Baud rate calculation from datasheet
  switch(baudRate){
	case BAUD_9600:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=156;
	  break;
	case BAUD_19200:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=78;
	  break;
	case BAUD_38400:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=39;
	  break;
	case BAUD_57600:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=26;
	  break;
	case BAUD_115200:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=13;
	  break;
  }
     //#define SCI1CR2_TCIE_MASK               64U
    //#define SCI1CR2_SCTIE_MASK              
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|(SCI1CR2_TE_MASK|(SCI1CR2_TCIE_MASK|SCI1CR2_SCTIE_MASK)); 
  *(serial_port->ControlRegister1) = 0x00;
}  