      .386
      .model flat
      .data
      .code
       PUBLIC @InvertMatrixFastCall@12
@InvertMatrixFastCall@12 PROC  
       push   ebp
       mov    ebp, esp
	   push   ebx

       mov    ebx, ecx
       mov    ecx, edx
       imul ecx, [ebp+8]
      
       c1:
        mov eax, [ebx]
        mov edx, 1
        push ecx
        mov ecx, 32 
        c2:
        xor eax, edx
        imul edx, 2
        loop c2
        pop ecx 
        mov [ebx], eax
        add ebx, 4
       loop c1 

	   pop    ebx
       pop    ebp
       ret 4
@InvertMatrixFastCall@12  ENDP

       end
