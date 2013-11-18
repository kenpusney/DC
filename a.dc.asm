move 46,&1
move 1,&2   ; a
move 1,&3   ; b
move 1,&4   ; c


initcond: ;if counter == 1 or counter == 2 then out 1
cmp &1,1
jz @out1
cmp &1,2
jz @out1

;else
sub &1,2,&1

cycle:
add &2,&3,&4
add &3,0,&2
add &4,0,&3
sub &1,1,&1
jnz @cycle

out &4
term

out1:
out 1
term