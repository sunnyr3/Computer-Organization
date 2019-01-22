      .text
main: li $t0, 45
      li $t1, 54
      j gcd

gcd:  bne $t0, $t1, loop
      li $v0 1        # syscall 1 (print_int)
      move $a0 $t0
      syscall
      li $v0 10       # syscall 10 (exit)
      syscall      

loop: bgt $t0, $t1, greater
      sub $t1, $t1, $t0
      j gcd

greater:
      sub $t0, $t0, $t1
      j gcd
  
      jr $ra
