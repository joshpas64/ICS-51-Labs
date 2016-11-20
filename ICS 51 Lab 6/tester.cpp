// main.cpp

// Older versions of the Visual C++ compiler required you
// insert a statement at the beginning of main() that
// declared and assigned a floating-point variable in order
// to load the floating-point library.

#include <stdio.h>
#include <string>
#include <strstream>
using namespace std;

extern "C" void print(char*, char*);

void print(char* name, char* id) {
	printf("Your name: %s, Your id: %s\n", name, id);
}

extern "C" void part1( );
extern "C" void part2();
extern "C" void part3();

extern "C" char* inpStr;
extern "C" char* outStr;
char * inpStr, * outStr;

int main( )
{
	
	part1();
	part2();


	inpStr = new char[100];
	outStr = new char[100];
	//Just printing my name and ID number all the rest of the code in tester.cpp and part 1 and 2 of lab6.asm is intact
	char* name = "Joshua Pascascio";
	char* id = "52192782";
	print(name, id);
	strcpy(inpStr, "TE*****ST_   -~~~1:))):(");
	part3();
	if (strcmp(outStr, "TEST_1")) {
		printf("TEST 1 Failed. Expected %s Got %s.\n", "TEST_1", outStr);
	}
	else {
		printf("TEST 1 passed.\n");
	}

	strcpy(inpStr, "!!!!T:_!_&E****ST_2###%$%#");
	part3();
	if (strcmp(outStr, "T__EST_2")) {
		printf("TEST 2 Failed. Expected %s Got %s.\n", "T__EST_2", outStr);
	}
	else {
		printf("TEST 2 passed.\n");
	}


	strcpy(inpStr, "^&%&TE*****ST_3^%%^&_");
	part3();
	if (strcmp(outStr, "TEST_3_")) {
		printf("TEST 3 Failed. Expected %s Got %s.\n", "TEST_3_", outStr);
	}
	else {
		printf("TEST 3 passed.\n");
	}

	return 0;
}