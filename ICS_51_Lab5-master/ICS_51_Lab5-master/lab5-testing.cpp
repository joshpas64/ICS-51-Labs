#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <iomanip>

#include "lodepng.h"

// These functions should be implemented in lab5.cpp
void imageThresholding(unsigned char* buffer, int dim);
void imageFlip(unsigned int* image, int dim);
void imageFilter3x3(unsigned char* image_int, int image_dim, int* filter, int dive, unsigned char* image_out);
extern char *yourName;
extern char *yourStudentID;

int main() {
	int i, j;

	std::cout << "Your Name: " << yourName << std::endl << "Your Student ID: " << yourStudentID << std::endl;


#define TEST_P1 1
#define TEST_P2 1
#define TEST_P3 1

	std::vector<unsigned char> png;
	std::vector<unsigned char> image;
	std::vector<unsigned char> image2;
	unsigned int width, height;
	lodepng::State state;
	std::string filename, outFilename;
	
#if TEST_P1
	// Part 1 tests
	unsigned char testStr0[3][3] = { {3,   30,  60},
									 {90,  120, 150},
									 {180, 210, 240} };

	unsigned char exptectedStr0[3][3] = { {0,   0,   0},
										  {0,   0,   255},
										  {255, 255, 255} };
  
	imageThresholding(&testStr0[0][0], 3);

	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j) {
			if (testStr0[i][j] != exptectedStr0[i][j]) {
				std::cout << "Part 1: Test 1 failed at index: " << i << "," << j << " got: " << int(testStr0[i][j]) << " expected: " << int(exptectedStr0[i][j]) << std::endl;
				break;
			}
		}
	if (i*j == 9)
		std::cout << "Part 1: Test 1 passed." << std::endl;

	unsigned char testStr1[4][4] = {{0,   30,  90,  120},
									{127, 45,  130, 60},
									{127, 128, 0,   130},
									{127, 228, 255, 255 }};
	unsigned char exptectedStr1[4][4] = {{0, 0,   0,   0},
	                                     {0, 0,   255, 0 },
										 {0, 255, 0,   255},
										 {0, 255, 255, 255 }};

	imageThresholding(&testStr1[0][0], 4);
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j) {
			if (testStr1[i][j] != exptectedStr1[i][j]) {
				std::cout << "Part 1: Test 2 failed at index: " << i << "," << j << " got: " << (unsigned int)testStr1[i][j] << " expected: " <<( unsigned int)exptectedStr1[i][j] << std::endl;
				break;
			}
		}
	if (i*j == 16)
		std::cout << "Part 1: Test 2 passed." << std::endl;

	// Load a grayscale png (1Byte per pixel)
	// Make a binary image by thresholding

	filename = "lena.png";
	lodepng::decode(image, width, height, filename, LCT_GREY, 8U);

	if (image.size() == 0) {
		std::cerr << "lena.png not found. Make sure it exists in your solution directory." << std::endl;
		return -1;
	}
	assert(width == height);
	imageThresholding((unsigned char*)&image[0], width);
// When you use the actual images in your functions check your assembly functions. When manipulating data or adding offsets into 
// memory addresses dont use pointer register esi, edi, etc. because they may cause memory violation errors at runtime when using an
// actual image
	outFilename = "lena_binary.png";
	lodepng::encode(outFilename, image, width, height, LCT_GREY, 8U);
	image.clear();

	std::cout << "Check Lena_binary.png." << std::endl;
#endif

#if TEST_P2
	bool failed = false;
	// Part 2 tests
	unsigned int testStr2[3][3] = { {0x0,        0x10101010, 0x20202020},
	                                {0x30303030, 0x40404040, 0x50505050},
	                                {0x60606060, 0x70707070, 0x80808080} };


	unsigned int exptectedStr2[3][3] = { {0x20202020,  0x10101010, 0x0},
                                         {0x50505050,  0x40404040, 0x30303030},
                                         {0x80808080,  0x70707070, 0x60606060} };

	imageFlip(&testStr2[0][0], 3);
	
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j)	{
			if (testStr2[i][j] != exptectedStr2[i][j]) {
				std::cout << std::hex << "Part 2: Test 1 failed at index: "<< i<< ","<< j << " got: " << testStr2[i][j] <<" expected: " << exptectedStr2[i][j]<<  std::endl;
				failed = true;
			}
		}
	if (!failed)
		std::cout << "Part 2: Test 1 passed." << std::endl;


	unsigned int testStr2_1[4][4] = { { 0, 1,   2,  3 },
										{ 4, 5,   6,  7 },
										{ 8, 9,  10, 11 },
										{ 12, 13, 14, 15 } };

	unsigned int exptectedStr2_1[4][4] = { { 3,  2, 1, 0 },
											{ 7,  6, 5, 4 },
											{ 11, 10, 9, 8 },
											{ 15, 14, 13, 12 } };
	failed = false;
	imageFlip(&testStr2_1[0][0], 4);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (testStr2_1[i][j] != exptectedStr2_1[i][j]) {
				std::cout << "Part 2: Test 2 failed at index: " << i <<","<<j<< " got: " << (unsigned int)testStr2_1[i][j] << " expected: " << (unsigned int)exptectedStr2_1[i][j] << std::endl;
				failed = true;
			}
		}
	}
	if (!failed)
		std::cout << "Part 2: Test 2 passed." << std::endl;


	// Load a RGBA png (4-Bytes per pixel)
	// Rotate it to left
	filename = "lena_color.png";
	lodepng::decode(image, width, height, filename, LCT_RGBA, 8U);
	if (image.size() == 0) {
		std::cerr << "lena_color.png not found. Make sure you have this file in your solution directory." << std::endl;
		return -1;
	}
	assert(width == height);

	imageFlip((unsigned int*)&image[0], width);
	

	outFilename = "Lena_flipped.png";
	lodepng::encode(outFilename, image, width, height, LCT_RGBA, 8U);
	
	std::cout << "Check Lena_flipped.png." << std::endl;
#endif

#if TEST_P3


	unsigned char testStr3_1[4][4] = { { 0, 1,   2,  3 },
										{ 4, 5,   6,  7 },
										{ 8, 9,  10, 11 },
										{ 12, 13, 14, 15 } };
	int mask3_1[9] = { 0, 0, 0, 0, 4, 0, 0, 0, 0 };
	int mask3_2[9] = { 0, 1, 0, 0, 1, 0, 0, 1, 0 };
	unsigned char resStr3_1[4][4];
	unsigned char resStr3_2[4][4];

	unsigned char exptectedStr3_1[4][4] = { { 0, 1,   2,  3 },
										{ 4, 5,   6,  7 },
										{ 8, 9,  10, 11 },
										{ 12, 13, 14, 15 } };
	unsigned char exptectedStr3_2[4][4] = { { 4,  7, 10, 13 },
											{ 12, 15, 18, 21},
											{ 24, 27, 30, 33},
											{ 32, 35, 38, 41}};

	imageFilter3x3(&testStr3_1[0][0], 4, mask3_1, 4, &resStr3_1[0][0]);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (resStr3_1[i][j] != exptectedStr3_1[i][j]) {
				std::cout << "Part 3: Test 1 failed at index: " << i << "," << j << " got: " << (unsigned int)resStr3_1[i][j] << " expected: " << (unsigned int)exptectedStr3_1[i][j] << std::endl;
				failed = true;
			}
		}
	}
	if (!failed)
		std::cout << "Part 3: Test 1 passed." << std::endl;


	imageFilter3x3(&testStr3_1[0][0], 4, mask3_2, -1, &resStr3_2[0][0]);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (resStr3_2[i][j] != exptectedStr3_2[i][j]) {
				std::cout << "Part 3: Test 1 failed at index: " << i << "," << j << " got: " << (unsigned int)resStr3_2[i][j] << " expected: " << (unsigned int)exptectedStr3_2[i][j] << std::endl;
				failed = true;
			}
		}
	}
	if (!failed)
		std::cout << "Part 3: Test 2 passed." << std::endl;

	image.clear();
	image2.clear();
	filename = "lena.png";
	lodepng::decode(image, width, height, filename, LCT_GREY, 8U);
	image2.resize(width*height * 1);
	if (image.size() == 0) {
		std::cerr << "lena.png not found. Make sure you have this file in your solution directory." << std::endl;
		return -1;
	}
	assert(width == height);

	int mask[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
	imageFilter3x3((unsigned char*)&image[0], width, mask, 16, (unsigned char*)&image2[0]);
	outFilename = "Lena_blurred.png";
	lodepng::encode(outFilename, image2, width, height, LCT_GREY, 8U);
	std::cout << "Check Lena_blurred.png." << std::endl;

	int mask2[9] = {0, 0, 0, 0, 1, 0, 0, 0, 0 };
	imageFilter3x3((unsigned char*)&image[0], width, mask2, 1, (unsigned char*)&image2[0]);
	outFilename = "Lena_unchanged.png";
	lodepng::encode(outFilename, image2, width, height, LCT_GREY, 8U);
	std::cout << "Check Lena_unchanged.png." << std::endl;


	int mask3[9] = { 0, 1, 0, 1, 1, 1, 0, 1, 0 };
	imageFilter3x3((unsigned char*)&image[0], width, mask3, 5, (unsigned char*)&image2[0]);
	outFilename = "Lena_dilate.png";
	lodepng::encode(outFilename, image2, width, height, LCT_GREY, 8U);
	std::cout << "Check Lena_dilate.png." << std::endl;

	int mask4[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
	imageFilter3x3((unsigned char*)&image[0], width, mask4, 1, (unsigned char*)&image2[0]);
	outFilename = "Lena_sharpen.png";
	lodepng::encode(outFilename, image2, width, height, LCT_GREY, 8U);
	std::cout << "Check Lena_sharpen.png." << std::endl;


	int mask5[9] = { 0, 1, 0 , 1, -4, 1, 0 ,1 ,0};
	imageFilter3x3((unsigned char*)&image[0], width, mask5, 1, (unsigned char*)&image2[0]);
	outFilename = "Lena_edges.png";
	lodepng::encode(outFilename, image2, width, height, LCT_GREY, 8U);
	std::cout << "Check Lena_edges_x.png." << std::endl;


	int mask6[9] = { 2, 0, 2, 0, 0, 0, 2, 0, 2 };
	imageFilter3x3((unsigned char*)&image[0], width, mask6, 8, (unsigned char*)&image2[0]);
	outFilename = "Lena_erode.png";
	lodepng::encode(outFilename, image2, width, height, LCT_GREY, 8U);
	std::cout << "Check Lena_erode.png." << std::endl;

#endif
	return 0;
}
