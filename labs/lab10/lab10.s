# lab10.s

	.data
array:	.word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
tab:	.asciiz "\t"
newline:.asciiz "\n"

	.text
	.globl main

main:
	la $s0,array
	# 64 = 16 * 4
	li $s1,64
	add $s1,$s0,$s1
	j loop_header

loop_header:
	blt $s0,$s1,loop_body
	j loop_exit

loop_body:
	#----------- First Time -----------
	 lw $a0,0($s0)
	 li $v0,1
	 syscall
	 li $v0,4
	 la $a0,tab
	 syscall
	lw $t0,0($s0)
	addi $t0,$t0,7
	sw $t0,0($s0)
	 lw $a0,0($s0)
	 li $v0,1
	 syscall
	 li $v0,4
	 la $a0,newline
	 syscall
	
	#---------- Second Time ----------
	lw $a0,4($s0)
	li $v0,1
	syscall
	li $v0,4
	la $a0, tab
	syscall
	lw $t1, 4($s0)
	addi $t1, $t1, 7
	sw $t1, 4($s0)
	lw $a0,4($s0)
	li $v0,1
	syscall
	li $v0,4
	la $a0, newline
	syscall

	#---------- Third Time ----------
	lw $a0, 8($s0)
	li $v0,1
	syscall
	li $v0,4
	la $a0, tab
	syscall
	lw $t2, 8($s0)
	addi $t2, $t2, 7
	sw $t2, 8($s0)
	lw $a0, 8($s0)
	li $v0,1
	syscall
	li $v0,4
	la $a0, newline
	syscall

	#---------- Fourth Time ----------
	lw $a0, 12($s0)
	li $v0,1
	syscall
	li $v0,4
	la $a0, tab
	syscall
	lw $t3, 12($s0)
	addi $t3, $t3, 7
	sw $t3, 12($s0)
	lw $a0, 12($s0)
	li $v0,1
	syscall
	li $v0,4
	la $a0, newline
	syscall
	j loop_latch

loop_latch:
	addi $s0,$s0,16
	j loop_header

loop_exit:
	jr $ra		# return to caller

