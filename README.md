# OpSys-Spr2020

Lab01
  clearScreen function: Using a for loop that loops through 24 times, we were able
                        to implement 24 carriage return character and 24 newline
                        character using these interrupt 16.
                        
  printScreen function: To decide which path we wanted our char string to go, we
                        used an if/else path. If the parameter that was passed into
                        D was a 1, then it would print our char string to the print.out
                        file, else it would print to the display. We did this with two
                        different interrupts (16 , 23).
                        
 Interrupt 33/handleInterrupt21: In this function, we used a switch statement that would
                        take in the parameter from the initial interrupt 33 in main.
                        Currently we have only one switch case (0) for which we call the
                        printString function and pass the char string and parameter for D.
                        We also have a default case for any error case errors.
                        
Additionally, an additional script, runOS.sh, is included to invoke the Bochs emulator as a shortcut.

-- Josh Newman, Andy Weaver 1/31/2020
