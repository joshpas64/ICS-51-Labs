#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


// These functions should be implemented in lab3.c
extern void vectorOperations(int number_of_elements, int *first_array, int *second_array, int *operation_array, int *output_array);
extern unsigned gcd(unsigned int m, unsigned int n);
extern unsigned fibonacci(unsigned n);

void test_vectorOperations();
void test_gcd();
void test_fibonacci ();

extern char *yourName;
extern char *yourStudentID;

unsigned int num_of_tests = 0;
unsigned int num_of_tests_passed = 0;

int main(void)
{
	 // Once you are done implementing the required functions, enable the testcases
	#define TEST_PART1 1
	#define TEST_PART2 1
	#define TEST_PART3 1
	printf("ICS 51, Lab 3 \nName: %s\nStudent ID: %s\n\n", yourName, yourStudentID);

#if TEST_PART1
	printf("====================== PART1: Vector Operations ======================\n");
	test_vectorOperations();
	printf("\n");
#endif


#if TEST_PART2
	printf("====================== PART2: GCD ======================\n");
	test_gcd();
	printf("\n");
#endif


#if TEST_PART3
	printf("====================== PART3: Fibonacci ======================\n");
	test_fibonacci();
	printf("\n");
#endif

	if (num_of_tests_passed == 0)
		printf("All %d tests failed.\n\n", num_of_tests);
	else if (num_of_tests == num_of_tests_passed)
		printf("All %d tests passed.\n\n", num_of_tests);
	else
		printf("%d out of %d tests passed.\n\n", num_of_tests_passed, num_of_tests);
	return 0;
}


int performOperation_c (int operation, int first, int second)
{
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
}

void vectorOperations_c (int number_of_elements, int *first_array, int *second_array,
                         int *operation_array, int *output_array)
{
	int i;
	for (i=0; i<number_of_elements; i++)
	{
		output_array[i] = performOperation_c(operation_array[i], first_array[i], second_array[i]);
	}
}

void test_vectorOperations()
{
	int err = 0;
	int i = 0;

	int number_of_elements = 10;
	int operation_array[] = { 1, 2, 1, 4, 1, 2, 4, 3, 3, 0 };
	int first_array[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 182 };
	int second_array[] = { -3, 14, 5674, 289, -89, 234, 54, 234, 98, 71 };
	int output_array[10];
	int expected_output_array[10];

	vectorOperations(number_of_elements, first_array, second_array, operation_array, output_array);
	vectorOperations_c(number_of_elements, first_array, second_array, operation_array, expected_output_array);

	for (i = 0; i<number_of_elements; i++) {
		if (output_array[i] != expected_output_array[i]) {
			err = 1;
			printf("Test failed at index %d: expected %d, got %d\n", i, expected_output_array[i], output_array[i]);
		}
	}

	num_of_tests++;
	if (!err) {
		printf("Test passed.\n");
		num_of_tests_passed++;
	}
}


unsigned int fibonacci_c(unsigned int n)
{
	if ( n < 2 )
		return 1;
	else
		return ( fibonacci_c(n-1) + fibonacci_c(n-2) );
}

void test_fibonacci()
{
	unsigned n = 30;
	unsigned i;
	int err = 0;
	for (i = 0; i < n; i++) {
		if (fibonacci(i) != fibonacci_c(i)) {
			err = 1;
			printf("Test failed. Fibonacci(%d): expected %d, got %d\n", i, fibonacci_c(i), fibonacci(i));
		}
	}

	num_of_tests++;
	if (!err) {
		printf("Test passed.\n");
		num_of_tests_passed++;
	}
}

unsigned int gcd_c(unsigned int m, unsigned int n)
{
	if ((m % n) == 0)
		return n;
	else
		return gcd_c(n, m % n);
}

void test_gcd() {
	int err = 0;
	int i = 0;

	int number_of_elements = 5;
	int first_array[] = {10, 45, 8, 732, 6};
	int second_array[] = {10, 20, 569, 29, 71};

	for (i = 0; i<number_of_elements; i++) {
		if (gcd_c(first_array[i], second_array[i]) != gcd(first_array[i], second_array[i])) {
			err = 1;
			printf("Test failed at index %d: expected %d, got %d\n", i, gcd_c(first_array[i], second_array[i]), gcd(first_array[i], second_array[i]));
		}
	}

	num_of_tests++;
	if (!err) {
		printf("Test passed.\n");
		num_of_tests_passed++;
	}
}
