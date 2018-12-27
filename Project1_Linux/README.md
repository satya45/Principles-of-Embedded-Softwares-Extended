# Principles of Embedded Software

This report has comprehensively covered all the command descriptions, project plan and the time taken to complete the project as compared to the estimated time, a test case
and answers to all the report questions. 
In order to replace the if else structure, extensible use of function pointers have been incorporated in the project. Lookup Tables have been created in order to solve this issue.
Different header and source files have been created to support modularity ,modification, adding additional commands and features.
This project has covered all the error controls and bound checks as deemed necessary. For example if the user inputs a wrong hexadecimal value of a memory location the program displays “invalid memory location” and asks again to input for the memory location.
In addition to this if the offset input is beyond the allocated memory or if the 32 bit word is more than the memory is allocated , it displays a message “invalid offset”/”invalid words” and asks the user to input the parameters again.


The Following are the syntax to invoke different functions :
1. help- Help function displays all the available commands fro the user to input in order to invoke different functions described in the help menu.
2. allocate - The user specifies number of 32 bit word to allocate a memory block.
3. write -The user specifies offset or memory location where 32 bit hexadecimal data can be written into it.
4. display- The user specifies an offset or memory location of the contents that needs to be displayed.
5. writetime- The user specifies offset or memory location,number of words to be written starting from the base address and seed value to generate a pseudo random number and writes the value of the pseudo random number generated to the specified memory location and returns the execution time of the command.
6. verifytime- The user can verify the pseudo random number generated using the writetime command and returns the execution time of the command. The inputs required from the user for this command are offset or memory location,number of words to be written starting from the base address and seed value.
7. free- this function is used to free up the memory block.
8. ex- Exits the application.
9. main- Gives control on all the functions listed above.