//********************************
// Header:			palindromeChk
// File Name: 	main.c
// Authors:			Emmanouil Christos	8804 / Exarchou Dimitrios - Marios 8805
// Date:				16-Apr-20
//********************************

__asm int palindromeChk(const char *str)
{	
		PUSH	{r4-r6,lr}			// Prolog
	
		MOV		r4, #1					// Set flag to 1. (1 Palindrome, 0 nonPalindrome)
		MOV		r5, #0					// Initialize front pointer to r5.
		MOV		r6, #0					// Initialize back pointer to r6.
	
step1											// Find the size of the word and put the value in back counter.
		
		LDRB	r1,	[r0, r6]		// Load the char that is stored in the memory address (value of r0 + r6) to r1. In this compiler a char has a size of a byte.
		CMP		r1, #0					// Check if that has the end of the string array.
		BEQ		step2						// If YES go to step2.
		ADD		r6, r6, #1			// Increase back pointer.
		B		step1							// Repeat.

step2											// Main compare routine.
		
		SUB 	r6, r6, #1			// Decrease back pointer.
		CMP		r5, r6					// Compare pointers.
		BGE		step4						// If r5 >= r6 goto step3.
		LDRB	r1, [r0, r5]		// Load front char.
		LDRB	r2, [r0, r6]		// Load back char.
		CMP 	r1, r2					// Compare anti-diametric chars.
		BNE		step3						// If NOT equal go to step3.
		ADD		r5, r5, #1			// Increase front pointer.
		B		step2							// Repeat.
		
step3											// If word not Palindrome.
		
		MOV		r4, #0					// Set flag to 0.
		
step4

		LDR		r5,	=0x20000000	// Load memory address to r5.
		STR		r4, [r5]				// Store r4 to memomry address.
		MOV		r0, r4					// Move result ro r0.		
		POP		{r4-r6,pc}			// Epilog.
		
		BX		lr							// Return.
}

int main(void)
{
	const char string2check[] = "abcba";
	int chkResult = palindromeChk(string2check);
	
	while(1);
}

