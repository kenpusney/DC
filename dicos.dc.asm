;=============

; DicOS -- Directly Interpreted Collective Operating System

;=============
jmp @start

;----------
DCInit:
pop R1  ;task_cnt

move @_DCMemory,R2
out R2

ret

;----------
DCRegtask:
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

call @DCInit
move @_DCMemory,R1
add R1,1
out R1
move $R1
term

_DCMemory: