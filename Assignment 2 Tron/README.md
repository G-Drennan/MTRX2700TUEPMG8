# Assignment 2 

Giaan Drennan, Minghan Li, Antonio Matruglio, Lachlan Mizon.

## Part 1

This program puts input and output to teh serial port 1 (SCI1).

**Output**

The output fuction first requries a charater to be outputted to the serial port before the rest of the string can be sent. The charaters sent to the terminal is recored by a varaible currentOutputCounter which removes the current charater as it is outputted to teh terminal. Once the sting is fully sent to teh terminal the output interrupt is stopped. 

**TEST**

The output was tested by stepping thru the code and ensureing that the ouput matches the expected output in the code.

**Input**

The input function takes a global variable inputArray and then assigns charaters in the serial to the string. When the enter charater (13) is entered the input is stopped.

**TEST**

The input was tested by entering in a string in the terrminal and ensuring that the charaters appeared in the inputArray.  

## Part 2
## Part 3 
