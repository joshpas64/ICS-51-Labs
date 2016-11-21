INCLUDE Irvine32.inc

extern inpStr:DWORD
extern outStr:DWORD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;; Part 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.data
val1 WORD 00FFh
.code
;INVOKE printf, ADDR formatTwo, val1, val2

part1 PROC C
	mov ax, val1;
	;; val = 255 max of ax is (2^16 - 1)
	add ax, 1;  ax = 256
	; AX=0x100  SF=0x00   ZF=0x00  CF=0x00
	;; 256 < (2^16 - 1) so no overflow or carry out
	sub ax,1	
	; AX= 0xFF SF=0x00  ZF=0x00  CF=0x00
	;; once again 255 < (2^16 - 1)
	add al,1	
	; AL = 0x00'\0'   SF=0 ZF=0  CF=0x01
	;; al is 8 bit
	;; al has a maximum of 255 or (2^8 - 1)
	;; so adding 1 creates an overflow with 1 in the next 8 bit register next to al and leaving 00's in al
	;; This created a carry out to the next register meaning CF should be set to 1, or true
	mov al,2
	sub al,3	
	; AL = 0xFF   SF=0x01  ZF=0 CF=0x01
	;; in this case al is unsigned so the closest representation of -1 would 255 with SF set to true, meaning the value is negative now
	ret
part1 ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;; Part 2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.code
part2 PROC C
	mov  ax,7DFFh
	mov  dx,0;
	mov  bx,100h
	idiv bx       
	;; these registers only do integer division with remainders accounting for decimal places
	;; this division has quotient of 125 with remainder of 255
	;After idiv: DX = 0xFF,  AX = 0x7D
	;; 'A' register holds the quotient, 'D' register holds the remainder
	mov eax,00128765h
	mov ecx,10000h
	mul ecx 
	;; Very LARGE multiplication so an extra register 'D' is needed in the case of overflow 
	;; The max value of eax is (2^32 - 1)
	;; The result of this product is (18 * 2^32) + a remainder of (0x876500000h)
	;After mul: EDX = 0x12, EAX = 0x87650000 ,CF = 0x01
	;; 'D' register hold the amount that the product overflows by the next bit in this case, 18*2^32
	;; 'A' register holds the rest of the remaining product
	ret
part2 ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;; Part 3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
part3 PROC C
.data
.code
	 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	 ; Your code starts here
	 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	 push edx;
	 push eax;
	 push ebx;
	 push ecx;
	 push esi;
	 push edi;
	 ;;; To keep the parameters the same just in case they are needed later by the calling program
	 mov eax, inpStr;
	 ;;; input string
	 mov ebx, outStr;
	 ;;; output string to be formed
	 mov esi, 0;
	 ;; esi is incrementor for eax or the inputstring
	 mov edi, 0;
	 ;;;;; edi is the incrementor for the output string
	 mov ecx, 0;
	 ;;;; to add from esi, edi just to prevent any memory read error
	 ;;;; The valid characters in this case are the ASCII values 48-57, 65-90, 95, 97-122
	 ;;;; The null character in ASCII is value 0
	 ;;;; All C and C++ style strings end with a null or '\0' character
	 ;;;; once the character is hit all iteration ends and the outputstring is formed and returned
	ITER_STR:
		mov ecx, 0;
		add ecx, esi;
		;; Got to position offset from the inputstring (iterate the string char by char)
		mov dl,[eax + ecx]; 
		;;; Get the char at that position
		cmp dl,0;
		;;;; Check if you are at the end of the input string
		je DONE;
		inc esi; 
		;;;Prepare to go to the next position in the input string
		cmp dl, 48;
		;;;All valid ASCII characters are at least 48 or greater
		jge KEEP_CHECK;
		;;; If its not move to next char
		jmp ITER_STR;
	KEEP_CHECK:
		cmp dl, 57;
		;;;Valid character if between 48-57
		jle PUT_IN;
		cmp dl, 64;
		;;; Invalid if less than 65 but greater than 57
		jle ITER_STR;
		cmp dl, 90;
		;;;;; Valid if greater than 64 but less than 91
		jle PUT_IN;
		;;;; 91 - 94 are INVALID
		cmp dl, 95;
		;;;; 95 is OK
		je PUT_IN;
		cmp dl, 96;
		;;;; less than 97 but greater than 90 and not 95 is INVALID
		jle ITER_STR;
		cmp dl, 122;
		jle PUT_IN;
		;;;If greater than 96 and less than 123 it is valid
		jmp ITER_STR;
		;;;; Invalid chars including any value 123 or greater are skipped and the next char is taken from input string
		;;;PUT_IN is only reached when char's are valid if not the jmp ITER_STR will prevent the PUT_IN label from being executed
	PUT_IN:
		mov ecx, 0;
		;;;Reset ecx
		add ecx, edi;
		;;;; Find latest available position in ebx
		mov [ebx + ecx], dl;
		;;;; Move that valid char into ebx, or output string
		inc edi;
		;;; Move to next index in ebx
		;;; Check the next char in the input string
		jmp ITER_STR;
	DONE:
		mov ecx, 0;
		add ecx, edi;
		;;;;Get last position of output string
		mov [ebx + ecx], dl;
		;;; Since dl == 0 makes it terminate just mov that dl into the last index of ebx 
		;;; This is because output string must be C-Style string as well
		mov outStr, ebx;
		;;; Put ebx in outstr and reset all register with pop instruction
		pop edi;
		pop esi;
		pop ecx;
		pop eax;
		pop ebx;
		pop edx;
	 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	 ; Your code ends here
	 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	 


	ret
part3 ENDP

END
