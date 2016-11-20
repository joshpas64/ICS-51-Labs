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
	add ax, 1;  ax = 256
	; AX=0x100  SF=0x00   ZF=0x00  CF=0x00
	sub ax,1	
	; AX= 0xFF SF=0x00  ZF=0x00  CF=0x00
	add al,1	
	; AL = 0x00'\0'   SF=0 ZF=0  CF=0x01
	mov al,2
	sub al,3	
	; AL = 0xFF   SF=0x01  ZF=0 CF=0x01
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
	;After idiv: DX = 0xFF,  AX = 0x7D
	mov eax,00128765h
	mov ecx,10000h
	mul ecx 
	;After mul: EDX = 0x12, EAX = 0x87650000 ,CF = 0x01
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
	 mov eax, inpStr;
	 mov ebx, outStr;
	 mov esi, 0;
	 mov edi, 0;
	 mov ecx, 0;
	ITER_STR:
		mov ecx, 0;
		add ecx, esi;
		mov dl,[eax + ecx]; 
		cmp dl,0;
		je DONE;
		inc esi;
		cmp dl, 48;
		jge KEEP_CHECK;
		jmp ITER_STR;
	KEEP_CHECK:
		cmp dl, 57;
		jle PUT_IN;
		cmp dl, 64;
		jle ITER_STR;
		cmp dl, 90;
		jle PUT_IN;
		cmp dl, 95;
		je PUT_IN;
		cmp dl, 96;
		jle ITER_STR;
		cmp dl, 122;
		jle PUT_IN;
		jmp ITER_STR;
	PUT_IN:
		mov ecx, 0;
		add ecx, edi;
		mov [ebx + ecx], dl;
		inc edi;
		jmp ITER_STR;
	DONE:
		mov ecx, 0;
		add ecx, edi;
		mov [ebx + ecx], dl;
		mov outStr, ebx;
	 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	 ; Your code ends here
	 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	 


	ret
part3 ENDP

END
