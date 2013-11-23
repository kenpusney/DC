jmp @start

test_a:
pop R1
; call param
call R1
ret

test_b:
out 1
ret

start:

; standard call
call @test_b

; dynamic modification at runtime
move @test_b,R1
add R1,2  ;offset
add $R1,2,$R1

; function as param
push @test_b
call @test_a

term
