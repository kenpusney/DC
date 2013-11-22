jmp @start

recur:
pop data1
pop data2
sub data1,0
jz @_recur_res

add data1,data2,data2
sub data1,1

push data2
push data1
call @recur

_recur_res:
push data2
ret

testa:
out 1
push 5
ret

start:

push 0
push 5

call @testa

push 0
push 5
call @recur

term
