# expr.s

# f  = g  + h  - i  - j ;
#
# s0 = s1 + s2 - s3 - s4;

# example
# f = 7 + 6 - 5 - 2
#
# See Appendix A

main:	li $s1,7	# Load Immediate (li)  g = 7
	li $s2,6	# h = 6
	li $s3,5	# i = 5
	li $s4,2	# j = 2

	add $t0,$s1,$s2	# temp t0 = g + h
	sub $t1,$t0,$s3	# temp t1 = t0 - i
	sub $a0,$t1,$s4	# f = t1 - j

	li $v0,1	# syscall 1 (print_int)
	syscall		# prints $a0

	jr $ra		# return to the calling function

