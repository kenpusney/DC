jmp @start


;recursive function:
accumulate:
pop R1
pop R2
cmp R1,0
jz @_acc_res

add R1,R2,R2
sub R1,1

push R2
push R1
call @accumulate

_acc_res:
push R2
ret


;entry
start:

push 0
push 5
call @accumulate

pop R1

out R1

term
