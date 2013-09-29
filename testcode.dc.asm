add 0,10,&3   ; counter
add 0,1,&4   ; a
add 0,1,&5   ; b
add 0,0,&6   ; c


; if counter == 1 or counter == 2: c = 1
cmp &3,1
jz 30
cmp &3,2
jz 25

; else:
sub &3,2,&3


; while counter--: c = a + b; a = b; b = c
add &4,&5,&6
add &5,0,&4
add &6,0,&5
sub &3,1,&3
jnz -18


out &6
term

out 1
term