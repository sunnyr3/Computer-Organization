# checkpoint 2

# int x = 0;
#
# if (x<5)
#    x += 3;

    .data
num: .word 18
msg: .asciiz "x ($t0) equals "

    .text
main: lw $t0, num
      li $t1, 5
      blt $t0, $t1, less
      li $v0, 4          # syscall 4 (print_str)
      la $a0, msg
      syscall
      li $v0, 1
      move $a0, $t0
      syscall

      jr $ra

less: addi $t0, $t0, 3
      li $v0, 4
      la $a0, msg
      syscall
      li $v0, 1
      move $a0, $t0
      syscall    
      
      jr $ra
