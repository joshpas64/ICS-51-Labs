
//
// Your name and 
// Your Student ID
char *yourName = "Joshua Pascascio";
char *yourStudentID = "52192782";


// This function should take an grayscale square image and it.
// Each pixel is represented by one byte and image is of dim*dim dimension.
//
// //4 + 4 + 4 + 4 = 16 = 4^2 so just get x and add it (x-1) times

//Helpful later on
//Data: eax,ebx,ecx,edx
//Index and ptr: esi ,edi, ebp, eip, esp (stack ptr counter push -> esp = esp - 4??)
//Segment (For more dynamically allocated storage or for objects with less contigous
//	       data members: CS, DS, ES, FS, GS, SS
void imageThresholding(unsigned char* image, int dim) {
	__asm {
		//with larger or more dynamic data types it may follow this model 
		/*
		move memory ptr(object) to register
		make changes to register <-- This may need to be done multiple iterations depending on complexity of object
		(i.e. 
		1. mov eax,image 1st part [outer]
		2. mov dl, [eax] [inner level 1]
		--- Do processing on dl changing its values----
		3. mov [eax], dl [return from inner level 1]
		4. mov image, eax [return from outer]
		move register back to ptr(object)
		*/
		/// when i iterated (dim^2 - 1) and used esi  but 
		
			mov ebx, image;
			mov esi, 0; 
			mov eax, 0;
			mov ecx, dim;
			mov edx , 0;
		MULT: //find dim * dim
			cmp edx, dim; //since the indices arent relevant to the core function, we can just iterate 
				      // through dim * dim times instead of this:
				      /* 
				      for (int i =0; i < dim; i++)
				      	for(int j = 0; j < dim; j++)
				      */
			jge RESET;
			add eax, ecx;
			inc edx;
			jmp MULT;
		RESET:
			mov dim, eax; //make dim * dim the new bound limit
		ENDMULT:
			mov ecx, 0; //eax al , ebx bl, ecx cl, edx dl
			mov edx, 0;
			mov eax, 0;
			cmp esi, dim; // when doing iteration its usually best to use esi, or edi but not necessary
			jge DONE_FOR; //dim is now dim = (original) dim^2
			add eax, esi;
			mov cl, [ebx + eax]; //Remember the array is an array of char's not int's
			// cl is the lowest 8 bit (char - 1byte) register in ecx			10000101 ---  011111111
			mov dl, 0x80;    //76 'A'     // cmp cl, 0x80 --> 10000000 ---> 1000000  -> 00000000
			and dl, cl;           //output will always be wrong
		/*
			When using char's as your values remember that they not only denote values numerically, 
			but also actual characters like letters in an ASCII table, so compare char1 to char2 might compare
			their symbol values like 'A' and '?' or numerical like 12 and 14
			use bitmasking to compare since it uses only their numerical values represented as bit strings
		*/
			cmp dl, 0x00;
			jne MAKE_BRIGHT;
			mov cl, 0x00;
			jmp ASSIGN_PIXEL;
		MAKE_BRIGHT:
			mov cl, 0xFF;
		ASSIGN_PIXEL:
			mov [ebx + eax], cl; // If moving the value directly to an address in memory doesnt work
					     // mov that value into a register, then move that register to the memory addr
			inc esi;
			jmp ENDMULT;
		DONE_FOR:
			mov image, ebx; //mov all changes put in ebx back into the original parameter
	//	////////////// Your code ends here ///////////////////////// */
	}
}


// This function flips a given squared iamge with given dimension size horizontally.
//
// Two variables are definde to help you with the implemetanion.
// NOTE: you can't define additional variables. m[i][j] ==
//
void imageFlip(unsigned int* image, int dim) { 
	//The following comment lines are psuedocode and layout of the algorithm I would use before I started
	//coding. It makes actual implementation much easier. 
	// Note however if you are going to do something new or use data structures or certain functions you may want to test them in
	// a exp project before implementing your entire project
	// Example: Program uses a class, may want to test the functionality of class and member functions before testing the whole
	// program
	
	
	// dim is col width indexes is 0 - (dim - 1)  integer === 4 bytes
	// ADDRESS == BASE (eax) + (row) * (dim) + (col * 4) --> (BASE) + (ROW)*(DIM) + (shr [col], 2 )      1100
	/////// Scratch work: [10 = 1010], 3 -- 0 + 3 = 0011, 10 - 1 - 3-> 6 = 0110 ; [12 = 1100], 5 0 + 5 = 0101, 12 - 1 - 5 = 6 0110; [16], 3-> 10000 00011 -> 16 -3 -1 12 -- 1100
	// Point is x places to the RIGHT from 0 ----> Now will be x places to the LEFT from (dim - 1)       
	// calculate from the midpoint of each row        
	// loops a total of dim times (outer loop_
	// Each iteration (for  each row)
	// (FOR each column)(the terminating index is dim/2 [i.e. mov ebx, dim; shr ebx, 1;])
	// Base addr will always be [eax] i.e first mov eax, image
	// mov val from location [r][x] into R1
	// mov val from location [r][dim - 1 - x] into R2
	// BUILT IN SWAP function???
	// mov R3, R2
	// mov R2, R1
	// mov R1, R3
	// mov [r][x] , R2
	// mov [r][dim - 1 - x] , R1
	// repeat for next column pair
	// repeat for next row
	// move back i.e. mov image, eax;
	// needed : 4 registers ... 3 ?
	// granted two local memory variables
	// row, col var's
	// mid point vars
	// maybe two vars to denote the two different columns to be swapped 
	// col is in eax;
	// edx is baseaddr never going to be changed. 
	// start mov ebx, dim;
	// shr ebx, 1;
	// mov var2, ebx;
	// ecx makes col width * row initialized with mov ecx,0
	// ebx counts
	// cmp ebx, dim -----> add ecx, row [index ptr: edi](first part same as last fn)
	// leave ecx alone for now
	// now that this is done, ebx and edx avail see what else is needed; -> mov ebx, 0 mov edx,0
	// will have only two real registers to mess with since one will hold data, the others are for holfing addresses
	// mov ebx, 0
	// add ebx, esi
	// add ebx, ecx
	// mov edx, [eax + ebx*4] edx has mem val. ** (maybe since addressing is tedious maybe var1 and var2 should hold data?)
	// 
	// once done maybe mov ebx 
	// first use index ptr for col [esi] 
	// Values that are needed but dont need to be changed or processed much (dim, dim/2)[can use addr ptr's esi and edi tho]
	// use variables for column offsets; 


	unsigned int a_p, a_p_m; 
	__asm { 
		//a_p original pixel
		// a_p_m modified pizel
		//////////// Your code begins here ////////////////////
		mov eax, image;
 // Maybe keep ebx;
		mov esi, 0;
	ITER_ROW:
		cmp esi, dim;
		jge RETURN_IMAGE;
		mov edi, 0;
	INNER_FOR:
		mov ebx, dim; // since two columns are being modified each iteration only dim/2 iterations are needed for each row
		shr ebx, 1; // make ebx = dim / 2 
		cmp edi, ebx; //dim/2
		jge END_INNER;
		mov edx, 0;
		mov ecx, 0;
	GET_ROW_WIDTH:
		cmp ecx, dim;
		jge PRODUCT;
		add edx, esi;
		inc ecx;
		jmp GET_ROW_WIDTH;
	PRODUCT: // 4 ., dim - i
		mov ecx, edx;
		add ecx, edi;
		mov a_p, ecx; //store address offsets of each value you wish to modify in the local variables
		mov edx, dim;
		sub ecx, edi;
		sub edx, edi; // new col == col: x ; new column = dim -x -1
		sub edx, 1;
		add ecx, edx;
		mov a_p_m, ecx;
		mov ecx, a_p; // Use a_p and a_p_m with registers as temp values to perform swap functions
		mov edx, [eax + ecx * 4];
		mov ecx, a_p_m;
		mov ebx, [eax + ecx * 4]; // When doing address offsets only registers can be used not memory variables
					  // [eax + a_p_m*4] not valid
		mov[eax + ecx * 4], edx;
		mov ecx, a_p;
		mov[eax + ecx * 4], ebx; // values are swappped
		inc edi;
		jmp INNER_FOR;
	END_INNER:
		inc esi;
		jmp ITER_ROW; //go to next row
	RETURN_IMAGE:
		mov image, eax; // return modified image
		//////////// Your code ends here ////////////////////
	}

}

// This function implements convolution using 3x3 kernels. 
// You can assume that space for image_out is already allocated.
//
// Four variables are definde to help you with the implemetanion.
// NOTE: you can't define additional variables.
//
void imageFilter3x3(unsigned char* image_in, int image_dim, int* filter, int dive, unsigned char* image_out) {
	int temp1, temp2, temp3, temp4; // these are chars may need cl,bl and bitmask use!!!!!!!!!
	/*
	Example  
	a0 a1 a2 a3 a4 a5 a6            i0 i1 i2       
	b0 b1 b2 b3 b4 b5 b6            j0 j1 j2   
	c0 c1 c2 c3 c4 c5 c6	        k0 k1 k2
	d0 d1 d2 d3 d4 d5 d6
    e0 e1 e2 e3 e4 e5 e6
	f0 f1 f2 f3 f4 f5 f6
	g0 g1 g2 g3 g4 g5 g6
	*/
	// C++ code;
	// matrix[n][n], n , filter[3][3], div, image*out 
	/*
	mov eax, image_out;
	mov temp4, eax;
	mov esi,0;
	mov temp1, 0;
	for(int i = 0; int < dim; i++) 
	{
	OUTER:
		cmp esi, dim;
		jge FINISHED;
		mov edi, 0;
		mov ecx, esi;
		mov temp1, ecx;
		for(int j = 0; j < dim ; j++)
		{
		INNER:
			cmp edi, dim;
			jge END_INNER;
			mov ecx, 0;
			mov esi, 0;
			mov ecx, edi;
			mov temp2, ecx;
			mov temp3, 0;
			for(int k = 0; k < 3; k++)
			{
			OUTER_CONV:
				cmp esi, 3;
				jge END_OUTER_CONV;
				mov edi, 0;
				for(int m=0; m < 3; m++)
				{
				INNER_CONV:
					cmp edi, 3;
					jge END_INNER_CONV;
					mov ebx, esi;
					add ebx, esi;
					add ebx, esi;
					add ebx, edi;
					mov ecx, filter;
					mov al, [ecx + ebx*4]
					//if statements
					mov edx, temp1;
					sub edx , 1;
					add ebx, esi;
					cmp edx, 0;
					jl ADJUST_X_0
					cmp edx, dim;
					jge ADJUST_X_HIGH;
					jmp CONT;
					ADJUST_X_HIGH:
						mov edx, dim;
						sub edx, 1;
						jmp CONT;
					ADJUST_X_0:
						mov edx, 0;
						jmp CONT;
					CONT:
						mov ebx, 0;
						mov ecx, 0;
					MULT:
						cmp ecx, dim;
						jge END_MULT;
						add ebx, edx;
						inc ecx;
						jmp MULT;
					END_MULT:
						mov ecx, temp2;
						sub ecx, 1;
						add ecx. edi;
						cmp ecx, 0;
						jl ADJUST_Y_0;
						cmp ecx, dim;
						jge ADJUST_Y_HIGH;
						jmp CONT2;
					ADJUST_Y_0:
						mov ecx, 0;
						jmp CONT2;
					ADJUST_Y_HIGH;
						mov ecx, dim;
						sub ecx, 1;
						jmp CONT2;
					CONT2:
						add ebx, ecx;
						mov edx, image_in;
						mov cl, [edx + ebx * 4];

					mul cl;
					mov bl, div;
					div bl;
					mov ecx, temp3
					add ecx, eax;
					mov temp3, ecx;
					inc edi;
					jmp INNER_CONV;
				}
			END_INNER_CONV;
				inc esi;
				jmp OUTER_CONV;
			}
		END_OUTER_CONV:
			mov ecx, 0;
			mov edx, 0;
			mov ebx, temp1; //original row
		MULT2:
			cmp ecx, dim;
			jge END_MULT2;
			add edx, ebx;
			inc ecx;
			jmp MULT2;
		END_MULT2:
			mov ecx, temp2; // original column
			add edx, ecx;
			mov eax, temp3; //convolution value
			mov ebx, temp4;
			mov [ebx + edx * 4], al;
			mov temp4, ebx;
			mov ecx, temp2;
			inc ecx;
			mov edi, ecx;
			jmp INNER;
		}
	END_INNER:
		mov ecx, temp1;
		inc ecx;
		mov esi, ecx;
		jmp OUTER;
	FINISHED:
		mov eax, temp4;
		mov image_out,eax;
	}
	*/

	__asm {
		//////////// Your code begins here ////////////////////
		mov eax, image_out;
		mov temp4, eax;
		mov esi, 0;
		mov temp1, 0;
		OUTER:
			cmp esi, image_dim;
			jge FINISHED;
			mov edi, 0;
			mov ecx, esi;
			INNER:
				cmp edi, image_dim;
				jge END_INNER;
				mov ecx, 0;
				mov esi, 0;
				mov ecx, edi;
				mov temp2, ecx;
				mov temp3, 0;
				OUTER_CONV:
					cmp esi, 3;
					jge END_OUTER_CONV;
					mov edi, 0;
					INNER_CONV:
						cmp edi, 3;
						jge END_INNER_CONV;
						mov ebx, esi;
						add ebx, esi;
						add ebx, esi;
						add ebx, edi;
						mov ecx, filter;
						mov eax, [ecx + ebx]
							//if statements
						mov edx, temp1;
						sub edx, 1;
						add ebx, esi;
						cmp edx, 0;
						jl ADJUST_X_0
							cmp edx, image_dim;
						jge ADJUST_X_HIGH;
						jmp CONT;
					ADJUST_X_HIGH:
						mov edx, image_dim;
						sub edx, 1;
						jmp CONT;
					ADJUST_X_0:
						mov edx, 0;
						jmp CONT;
					CONT:
						mov ebx, 0;
						mov ecx, 0;
					MULT:
						cmp ecx, image_dim;
						jge END_MULT;
						add ebx, edx;
						inc ecx;
						jmp MULT;
					END_MULT:
						mov ecx, temp2;
						sub ecx, 1;
						add ecx, edi;
						cmp ecx, 0;
						jl ADJUST_Y_0;
						cmp ecx, image_dim;
						jge ADJUST_Y_HIGH;
						jmp CONT2;
					ADJUST_Y_0:
						mov ecx, 0;
						jmp CONT2;
					ADJUST_Y_HIGH:
						mov ecx, image_dim;
						sub ecx, 1;
						jmp CONT2;
					CONT2:
						add ebx, ecx;
						mov edx, image_in;
						mov ecx, [edx + ebx];
						mul ecx;
						mov ebx, dive;
						div ebx;
						mov ecx, temp3
						add ecx, eax;
						mov temp3, ecx;
						inc edi;
						jmp INNER_CONV;
					END_INNER_CONV:
					inc esi;
					jmp OUTER_CONV;
			END_OUTER_CONV:
				mov ecx, 0;
				mov edx, 0;
				mov ebx, temp1; //original row
			MULT2:
				cmp ecx, image_dim;
				jge END_MULT2;
				add edx, ebx;
				inc ecx;
				jmp MULT2;
			END_MULT2:
				mov ecx, temp2; // original column
				add edx, ecx;
				mov eax, temp3; //convolution value
				mov ebx, temp4;
				mov[ebx + edx ], eax;
				mov temp4, ebx;
				mov ecx, temp2;
				inc ecx;
				mov edi, ecx;
				jmp INNER;
		END_INNER:
			mov ecx, temp1;
			inc ecx;
			mov esi, ecx;
			jmp OUTER;
		FINISHED:
			mov eax, temp4;
			mov image_out, eax;
		////////////// Your code ends here /////////////////////////
	}
}
