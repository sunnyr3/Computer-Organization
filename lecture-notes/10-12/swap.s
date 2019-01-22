# swap.s

# swap is a leaf procedure, which means we do not
# need to save anything on the stack

	.data
	.align 0
	.asciiz "abcde"

	.text
	.align 2	# word alignment, 2^2
	.globl swap

swap:	sll $t1,$a1,2	# $t1 = k * 4
	add $t1,$a0,$t1	# $t1 = v+(k*4)
			#   (address of v[k])
	lw $t0,0($t1)	# $t0 (temp) = v[k]
	lw $t2,4($t1)	# $t2 = v[k+1]
	sw $t2,0($t1)	# v[k] = $t2 (v[k+1])
	sw $t0,4($t1)	# v[k+1] = $t0 (temp)
	jr $ra		# return to calling routine

