OpSys-Spr2020
Lab02 clearScreen function: Using a for loop that loops through 24 times, we were able to implement 24 carriage return character and 24 newline character using these interrupt 16.

readInt function: uses a while loop to multiply the running value by 10, add the current digit, and loop until all digits have been read and computed into an integer.  (The first iteration does not multiply by 10).

writeInt function:  Handles the special case for zero,and appends the NUL character to terminate the string.  The general case then takes the integer provided, and reads the least sisgnificant digit using the modulo function, converts to a char, and places in an array, in reverse order.  The array is reversed to reorder the digits of the number, then the NUL character is added.

readString function: using a do/while loop, reads a character, looks first for a CR and interprets with both the NL and CR characters, looks next for the backspace key, sending a BS value, then overwrite current value with a space, then deletes the space.  Finally, the general case is addresses displaying a normal typed character, increments and repeats.  Finally, the NUL is added to terminate the string. 

Interrupt 33/handleInterrupt21: Added three additional cases:  ax = 1 calls the readString(bx) function.  ax = 13 calls the writeInt(bx, cx) function.  ax = 14 calls the readInt(bx) function. 

-- Josh Newman, Andy Weaver 2/14/2020
