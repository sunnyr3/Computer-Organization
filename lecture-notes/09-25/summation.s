# summation.s

# int main()
# {
#   int i;
#   int sum = 0;
#   int from = 1, to = 100;
#   for ( i = from ; i <= to ; i++ ) sum += i;
#   printf( "The sum from %d to %d is %d\n", from, to, sum );
#   return EXIT_SUCCESS;
# }
#
# use SPIM to step through the code below...
# ...what do some of these instructions get translated into?

	.data
msg1:	.asciiz "The sum from "
msg2:	.asciiz " to "
msg3:	.asciiz " is "
msg4:	.asciiz "\n"

	.text
	.globl main
main:	li $s0,0	# $s0 is sum     $zero
	li $s1,1	# $s1 is from
	li $s2,100	# $s2 is to
	add $s3,$s1,0	# $s3 is loop variable i   ori   $zero

L1:	add $s0,$s0,$s3	# sum += i
	addi $s3,1	# i++
	ble $s3,$s2,L1	# Branch if Less than or Equal

	li $v0,4	# syscall 4 (print_str)
	la $a0,msg1
	syscall
	li $v0,1	# syscall 1 (print_int)
	ori $a0,$s1,0
	syscall
	li $v0,4	# syscall 4 (print_str)
	la $a0,msg2
	syscall
	li $v0,1	# syscall 1 (print_int)
	ori $a0,$s2,0
	syscall
	li $v0,4	# syscall 4 (print_str)
	la $a0,msg3
	syscall
	li $v0,1	# syscall 1 (print_int)
	ori $a0,$s0,0
	syscall
	li $v0,4	# syscall 4 (print_str)
	la $a0,msg4
	syscall

	jr $ra		# return to caller

