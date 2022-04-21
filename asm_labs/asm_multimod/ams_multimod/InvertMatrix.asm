      .386
      .model flat
      .data
      .code
       PUBLIC _InvertMatrix@12
_InvertMatrix@12 PROC  
       push   ebp
       mov    ebp, esp
	   push   ebx

       mov    ebx, [ebp+8]
       mov    ecx, [ebp+12]
       imul ecx, [ebp+16]

      
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
       ret 0Ch
_InvertMatrix@12  ENDP

       end
