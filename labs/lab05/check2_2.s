	.data
prompt: .asciiz "Enter an integer: "
msg1:	.asciiz "byte #1: "
msg2: 	.asciiz "\nbyte #2: "
msg3: 	.asciiz "\nbyte #3: "
msg4:	.asciiz "\nbyte #4: "

	.text
	.globl main
main: 	
	la $a0, prompt
	li $v0, 4
	syscall

	# Read the user's input
	li $v0, 5
	syscall

	add $a0, $v0, $zero
	la $a1, 0xff000000
	jal display

	li $v0, 10
	syscall

display:
	add $s0, $a0, $zero
	# Byte 1
	and $t0, $s0, $a1
	srl $t5, $t0, 24
	li $v0, 4
	la $a0, msg1
	syscall
	li $v0, 1
	move $a0, $t5
	syscall

	# Byte 2
	la $a1, 0x00ff0000
	and $t0, $s0, $a1
	srl $t5, $t0, 16
	li $v0, 4
	la $a0, msg2
	syscall
	li $v0, 1
	move $a0, $t5
	syscall

	# Byte 3
	la $a1, 0x0000ff00
	and $t0, $s0, $a1
	srl $t5, $t0, 8
	li $v0, 4
	la $a0, msg3
	syscall
	li $v0, 1
	move $a0, $t5
	syscall

	# Byte 4
	la $a1, 0x000000ff
	and $t0, $s0, $a1
	srl $t5, $t0, 0
	li $v0, 4
	la $a0, msg4
	syscall
	li $v0, 1
	move $a0, $t5
	syscall

	jr $ra