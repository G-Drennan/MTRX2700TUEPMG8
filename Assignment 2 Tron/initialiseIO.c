#include <mc9s12dp256.h>
#include "initialiseIO.h"

//Assign SCI1 registers to struct  
SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};

//Set relevant values in SCI1 registers, clear SCI1CR1
void SerialInitialiseBasic(SerialPort *serial_port) {

  //baud rate is BAUD_9600
  *(serial_port->BaudHigh)=0;
  *(serial_port->BaudLow)=156;   
  
  //Set bits in CR2 and clear CR1
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_SCTIE_MASK|SCI1CR2_RIE_MASK;     
  *(serial_port->ControlRegister1) = 0x00;
}