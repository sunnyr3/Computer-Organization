# dynamic.s

	.text
	.globl main

main:	
	addi $sp,$sp,-8
	sw $a0,0($sp)
	sw $ra,4($sp)

	# dynamically allocate 100 bytes -- malloc( 100 );
	li $a0,100
	li $v0,9
	syscall		# dynamically allocate memory

	sw $a0,0($v0)

	# dynamically allocate 100 bytes -- malloc( 100 );
	li $a0,100
	li $v0,9
	syscall		# dynamically allocate memory

	sw $a0,0($v0)

	# dynamically allocate 100 bytes -- malloc( 100 );
	li $a0,100
	li $v0,9
	syscall		# dynamically allocate memory

	sw $a0,0($v0)

	lw $ra,4($sp)
	lw $a0,0($sp)
	addi $sp,$sp,8
	jr $ra

