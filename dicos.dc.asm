;=============

; DicOS -- Directly Interpreted Collective Operating System

;=============

jmp @start  ; bootloader

;----------
DCInit:
pop R1  ;task_cnt

ret

;----------
DCRegTask:
ret

;----------
DCExit0:
ret

DCExit1:
ret

DCExit2:
ret

; task1(void)
task1:
out 1
ret

; task2(void)
task2:
out 2
ret

start:

call @DCDumpMem

term

DCDumpMem:
move @_DCMemory,R1
__dcdm_iter:

add R1,1,R1
out $R1
cmp R1,@_DCEnd
jnz @__dcdm_iter
ret

_DCMemory:
term
term
term
term
term
_DCEnd: