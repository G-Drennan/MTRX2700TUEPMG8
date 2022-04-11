# Assignment 2 

Giaan Drennan, Minghan Li, Antonio Matruglio, Lachlan Mizon.

## Part 1

This program puts input and output with interrupts to the desired serial port written the the various functions (in this case SCI1). These interrupts only take a few milliseconds.  

**Output**

The output fuction first requries a charater to be outputted to the serial port before the rest of the string can be sent. The charaters sent to the terminal is recored by a pointer varaible currentOutputCounter which removes the current charater from its stack as it's outputted to the terminal. Once the sting is fully sent to the terminal the output interrupt is stopped as the pointer currentOutputCounter is empty. 
The string is initialy stored as an array of size 64.

**TEST**

The output was tested by stepping thru the code and ensureing that the ouput matches the expected output in the code and that the pointer moved thru the array as needed. 

**Input**

The input function takes a global variable inputArray and then assigns charaters in the serial port to the inputArray. When the enter charater (13) is entered the input is stopped.
The inputArray is initialy stored as an array of size 64. 

**TEST**

The input was tested by entering in a string in the terrminal and ensuring that the charaters appeared in the inputArray.  

## Part 2

**High Level Information**

This code accepts characters from the terminal and performs commands based on what was input after the user has hit enter.

The is separated into a main file, a file that sets up the IO ports, a file that gathers incoming characters and outputs strings, and a module that runs tasks based on what input characters/commands were sen't.

**Instructions**

The code currently accepts 3 commands with parameters. The music command is expanded upon in section 3. The other two commands are "message" and "LED". If the user inputs message, it will output two different messages depending on whether it was followed with a 1 or a 2, e.g. "message 1". The LED command will turn an LED on the dragon board on or off depending on whether it was followed with on or off, e.g. "LED on". Any invalid messages or parameters will be met with an error.

**Testing**

The code can be tested much the same way to checking the I/O module, by checking the memory where the input was allocated to see if the correct characters are stored, or checking the terminal for whether the correct characters are output. Additionally, by separating the code into modules, the variables before and after different modules were run can help narrow down where any issues may lie.

**Discussion**

By adding in a new string to the if else statement, it could quite easily be added to the command function. It's designed to add more potential commands as add ons if need be, simply requiring the string that is the command, and what the command does. 

The parser could fail if there were input commands that were longer than 64 characteres long, by not adding a space between parameters and the original keyword, by typing the word for a number for a parameter instead of the number itself, and by typing in characters faster than the software can input them.

## Part 3 
The program converts a character into a note. Using the method developed in exercise 1, a string of char is passed through the terminal to the function. The produced note is then determined based on the binary input of that character. This is done with the below data structure. 

                                                                            _ _  _ _  _ _ _ _ 
                                                                             Oc   Du   Notes 
                                                                             
Using this logic two functions were developed to determine the corresponding frequency and the duration of the note called find_freq, find_duration. Find_duration determines if the corresponding bits are a 0-3, dependent on this the duration will be a full, half, quarter, or eight note. The find_frequency function determines the inputted note value to be from 0-15, representing 12 notes and 4 rests. The 12 notes are initialised to be in the third octave. Then the inputted octave is considered whose value can range from 0-3. The initial frequency is then multiplied two to the power of the octave value. If the note is selected to be a rest i.e., a 12-15, the function will return a zero. The function then returns the results as an integer. Using these two integers a play note function is called. The function checks if the input was a rest note, turning the speaker off if so. Otherwise the function plays the note for the specified duration. 

**Testing**

The code can be tested using the below program in another script and a note tuner app. Using the script, the user can define the note on a bit level. The script will then produce the relevant character. This can then be inputted to the exercise and verified with the not tuner app. 

#include <stdio.h>

int main()
{
    char buffer[8];
    if (0 == fread(buffer, sizeof(char), 8, stdin))
        return 1;
    
    unsigned char byte = 0;
    for (int i = 0; i < 8; i++)
    {
        char c = buffer[i];
        unsigned int num = c - '0';
        num = num << (7 - i);
        byte |= num;
    }

    printf("%c\n", byte);
    printf("%d\n", byte);

    return 0;
}

**Discussion**
If a new tune is requested before the previous one finishes the program will que the song and it will be played once the current song is completed. 

As the input is read from terminal and due to the consideration of each of the 8 bits to produce a note there are no invalid inputs. In fact, the number of inputs is greater than the number of inputs possible on the keyboard. If there was a parsing error from the tune string the outputted song would have undefined behaviour.

