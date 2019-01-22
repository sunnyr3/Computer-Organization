# read.s

	.text
	.align 2
	.globl main

main:	li $v0,5	# read_int
	syscall
	# register $v0 has the integer the user entered

	jr $ra

