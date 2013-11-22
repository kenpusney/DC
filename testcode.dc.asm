jmp @start

recur:
pop R1
pop R2
sub R1,0
jz \_recur_res

add R1,R2,R2
sub R1,1

push R2
push R1
call @recur

_recur_res:
push R2
ret

testa:
out 1
push 5
ret

start:

push 0
push 5
call @recur

pop R1
out R1

term
