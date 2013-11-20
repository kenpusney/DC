jmp @start


;recursive function:
accumulate:
pop data1
pop data2
cmp data1,0
jz @_acc_res

add data1,data2,data2
sub data1,1

push data2
push data1
call @accumulate

_acc_res:
push data2
ret


;entry
start:

push 0
push 5
call @accumulate

pop data1

out data1

term
