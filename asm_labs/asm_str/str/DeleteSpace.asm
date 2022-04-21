      .386
      .model flat
      .data
      .code
       PUBLIC _DeleteSpace
_DeleteSpace PROC 
        push ebp
        mov ebp, esp
        pushf
        push edi
        push ebx
        push esi
        xor ah, ah      
        mov edi, [ebp+08h] 
        mov ecx, [ebp+0Ch] 
        mov edx, edi     
        mov eax, ' '
        push edi 
        add edi, ecx
        dec edi
        scasb
        jne sk
        inc ecx
        sk:
        pop edi
        cld
      c1 :
    jecxz fin2
        mov   al, ' '
        test  al, 1
        repe  scasb      
        je    fin
        test  byte ptr[edi - 1], 0FFh
        je    fin        
        mov   ebx, edi
        dec   ebx        
        repne scasb
        inc  ah        
        ;push eax
        push ecx
        push edi         
        mov ecx, edi
        mov esi, ebx
        mov edi, edx
        sub ecx, esi
        cld
        rep movsb
        pop edi
        pop ecx
        add edx, edi
        sub edx, ebx
        jmp c1
     fin :
        cmp ah, 0   
        je  fin2
        dec edx
    fin2 :
    mov byte ptr[edx], 0
        pop esi
        pop ebx
        pop edi
        popf
        pop ebp
        ret
_DeleteSpace ENDP
   end