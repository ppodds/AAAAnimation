transform PROTO
;ptrbyte(第一個位置)(rcx)(data的陣列PTR)
;ptrbyte(第一個位置)(rdx)(回傳陣列PTR)
;DWORD(Width)(r8)
;DWORD(Height)(r9)
;DWORD(linesize) (rbp+30h)
.CODE
transform PROC
    push rbp
    mov rbp, rsp
    mov rax, rcx
    mov rcx, r9
    L1: 
        push rcx
        mov rcx, r8
        L2:
            mov bl, [rax]
            cmp bl, 128
            jA L3
            mov BYTE PTR [rdx], ' '
            jmp L4
            L3:
                mov BYTE PTR [rdx], '%'
            L4:
                inc rdx
                inc rax
            loop L2
        mov BYTE PTR [rdx], 0Ah
        inc rdx
        movsxd r10, SDWORD PTR [rbp+30h]
        sub r10,r8
        add rax, r10
        pop rcx
    loop L1
    leave
    ret
transform ENDP
END