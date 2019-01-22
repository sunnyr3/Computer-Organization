        .data
array: .word 12, 100, 101, 5, 123456789, 18
msg:   .asciiz"Number of Odd Integers is: "

        .text
main:
        li $a1, 6               # size of array
        la $a0, array
        li $s1, 2

        li $t2, 0
        li $t3, 0               # Count the number of odd int

numodds:
        beq $a1, $zero, exit    # If size of array is 0, then exit
        lw $t0, 0($a0)
        div $t0, $s1
        mfhi $t1                # Remainder 
        addi $a0, $a0, 4
        addi $a1, $a1, -1
        beq $t1, 1, isodd
        j numodds

isodd:
        addi $t3, $t3, 1
        j numodds
        b exit

exit:
        la $a0, msg
        li $v0, 4
        syscall

        move $a0, $t3
        li $v0, 1
        syscall

        li $v0, 10
        syscall