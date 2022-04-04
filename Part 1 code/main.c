#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h> 
#include "serial.h" 


void main(void) { 
     
  /* put your own code here */

  char string_buffer[64];
  char string[] = "0ABC"; 
  sprintf(&string_buffer[0],"HELLO WORLD!"); 
  
  SerialInitialise(BAUD_9600, &SCI0);
  SerialInitialise(BAUD_9600, &SCI1);    
   
  //SerialOutputString(&string_buffer[0], &SCI0);
  //SerialOutputString(&string_buffer[0], &SCI1); 
  

  EnableInterrupts;
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
} 

/*interrupt 21 void GetOut(){ //Is this correctly on SCI1?

  SerialOutputString(&string_buffer[0], &SCI1); 
  
}*/    