move 46,R1
move 1,R2   ; a
move 1,R3   ; b
move 1,R4   ; c


; if counter == 1 or counter == 2: c = 1
cmp R1,1
jz @out1
cmp R1,2
jz @out1

; else:
sub R1,2

iterate:
; while counter--: c = a + b; a = b; b = c
add R2,R3,R4
move R3,R2
move R4,R3
sub R1,1
jnz @iterate

out R4
term

out1:
out 1
term