/*
	ICS 51. Lab #7

	IMPORTATNT NOTES:

	- Noramally, the compiler adds the prologue/epilogue code for the callee. However, when the
	__declspec(naked) attribute is used, it is the programmer's responsibility to write the
	prologue/epilogue code. In this lab you need to write prologue/epilogue code sections only
	for the functions that have been declared with the naked attribute, namely:

	   + performOperation
	   + gcd
	   + fibonacci

	- You cannot define any local variable in the C code. If you need additional variables in your
	assembly code, you have to allocate space for them in the prologue of the function.

	- You are not allowed to change anything in this file except for adding your assembly code
    between the lines marked "BEGIN YOUR CODE HERE" and "END YOUR CODE HERE".

	- Remember to fill in your name, student ID below.

	- ONLY submit the lab7.c file for grading.

*/

char *yourName = "Joshua Pascascio";
char *yourStudentID = "52192782";


/***********************************************************************************************

PART 1: Vector Operation

The vectorOperations function gets as parameters 4 arrays of the same length and
the number of elements in those arrays.

For each pair of elements in first_array and second_array, it calls performOperation
and stores the returned result in the same index of output_array.

output_array[index] = performOperation(operation_array[index], first_array[index], second_array[index]).

You also need to implement the body of performOperation function according to the provided
C code.

************************************************************************************************/

__declspec(naked)
int performOperation(int operation, int first, int second)
{

	// C code to be converted to x86 assembly
	/*
	if (operation==0)
		return first + second;
	else if (operation==1)
		return first - second;
	else if (operation==2)
		return (first > second)? first : second;
	else if (operation==3)
		return (first < second)? first : second;
	else
		return first;
	*/

	__asm {
		// BEGIN YOUR CODE HERE
		// END YOUR CODE HERE
		push ebp;
		mov ebp, esp;
		sub esp, 4;
		push edi;
		push esi;
		push ebx;
		mov eax, [ebp + 8];
		mov ecx, [ebp + 12];
		mov edx, [ebp + 16];
		cmp eax, 0;
		je ADD_LINE;
		cmp eax, 1;
		je SUB_LINE;
		cmp eax, 2;
		je COMP1;
		cmp eax, 3;
		je COMP2;
		jmp DONE;
	ADD_LINE: 
		add ecx, edx;
		jmp DONE;
	SUB_LINE:
		sub ecx, edx;
		jmp DONE;
	COMP1:
		cmp ecx, edx;
		jle PROC1;
		jmp DONE;
	COMP2:
		cmp ecx, edx;
		jge PROC1;
		jmp DONE;
	PROC1:
		mov ecx, edx;
	DONE:
		mov eax, ecx;
		pop ebx;
		pop esi;
		pop edi;
		mov esp, ebp;
		pop ebp;
		ret
	}

}

void vectorOperations(int number_of_elements, int *first_array, int *second_array,
	int *operation_array, int *output_array)
{
//  C code to be converted to x86 assembly
//
//	int i;
//	for (i=0; i<number_of_elements; i++)
//	{
//	    output_array[i] = performOperation(operation_array[i], first_array[i], second_array[i]);
//	}
//

	__asm {
		// BEGIN YOUR CODE HERE
		mov edi, number_of_elements;
		mov esi, 0;
		mov ecx, first_array;
		mov edx, second_array;
		mov eax, operation_array;
		mov ebx, output_array;
	START_LOOP:
		cmp esi, edi;
		jge DONE;
		push edx;
		push ecx;
		push eax;
		mov edx, dword ptr[edx + esi * 4];
		mov ecx, dword ptr[ecx + esi * 4];
		mov eax, dword ptr[eax + esi * 4];
		push edx;
		push ecx;
		push eax;
		call performOperation;
		add esp, 12;
		mov dword ptr[ebx + esi * 4], eax;
		pop eax;
		pop ecx;
		pop edx;
		inc esi;
		jmp START_LOOP;
	DONE:
		mov output_array, ebx;
		
		// END YOUR CODE HERE
	}
}


/***********************************************************************************************

    PART 2: Dijkstra's Algorithm to calculate GCD.


	Implement two functions that calculates the greatest common divisor of two input parameters.

	Given two unsigned integer number n, we can define GCD(m, n) as:


		GCD(m, n) =  n                       ,    if (m %n) == 0
				     GCD(n, m%n)             ,    if (m %n) > 0

	


************************************************************************************************/

__declspec(naked)
unsigned int gcd (unsigned int m, unsigned int n)
{

// C code to be converted to x86 assembly
//
//	if ((m % n) == 0)
//      return n;
//  else
//		return gcd(n, m % n);
//

	__asm{
		// BEGIN YOUR CODE HERE
		push ebp;
		mov ebp, esp;
		sub esp, 4;
		push edi;
		push esi;
		push ebx;
		mov eax, [ebp + 8];
		mov ecx, [ebp + 12];
		mov edx, 0;
		idiv ecx;
		cmp edx, 0;
		je TERMINATE;
		push edx;
		push ecx;
		call gcd;
		pop ecx;
		pop edx;
		jmp DONE;
	TERMINATE:
		mov eax, ecx;
		// END YOUR CODE HERE
	DONE:
		pop ebx;
		pop esi;
		pop edi;
		mov esp, ebp;
		pop ebp;
	    ret;
	}
}


/***********************************************************************************************

    PART 3: Fibonacci

	Implement a recursive function in assembly which returns the Nth number in the fibbonaci
	series (1, 1, 2, 3, 5, 8, ...).

************************************************************************************************/

__declspec(naked)
unsigned int fibonacci (unsigned int n) {

// C code to be converted to x86 assembly
/*
	if (n < 2)
		return 1;
	else
		return fibonacci(n - 1) + fibonacci(n - 2);
*/

	__asm{
		// BEGIN YOUR CODE HERE
		// END YOUR CODE HERE
		push ebp;
		mov ebp, esp;
		sub esp, 4;
		push edi;
		push esi;
		push ebx;
		mov ebx, 1;
		mov eax, [ebp + 8];
		cmp eax, 1;
		jle DONE;
		sub eax, 1;
		push eax;
		call fibonacci;
		mov ebx, eax;
		pop eax;
		sub eax, 1;
		push eax;
		call fibonacci;
		mov edx, eax;
		pop eax;
		add ebx, edx;
	DONE:
		mov eax, ebx;
		pop ebx;
		pop esi;
		pop edi;
		mov esp, ebp;
		pop ebp;
		ret;
	}
}
