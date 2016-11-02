#include <stdio.h>
#include <ctype.h>

/*
ICS 51, Lab #4

-----------------------------------------------------------------

PART I:

Given a 32-bit integer, swap all odd bits with even bits.
For example, if the given number is 23 (00010111), it should be
converted to 43 (00101011). Every even position bit is swapped
with adjacent bit on right side, and every odd position bit is
swapped with adjacent on left side.

Implementation details:
The input integer is stored in registers ebx. You need to store the
answer into register eax.

Hint:
You only need a half-dozen instructions to do this.
Think about "clearing" odd (even) bits and using shift (shl, shr)
instructions.

If we have an 8-bit number 00010111, the expected output is 00101011.
Clearing (zeroing) odd bits (7, 5, 3, 1) of 00010111 would make it
00010101. Now if we shift it to the left by one bit, it becomes
00101010. The odd bits of 00101010 are equal to the odd bits of the
expected output. They are "0 1 1 1".

Using the same technique, generate the even bits of the expected
output and then figure out a way for combining generated odd and
even bits.

-----------------------------------------------------------------

PART II:

You are given three integers. You need to add the smallest
number to the largest number and multiply that sum by two.

Implementation details:
The three integers are stored in registers eax, ebx, and ecx. You
need to store the answer into register eax.

Hint:
One way of finding minimum and maximum number is to sort the numbers.

-----------------------------------------------------------------

IMPORTATNT NOTES:

- To test your code see the "testcode" function in lab1-testing.c

- Write your assembly code only in the marked blocks.

- Do NOT change anything outside the marked blocks.

- For part II, you are NOT allowed to use any version of the
MULTIPLY instruction!

- Remember to fill in your name, student ID below.

- This lab has to be done individually.

- Submit ONLY lab4.c file for grading.

*/

char *yourName = "Joshua Pascascio";
char *yourStudentID = "52192782";

// Implement the body of this function for part I (00010111 - > 00101011
int swapBits(int x) // 8 places 4 pairs
{
	int result;
	__asm
	{
		mov ebx, x; // 00010111 shl 1  00101110 shr 1 00001011
		// Use predefined bit strings to clear val

		// YOUR CODE STARTS HERE
		mov eax, ebx;
		// The instructions clear the even bits with one instr.
		// To do this use constant bitstring with 0's in its even places and ones everywhere else
		// AND the value with this constant so you get val with no even bits because AND(0,1) == 0
		// Repeat but for odd bits
		// 10101010 10101010 101010 10101010 == 2863311530 Zero Even shift right then
		// 01010101 01010101 010101 01010101 == 178956970 Zero Odd shift left
		//Since the strings are 'zeroed' use or to concatenate them together
		// YOUR CODE ENDS HERE
		and eax, 2863311530;
		and ebx, 1431655765;
		shr eax, 1;
		shl ebx, 1;
		or eax, ebx; // Or will give the right answer because there is no real concatenation no any value
		//since one bitstring has all 0's in even place OR(0,x) will just give x
		// So OR will just combine them and give right result
		mov result, eax;
	}
	return result;

}


/* Implement the body of this function for part II*/
void doubleMax(int a, int b, int c, int *result)
{
	__asm
	{
		mov esi, result;
		mov eax, a;
		mov ebx, b;
		mov ecx, c;

		// YOUR CODE STARTS HERE
		//This one is more tricky just layout a scenario with the three possibilities
		/*
		1. (a+b) * 2
		2. (a+c) * 2
		3. (b+c) * 2
		*/
		//From there see what comparison result (i.e. a < b) tells you about the possible values for max and min
		// and jump to the right label according which will then jump to the right sum statement and jump to the end of the 
		// function.
		cmp eax, ebx;
		jge compare_2;
		cmp eax, ecx;
		jge sum3;
		add eax, ecx;
		add eax, eax;
		jmp EndOfIf;
		// YOUR CODE ENDS HERE
		// Make sure your answer is stored inside EAX
	compare_2:
		cmp ebx, ecx;
		jle sum1;
	sum1:
		add eax, ebx;
		add eax, eax;
		jmp EndOfIf;
	sum3:
		add ebx, ecx;
		add ebx, ebx;
		mov eax, ebx;
		jmp EndOfIf;
	EndOfIf:
		mov[esi][0], eax; // Another way to offset address is [baseaddr][offset] so 
		// so mov [ecx][9], ebx is the same as 
		// mov [ecx + 9], ebx , other ways can be found in x86 assembly documentation
	}
	return;
}
