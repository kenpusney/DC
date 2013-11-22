;=============

; Directly Interpreted Collective Operating System

;=============
jmp @start

passf0call:
pop R1
call R1
ret

passf1call:
pop R1
call R1
ret

; DCExit(int)
DCExit:
pop
ret

; task1(void)
task1:
out 1
push 2
call @DCExit
ret

; task2(void)
task2:
out 2
ret

start:

push @task2
call @passf0call
call @task1

term