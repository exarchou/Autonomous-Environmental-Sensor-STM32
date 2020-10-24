# Project 1: Palindrome Sequence

The purpose of this report is to describe - explain the code implemented for the first project. The aim of this work is to create a routine that checks whether a sequence of chars (string) is palindrome or not.



## Implementation

The **STM32F401RE microcontroller (ARM Cortex-M4)** and the tools of **Keil**, CMSIS Core and Device Startup were used to complete the task. In addition, **ARM Compiler 5 and ST-Link Debugger** were used. A program was developed in **C and ARM assembly**, something that was possible thanks to compiler and was achieved due to the embedded assembler.



> #### main

Initially in the main routine the alphanumeric is initialized and the routine that examines the palindrome of the string is called, the result of which returns to an integer variable. Note that the alphanumeric input is done exclusively by changing the string inside the code.



> #### palindromeChk

The routine that performs the test is implemented using ARM assembly. The function takes as input the pointer of a character and returns an integer 1 or 0 if the string under consideration is palindrome or not respectively. In the code the preserved registers r4, r5 and r6 are used and in the prolog of the function they are added to the stack. R4 has the role of flag that carries the result of the test, is initialized to the value 1 and under appropriate conditions can change its value to 0. R5 and r6 are counters and are initialized to the value 0. The first step of the routine is to find the string size. It achieves this with an iterative process. Note that r0 is the register in which the memory address of the first character of the string is stored when the function is called. In each iteration the contents of the memory are loaded in r1 with address r0 + r6 and it is checked if it corresponds to the end of the string. If so, the routine goes to the next step otherwise it increases the value of r6 by one. At the end of the iteration r6 contains the size of the string.

The next step is to check the palindrome. This is a repetition. R5 and r6 are two string pointers, r5 indicates at the beginning and r6 at the end. If r5 and r6 point to the same position (odd string size) or r5 points to position greater than r6 (even string size), this means that all symmetric characters have been checked, the string is palindrome and the iteration can be stopped to go the routine in the last step. If during the comparison of two symmetrical characters an inequality is found then the repetition is stopped again with the difference that now the routine changes the value of r4 to 0 and then goes to the last step. In the last step of the function the selected address is loaded in r5, the result (r4) is saved in this address, the result is transferred to r0 to return to main, the r4, r5, r6 are removed from the stack and the normal flow is returned of the program, outside the palindromeChk routine. Note that the address 0x20000000 was selected.



## Testing

The function was checked by initializing different strings in the main and observing the value of r0 before returning from palindromeChk and the contents of the selected memory address via the debugger. The table below presents the various alphanumerics that were put to the test and the corresponding results proving the correct operation of the program.



|  String  | Length(r6) |        Condition to exit step2        |  r0  | [ 0x20000000 ] |
| :------: | :--------: | :-----------------------------------: | :--: | :------------: |
| ‘abccba’ |     6      |  (r5 = 3) >= (r6 = 2) -> T -> step4   |  1   |   0x00000001   |
| ‘abccda’ |     6      | (r1 = ‘b’) = (r2 = ‘d’) -> F -> step3 |  0   |   0x00000000   |
| ‘abcba’  |     5      |  (r5 = 2) >= (r6 = 2) -> T -> step4   |  1   |   0x00000001   |
| ‘a0b0a’  |     5      |  (r5 = 2) >= (r6 = 2) -> T -> step4   |  1   |   0x00000001   |
|   ‘a’    |     1      |  (r5 = 0) >= (r6 = 0) -> T -> step4   |  1   |   0x00000001   |
|    ‘’    |     0      |  (r5 = 0) >= (r6 = -1) -> T -> step4  |  1   |   0x00000001   |



where T = True and F = False.

Note: 0 at ASCII is 0x30.



## Conclusion

It is observed that the empty string and the string consisting of one character are considered as palindromes.