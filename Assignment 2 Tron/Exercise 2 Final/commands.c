#include <mc9s12dp256.h>
#include <string.h>

#include "commands.h"

//Define the constant strings for the different kinds of commands
const char outputCommand[] = "message";
const char LEDCommand[] = "LED";
const char musicCommand[] = "music";


//**********************************************//
//Define the strings to be output depending on inputs
extern char outputMessage1[] = "This command outputs a message\r\n";
extern char outputMessage2[] = "Or potentially outputs this message\r\n";
extern char errorMessage1[] = "Invalid command\r\n";
extern char errorMessage2[] = "Invalid command parameters\r\n";

//**********************************************//
//Compare input to command function
char* commandFunction(char *inputString, int *wFpointer){
  
  //Get the length of the input string
  int len = strlen(inputString);
  
  //Output Command
  if(!strncmp(inputString, outputCommand, 7)){
  
    //Set writing flag pointer to 1
    *wFpointer = 1; //Turns on writing flag to ignore reading interrupts
    
    //First message if parameter is 1
    if(inputString[8] == '1'){
    
      return outputMessage1; //Set the string location to the outputMessage1

    //Second message if parameter is 2
    }else if(inputString[8] == '2'){
    
      return outputMessage2; //Set the string location to the outputMessage2

    //Parameter Error if not 1 or 2
    }else{
     
      return errorMessage2; //Set the string location to the errorMessage

    }
    
  //LED command  
  }else if(!strncmp(inputString, LEDCommand, 3)){
  
    //LED on if parameter is on
    if(!strcmp(inputString + len - 3, "on\r")){
    
      PORTB = 1;//Turn LED on
    
    //LED Off if parameter is off 
    }else if(!strcmp(inputString + len - 4, "off\r")){
      PORTB = 0;//Turn LED off
      
    //Parameter error if not on or off
    }else{
    
      *wFpointer = 1; //Turns on writing flag to ignore reading interrupts
      return errorMessage2; //Set the string location to the errorMessage
    }
    
  //Music Command   
  }else if(!strncmp(inputString, musicCommand, 5)){
  
  
  //Error command  
  }else{
  
    
    *wFpointer = 1; //Turns on writing flag to ignore reading interrupts
    return errorMessage1; //Set the string location to the errorMessage
 
  }
}