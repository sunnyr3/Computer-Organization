# bitcount.s
#
# The bitcount procedure defined below counts
# the number of 1-bits in given input $a0, returning
# this count in $v0

        .data
txt1:   .asciiz "The number "
txt2:   .asciiz " has "
txt3:   .asciiz " bit"
txt4:   .asciiz "s"
newline:.asciiz "\n"

############################################################

	.text
	.globl bitcount
	.globl main

############################################################

bitcount:
	# save registers $a0 and $ra on the stack
	addi $sp,$sp,-8
	sw $a0,0($sp)
	sw $ra,4($sp)

loopinit:
	li $t0,0	# use $t0 to keep track of the number of 1 bits
	li $t1,32	# loop variable to iterate 32 times

loopbody:
	# mask (clear) all but the leftmost bit
	# andi $t3,$a0,0x80000000 <-- this will not work -- why not?
	li $t2,0x80000000	# mask: 10000000000000000000000000000000
				# why does this instruction work with
				#  a 32-bit operand?

	and $t3,$a0,$t2
	beq $t3,$zero,skip	# if $t3 is 0, skip this bit
	addi $t0,$t0,1		# count this 1-bit (in $t0)
skip:	sll $a0,$a0,1		# shift $a0 left one bit position
latch:	sub $t1,$t1,1		# decrement loop variable
	bne $t1,$zero,loopbody

	move $v0,$t0		# return the result in $v0
	lw $ra,4($sp)
	lw $a0,0($sp)
	addi $sp,$sp,8
	jr $ra

############################################################

main:	addi $sp,$sp,-8
	sw $a0,0($sp)		# save register $a0 on the stack
	sw $ra,4($sp)		# save return address $ra on the stack

#	li $a0,1234	# try different values here
#	jal bitcount
#	move $a0,$v0
#	li $v0,1	# print_int
#	syscall

        li $a0,1234	# try different values here
        jal bitcount
        move $t0,$a0
        move $t1,$v0

        la $a0,txt1
        li $v0,4        # print_str
        syscall

        move $a0,$t0
        li $v0,1        # print_int
        syscall

        la $a0,txt2
        li $v0,4        # print_str
        syscall

        move $a0,$t1
        li $v0,1        # print_int
        syscall

        la $a0,txt3
        li $v0,4        # print_str
        syscall

        beq $t1,1,S
        la $a0,txt4
        li $v0,4        # print_str
        syscall

S:      la $a0,newline
        li $v0,4        # print_str
        syscall

	lw $ra,4($sp)
	lw $a0,0($sp)
	addi $sp,$sp,8
	jr $ra

