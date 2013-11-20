move 46,&1
move 1,&2   ; a
move 1,&3   ; b
move 1,&4   ; c


; if counter == 1 or counter == 2: c = 1
cmp &1,1
jz 30
cmp &1,2
jz 25

; else:
sub &1,2,&1


; while counter--: c = a + b; a = b; b = c
add &2,&3,&4
add &3,0,&2
add &4,0,&3
sub &1,1,&1
jnz -18


out &4
term

out 1
term