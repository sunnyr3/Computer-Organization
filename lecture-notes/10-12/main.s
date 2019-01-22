# main.s

	.text
	.globl main

main:	addi $sp,$sp,-8
	sw $ra,4($sp)
	sw $a0,0($sp)

	li $a0,20	# 20 bytes (5 words)
	li $v0,9	# sbrk
	syscall		# dynamically allocate memory -- malloc( 20 );
			# returns the address of this memory in $v0

	li $t0,35	# [ 35, 28, 135, 4, 3 ]
        sw $t0,0($v0)
	li $t0,28
        sw $t0,4($v0)
	li $t0,135
        sw $t0,8($v0)
	li $t0,4
        sw $t0,12($v0)
	li $t0,3
        sw $t0,16($v0)

	move $a0,$v0
	li $a1,5	# size of array (n = 5)
	jal sort

	lw $a0,0($sp)
	lw $ra,4($sp)
	addi $sp,$sp,8
	jr $ra
