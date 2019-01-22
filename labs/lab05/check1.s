# checkpoint 1

	.data
prompt:	.asciiz "Enter an integer: "
num:	.word 15
msg1: 	.asciiz "EVEN\n"
msg2: 	.asciiz "ODD\n"

	.text
main:	
	la $a0, prompt
	li $v0, 4
	syscall 

	# Read in input value
	li $v0, 5
	syscall
	
	add $a0, $v0, $zero
	j isodd

isodd:	
	li $t0, 2
	div $a0, $t0
	mfhi $t0	# Save the remainder
	beq $t0, $zero, iseven
	la $a0, msg2
	li $v0, 4
	syscall	
	addi $v0, $zero, 1	# Return 1
	jr $ra		# Retuen caller

iseven:	
	la $a0, msg1
	li $v0, 4
	syscall
	addi $v0, $zero, 0	# Return 0
	jr $ra	




