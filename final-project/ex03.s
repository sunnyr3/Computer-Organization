ori $s1,$zero,451
loop:
addi $t2,$t2,73
slti $t4,$s1,453
addi $s1,$s1,1
bne $t4,$zero,loop
ori $s6,$t6,77
add $s7,$s0,$s0
andi $s2,$t5,255
