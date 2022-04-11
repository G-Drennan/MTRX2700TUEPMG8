#include <mc9s12dp256.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"

//Define the constant strings for the different kinds of commands
const char outputCommand[] = "message";
const char LEDCommand[] = "LED";
const char musicCommand[] = "music";


//**********************************************//
//Define the strings to be output depending on inputs
extern char outputMessage1[] = "This command outputs a message\r\n";
extern char outputMessage2[] = "Or potentially outputs this message\r\n";
extern char errorMessageGeneral[] = "Invalid command\r\n";
extern char errorMessageMessage[] = "Invalid command parameters, must be a 1 or a 2\r\n";
extern char errorMessageLED[] = "Invalid command parameters, must be on or off\r\n";

//Music related variables 
char returnMessage[20];
int song_length;
int j;

// this function determines duration of the input, assuming a full note is 4000 ms long 
int find_duration(char note){
  int index = 0;

  unsigned char mask = 0x30; // Concider these bit 00110000
  unsigned int duration_index = (mask & note) >> (4); // shift over 4 places so we get 0-3

  int corresponding_duration[4]= {500, 1000, 2000, 4000}; // defined four durations, eight, quater, half, full of a four second note

  return corresponding_duration[duration_index];
}



//**********************************************//
//Compare input to command function
char* commandFunction(char *inputString, int *wFpointer, int *mFpointer, char *Notes){
  
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
     
      return errorMessageMessage; //Set the string location to the errorMessage

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
      return errorMessageLED; //Set the string location to the errorMessage
    }
    
  //Music Command   
  }else if(!strncmp(inputString, musicCommand, 5)){
  
    *wFpointer = 1; //Turns on writing flag to ignore reading interrupts
    *mFpointer = 1; //Turn on the music flag
    
    strncpy(Notes, inputString+6,8); //Isolate the notes
    
    
    song_length = 0;
     
    for (j = 0; j<8; j++){
      char current_note = Notes[j];
      song_length = song_length + find_duration(current_note);         // sum the duration of each note 
                                                                   // to give the length of the song 
    }
    
    //Convert the integer song length to a string to be returned 
    sprintf(returnMessage, "Song goes for %i\r\n", song_length);//Convert the number of beats to the string to be returned
    return returnMessage; //Return the string to be output to terminal
                                                                              
  //Error command  
  }else{
  
    
    *wFpointer = 1; //Turns on writing flag to ignore reading interrupts
    return errorMessageGeneral; //Set the string location to the errorMessage
 
  }
}