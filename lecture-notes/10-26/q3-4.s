# q3-4.s

	.data
txt:	.asciiz "abcdEFGHijklMNOP1234!!!"

#############################################################

	.text
	.globl downcase
	.globl main

downcase:
	addi $sp,$sp,-8
	sw $a0,4($sp)
	sw $ra,0($sp)

	li $t0,0		# $t0 is count
repeat:	lb $t1,0($a0)		# $a0 is base addr of s
	beq $t1,$zero,done	# if *s == '\0' done
	sle $t2,$t1,0x5a	# sle: *s <= 0x5a 'Z'
	sge $t3,$t1,0x41	# sge: *s >= 0x41 'A'
	add $t4,$t2,$t3		# $t4 = $t2 + $t3
	bne $t4,2,notupper
	addi $t1,$t1,0x20	# convert to lowercase
	sb $t1,0($a0)		# store changed byte
	addi $t0,$t0,1		# count++
notupper:
	addi $a0,$a0,1		# s++ (next character...)
	j repeat

done:	move $v0,$t0
	lw $ra,0($sp)
	lw $a0,4($sp)
	addi $sp,$sp,8
	jr $ra

#############################################################


main:	addi $sp,$sp,-4
	sw $ra,0($sp)

	la $a0,txt
	jal downcase

	move $a0,$v0
	li $v0,1	# print_int
	syscall

	la $a0,txt
	li $v0,4	# print_str
	syscall

	lw $ra,0($sp)
	addi $sp,$sp,4
	jr $ra

