ori $s1,$zero,4
loop1:
addi $t2,$t2,4
beq $t3,$zero,loop2
ori $s6,$t6,77
add $s7,$s0,$s0
andi $s2,$t5,255
loop2:
bne $s1,$t2,loop1
addi $t4,$t2,1
addi $s3,$zero,22
ori $t4,$zero,89
