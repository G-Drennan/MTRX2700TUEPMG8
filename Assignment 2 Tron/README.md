# Assignment 2 

Giaan Drennan, Minghan Li, Antonio Matruglio, Lachlan Mizon.

## Part 1

This program puts input and output to the desired serial port written the the various functions (in this case SCI1).

**Output**

The output fuction first requries a charater to be outputted to the serial port before the rest of the string can be sent. The charaters sent to the terminal is recored by a pointer varaible currentOutputCounter which removes the current charater from its stack as it's outputted to the terminal. Once the sting is fully sent to the terminal the output interrupt is stopped as the pointer currentOutputCounter is empty. 

**TEST**

The output was tested by stepping thru the code and ensureing that the ouput matches the expected output in the code and that the pointer moved thru the array as needed. 

**Input**

The input function takes a global variable inputArray and then assigns charaters in the serial port to the inputArray. When the enter charater (13) is entered the input is stopped.

**TEST**

The input was tested by entering in a string in the terrminal and ensuring that the charaters appeared in the inputArray.  

## Part 2
## Part 3 
