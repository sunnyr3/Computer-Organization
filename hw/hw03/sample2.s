	.data
array: .space 64
prompt1: .asciiz "Enter the values for matrix A:\n"
prompt2: .asciiz "Enter a scalar b:\n"
newline: .asciiz "\n"
tab: .asciiz "\t"
product: .asciiz "Product of A x b:\n"

    .text
main:
    li $v0 4
    la $a0 prompt1 #Print prompt
    syscall

    li $s0 16 #Array size
    la $s1 array #Array address
    li $t0 0 #counter

    la $a1 array #Pass array into argument
    jal input

    li $v0 4
    la $a0 prompt2 #ask for scalar
    syscall
    li $v0 5
    syscall
    move $s2 $v0 #s2 = scalar

    jal multiply

    la $a1 array
    li $t0 0
    li $v0 4
    la $a0 product
    syscall #Print statement
    j print

    li $v0 10
    syscall

#Reading input
input:
    bne $s0, $t0, loop
    jr $ra

loop:
    li $v0 5
    syscall
    sw $v0 ($a1) #array[i] = input

    j latch

latch:
    addi $t0 $t0 1
    addi $a1 $a1 4 #move to next array location
    j input

#multiply function
multiply:
    la $a0 array
    li $t0 0

header:
    bne $s0, $t0, multbody
    jr $ra

multbody:
    lw $t1, ($a0)
    mult $t1, $s2
    mflo $t1
    sw $t1 ($a0)
    j multlatch

multlatch:
    addi $t0, $t0, 1
    addi $a0, $a0, 4
    j header

#Print 2d array
print:
    li $t1 0
    bne $t0, 4, innerheader
    li $v0 10
    syscall

printlatch:
    addi $t0, $t0, 1
    la $a0 newline
    li $v0 4
    syscall #New line
    j print

innerheader:
    bne $t1, 4, printLoop
    j printlatch

printLoop:
    lw $a0 ($a1)
    li $v0 1
    syscall #Print value
    li $v0 4
    la $a0 tab
    syscall #Tab
    j innerlatch

innerlatch:
    addi $t1, $t1, 1
    addi $a1, $a1, 4
    j innerheader