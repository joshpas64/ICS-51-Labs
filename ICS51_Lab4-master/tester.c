#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

extern void doubleMax(int a, int b, int c, int *result);
extern int swapBits(int x);

extern char *yourName;
extern char *yourStudentID;
static void testcode();

int main(void)
{
	testcode();
	_getch();
	return 0;
}

static void testcode(void)
{
	int result1;
	int correct_answer;
	int *result2;

	printf("%s %s\n", yourName, yourStudentID);

#define TEST_P1 1
#define TEST_P2 1


#if TEST_P1
	printf("\nTesting part I \n");
	result1 = swapBits(0xAAAAAAAA);
	correct_answer = 0x55555555;
	printf("Input = 0x%08X, Output = 0x%08X - %s\n", 0xAAAAAAAA, result1, result1 == correct_answer ? "CORRECT" : "INCORRECT");

	result1 = swapBits(43);
	correct_answer = 23;
	printf("Input = 0x%08X, Output = 0x%08X - %s\n", 43, result1, result1 == correct_answer ? "CORRECT" : "INCORRECT");

	result1 = swapBits(0x12345678);
	correct_answer = 0x2138A9B4;
	printf("Input = 0x%08X, Output = 0x%08X - %s\n", 0x12345678, result1, result1 == correct_answer ? "CORRECT" : "INCORRECT");
#endif


#if TEST_P2
	printf("\nTesting part II \n");
	result2 = (int*)malloc(sizeof(int));
	doubleMax(1, 2, 3, result2);
	correct_answer = 8;
	printf("Input = %d, %d, %d, Output = %d - %s\n", 1, 2, 3, *result2, *result2 == correct_answer ? "CORRECT" : "INCORRECT");

	doubleMax(4, -7, -7, result2);
	correct_answer = -6;
	printf("Input = %d, %d, %d, Output = %d - %s\n", 4, -7, -7, *result2, *result2 == correct_answer ? "CORRECT" : "INCORRECT");

	doubleMax(3, 0, 0, result2);
	correct_answer = 6;
	printf("Input = %d, %d, %d, Output = %d - %s\n", 3, 0, 0, *result2, *result2 == correct_answer ? "CORRECT" : "INCORRECT");

	free(result2);
#endif




}
