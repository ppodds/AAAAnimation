wait_until_smaller PROTO
; arguments
; xmm0: REAL4 a REAL4 variable need to be compared
; rdx: SQWORD PTR a SQWORD pointer which value be pointed would increase
; this procedure would block the thread until the condition is fulfilled
; Caution: it may cause the thread is blocked by a infinite loop
.CODE
wait_until_smaller PROC
    push rbp
    mov rbp, rsp
compare:
    cvtsi2ss xmm1, SQWORD PTR [rdx] ; convert rdx to REAL4 type and store it in xmm1 
    comiss xmm0,xmm1 ; compare xmm0 with xmm1
    jbe fufilled ; jump to fufilled if xmm0 <= xmm1
    jmp compare ; jump to compare if xmm0 > xmm1
fufilled:
    leave
    ret
wait_until_smaller ENDP
END