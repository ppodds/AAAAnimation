transform PROTO
; arguments
; rcx: BYTE PTR image raw data pointer 
; rdx: BYTE PTR ascii frame data pointer
; r8: DWORD frame width
; r9: DWORD frame height
; rbp+30h: DWORD image raw data linesize
; this procedure modify rdi's byte array as ascii frame data
.CODE
transform PROC
    push rbp
    mov rbp, rsp
    mov rsi, rcx
    mov rdi, rdx
    mov rcx, r9
    L1: 
        push rcx
        mov rcx, r8
        L2:
            mov bl, [rsi]
            cmp bl, 56
            jb L4
            cmp bl, 76
            jb L5
            cmp bl, 96
            jb L6
            cmp bl, 116
            jb L7
            cmp bl, 136
            jb L8
            cmp bl, 156
            jb L9
            cmp bl, 176
            jb L10
            cmp bl, 196
            jb L11
            cmp bl, 216
            jb L12
            cmp bl, 255
            jb L13
            L4:
                mov BYTE PTR [rdi], ' '
                jmp L14
            L5:
                mov BYTE PTR [rdi], '.'
                jmp L14
            L6:
                mov BYTE PTR [rdi], ':'
                jmp L14
            L7:
                mov BYTE PTR [rdi], '!'
                jmp L14
            L8:
                mov BYTE PTR [rdi], '+'
                jmp L14
            L9:
                mov BYTE PTR [rdi], '*'
                jmp L14
            L10:
                mov BYTE PTR [rdi], 'e'
                jmp L14
            L11:
                mov BYTE PTR [rdi], '$'
                jmp L14
            L12:
                mov BYTE PTR [rdi], '@'
                jmp L14
            L13:
                mov BYTE PTR [rdi], '8'
                jmp L14
            L14:
                inc rdi
                inc rsi
            loop L2
        mov BYTE PTR [rdi], 0Ah
        inc rdi
        movsxd r10, SDWORD PTR [rbp+30h]
        sub r10,r8
        add rsi, r10
        pop rcx
    dec rcx ; loop can only do small jump
    jne L1 ; we need to use this replace loop 
    leave
    ret
transform ENDP
END