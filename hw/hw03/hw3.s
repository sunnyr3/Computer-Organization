	.data
prompt1: .asciiz "Please enter values for n, k, and m:\n"
prompt2: .asciiz "Please enter values for the first matrix ("
prompt3: .asciiz "Please enter values for the second matrix ("
char1:	.asciiz "x"
char2:	.asciiz "):\n"
left:	.asciiz "["
right:	.asciiz "]\n"
tab:	.asciiz "\t"
newline: .asciiz "\n"
multi:	.asciiz "multiplied by\n"
eql:	.asciiz "equals\n"

	.text
	.globl main
main:	
	# Print the first prompt	
	li $v0 4
	la $a0 prompt1
	syscall

	# Read in value for n
	li $v0, 5
	syscall 
	add $s0, $v0, $zero

	# Read in value for k
	li $v0, 5
	syscall
	add $s1, $v0, $zero

	# Read in value for m
	li $v0, 5
	syscall
	add $s2, $v0, $zero

	# Get the size of array for the first matrix
	mul $t0, $s0, $s1
	sll $t0, $t0, 2

	# Get the size of array for the second matrix
	mul $t1, $s1, $s2
	sll $t1, $t1, 2

	# Read in inputs for the first matrix
	jal read_first_matrix
	move $s3, $a1

	# Read in inputs for the second matrix
	jal second_matrix
	move $s4, $a2

	# Print a newline
	la $a0, newline
	li $v0, 4
	syscall

	# Print the first matrix
	add $t1, $s0, $zero
	jal print_first_matrix

	la $a0, multi
	li $v0, 4
	syscall

	# Print the second matrix
	add $t1, $s1, $zero
	jal print_second_matrix

	# Print "equals"
	la $a0, eql
	li $v0, 4
	syscall

	move $s3, $a1
	move $s4, $a2
	# t2 is the sum
	li $t0, 0
	sll $t1, $s2, 2
	li $t2, 0
	li $t8, 0
	# s5 is the sum
	li $s5, 0
	# Start multiplication
	jal multiply

	# Exit the program
	li $v0, 10
	syscall


read_first_matrix:
	# Print the prompt
	la $a0, prompt2
	li $v0, 4
	syscall
	add $a0, $s0, $zero
	li $v0, 1
	syscall
	la $a0, char1
	li $v0, 4
	syscall
	add $a0, $s1, $zero
	li $v0, 1
	syscall
	la $a0, char2
	li $v0, 4
	syscall

	# Allocate the first matrix
	move $a0, $t0
	li $v0, 9
	syscall
	move $s3, $v0
	move $a1, $s3

read_for_first:
	# If t0 is zero, then finish reading input
	beq $t0, $zero, return

	# Read in the new integer
	li $v0, 5
	syscall
	add $t3, $v0, $zero
	
	# Save into the array
	sw $t3, 0($s3)
	addi $s3, $s3, 4
	addi $t0, $t0, -4
	j read_for_first


second_matrix:
	# Print the prompt
	la $a0, prompt3
	li $v0, 4
	syscall
	add $a0, $s1, $zero
	li $v0, 1
	syscall
	la $a0, char1
	li $v0, 4
	syscall
	add $a0, $s2, $zero
	li $v0, 1
	syscall
	la $a0, char2
	li $v0, 4
	syscall

	# Allocate the second matrix 
	add $a0, $t1, $zero
	li $v0, 9
	syscall
	move $s4, $v0
	move $a2, $s4

read_for_second:
	# If t1 is zero, then finish reading input
	beq $t1, $zero, return

	# Read in the new integer
	li $v0, 5
	syscall
	add $t3, $v0, $zero

	# Save into the array
	sw $t3, 0($s4)
	addi $s4, $s4, 4
	addi $t1, $t1, -4
	j read_for_second


print_first_matrix:
	beq $t1, $zero, return
	add $t0, $s1, $zero
	# Print the left square blacket
	la $a0, left
	li $v0, 4
	syscall

print_first_loop:
	beq $t0, $zero, print_first_newline
	lw $a0, 0($s3)
	li $v0, 1
	syscall		# Print integer
	la $a0, tab
	li $v0, 4
	syscall		# Print tab
	
	addi $t0, $t0, -1
	addi $s3, $s3, 4
	j print_first_loop

print_first_newline:
	la $a0, right
	li $v0, 4
	syscall		# Print the right blacket
	addi $t1, $t1, -1
	j print_first_matrix


print_second_matrix:
	beq $t1, $zero, return
	add $t0, $s2, $zero
	# Print the left square blacket
	la $a0, left
	li $v0, 4
	syscall

print_second_loop:
	beq $t0, $zero, print_second_newline
	lw $a0, 0($s4)
	li $v0, 1
	syscall		# Print integer
	la $a0, tab
	li $v0, 4
	syscall		# Print tab
	
	addi $t0, $t0, -1
	addi $s4, $s4, 4
	j print_second_loop

print_second_newline:
	la $a0, right
	li $v0, 4
	syscall		# Print the right blacket
	addi $t1, $t1, -1
	j print_second_matrix

multiply:
	beq $t8, $s0, return
	# Print the left blacket
	la $a0, left
	li $v0, 4
	syscall

mult_loop:
	# If t0=k, then we need to start from a new row
	beq $t0, $s2, start_newline
	# To check if t7 exceeds n
	add $t7, $s1, $zero
	# Set the starting point at the first matrix
	move $s3, $a1
	mul $t9, $t2, $s1
	sll $t9, $t9, 2
	add $s3, $s3, $t9
	# Set the starting point at the second matrix
	move $s4, $a2
	add $t3, $zero, $t0
	sll $t3, $t3, 2
	add $s4, $s4, $t3

mult_loop2:
	beq $t7, $zero, print_ans
	# Get the number from the first matrix
	lw $t4, 0($s3)
	# Get the number from the second matrix
	lw $t5, 0($s4)

	# Multiply t4 and t5
	mul $t6, $t4, $t5

	# Add to the sum
	add $s5, $s5, $t6

	# Decrement t7 by 1
	addi $t7, $t7, -1
	
	add $s4, $s4, $t1
	add $s3, $s3, 4
	j mult_loop2

print_ans:
	# Print the integer
	add $a0, $s5, $zero
	li $v0, 1
	syscall
	# Print tab
	la $a0, tab
	li $v0, 4
	syscall

	addi $t0, $t0, 1
	li $s5, 0

	j mult_loop

start_newline:
	# Print the right blacket
	la $a0, right
	li $v0, 4
	syscall
	addi $t0, $t0, 1
	beq $t8, $s0, return
	li $t0, 0
	li $s5, 0
	addi $t8, $t8, 1
	addi $t2, $t2, 1
	j multiply

return:
	jr $ra
