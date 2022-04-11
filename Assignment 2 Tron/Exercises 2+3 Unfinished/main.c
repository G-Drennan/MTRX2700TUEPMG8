#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>   
#include <string.h>

#include "playMusic.h"
#include "commands.h"
#include "stringIO.h"
#include "initialiseIO.h"

int i; //i for a for loop

char *currentOutputLocation; //Stores character for output string
int writingFlag = 0; //Variable for if the program is currently outputting a string
int *wFpointer = &writingFlag; //Pointer to the writing flag


int musicFlag = 0; //Variable for if the program is to output music
int *mFpointer = &musicFlag; //Pointer to the music flag
char* Notes[8];
 
char inputArray[64]; //Allocated memory for incoming strings  
int arrInLocation; //Location in array for incoming strings


interrupt VectorNumber_Vsci1 void SerialInterruptHandler(){

  //***
  //Output
  if (IsOutTrue(&SCI1) && (writingFlag == 1)) {
  
    //Output the current character of the string
    SerialOutputChar(*(currentOutputLocation), &SCI1, wFpointer);  
    
    //Increment char it points to
    currentOutputLocation++;  
    
  } 
  
  
  //***
  //Input
  else if(IsInTrue(&SCI1) && (writingFlag==0)){ 
  
    //Store the current input character to the array by passing pointer to currently empty location
    SerialInputChar(&SCI1, inputArray, arrInLocation);
    
    //If the most recently read function is a newline character, read the command
    if(inputArray[arrInLocation] == '\r'){
   
      char* outputString = commandFunction(inputArray, wFpointer, mFpointer, *Notes); //Calls the command function
      currentOutputLocation = &outputString[0]; //Assigns the output character to the returned string
      
      
       
      
      
      arrInLocation = 0; //Resets the location of the input array pointer
      
      //Cycle through the number of bits assigned and set to 0 to clear previous input
      for(i=0; i<64; ++i){
        inputArray[i] = 0;
      }
     
       
      
      if(writingFlag == 1){
        SerialOutputChar(*(currentOutputLocation), &SCI1, wFpointer); //Force the first character output
        currentOutputLocation++; //Increment pointer  
      } 
      
      //If it was the music function, play the song
      if(musicFlag == 1){
        playMusic(*Notes);  
      }
      
    }else{
  
      //Increment array location if not finished inputting
      arrInLocation++;
    }
            
  }
}


//Main
void main(void){

  SerialInitialiseBasic(&SCI1); //Initialise the SCI1 port
  DDRB = 0xFF; //Set the direction to output
  PORTB = 0x00; //LEDs are off to begin with
	EnableInterrupts //Turn on interrupts


  for(;;) {
  
  } 
}
