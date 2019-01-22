# Checkpoint 1

	.data
prompt: .asciiz "Enter positive integer:\n"
for:	.asciiz "For $"
need:	.asciiz ", you need:\n"
qrt:	.asciiz " quarter\n"
dime:	.asciiz " dime\n"
penny:	.asciiz " penny\n"
qrts: 	.asciiz " quarters\n"
dimes:	.asciiz " dimes\n"
pennies: .asciiz " pennies\n"
dot:	.asciiz "."

	.text
	.globl main
	.globl challenge
main:
	li $s0, 5
	li $t1, 25
	li $t2, 10

read_input:
	beq $s0, $zero, exit
	# Print the prompt
	la $a0, prompt
	li $v0, 4
	syscall
	
	# Read input
	li $v0, 5
	syscall

	add $a0, $v0, $zero
	j challenge

challenge:
	add $t0, $a0, $zero
	
	# Print output prompt
	jal print_prompt	

	# Get the number of quarters
	divu $t0, $t1
	# t3 is quotient, and t4 is remainder
	mflo $t3
	mfhi $t4

	# Print the number of quarters
	jal print_quarters

	# Get the number of dimes
	divu $t4, $t2
	# t3 is quotient, and t4 is remainder
	mflo $t3
	mfhi $t4

	# Print the number of dimes
	jal print_dimes

	# t4 is the number of pennies
	jal print_pennies

	addi $s0, $s0, -1
	j read_input

print_prompt:
	la $a0, for
	li $v0, 4
	syscall

	li $t3, 100
	div $t0, $t3
	mflo $t4
	mfhi $t5

	add $a0, $t4, $zero
	li $v0, 1
	syscall

	la $a0, dot
	li $v0, 4
	syscall


	add $a0, $t5, $zero
	li $v0, 1
	syscall

	la $a0, need
	li $v0, 4
	syscall

	jr $ra

print_quarters:
	add $a0, $t3, $zero
	li $v0, 1
	syscall

	slti $t5, $t3, 2
	beq $t5, $zero, quarters
	la $a0, qrt
	li $v0, 4
	syscall

	jr $ra

quarters:
	la $a0, qrts
	li $v0, 4
	syscall
	jr $ra

print_dimes:
	add $a0, $t3, $zero
	li $v0, 1
	syscall

	slti $t5, $t3, 2
	beq $t5, $zero, more_dimes
	la $a0, dime
	li $v0, 4
	syscall

	jr $ra

more_dimes:
	la $a0, dimes
	li $v0, 4
	syscall
	jr $ra 

print_pennies:
	add $a0, $t4, $zero
	li $v0, 1
	syscall

	slti $t5, $t4, 2
	beq $t5, $zero, more_pennies
	la $a0, penny
	li $v0, 4
	syscall
	jr $ra

more_pennies:
	la $a0, pennies
	li $v0, 4
	syscall
	jr $ra

exit:
	li $v0, 10
	syscall