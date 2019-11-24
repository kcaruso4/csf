.text

.globl main
.globl vec_sum_sq

main:
	la $a0, result
	la $a1, vec1
	la $a2, vec2
	la $t0, n_elts
	lw $a3, 0($t0)

	# save return address
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	# call vec_sum_sq
	jal vec_sum_sq

	# restore return address
	lw $ra, 0($sp)
	addi $sp, $sp, 4

	# return from main
	jr $ra

# $a0 is base address of result vector.
# $a1 is base address of first argument vector.
# $a2 is base address of second argument vector.
# $a3 is the number of elements in the argument vectors.

# OPTIMIZATION: To avoid pipeline stalls I strategically determined
# the order of the instructions. I determined the order of commands
# by alternating between loading a word/performing a calculation
# and updating addresses because these command were independent of
# one another. Therefore I could load/perform a calculation and
# update an address simultaneously while avoiding data hazards.

# I think I was successful because from my understanding of time
# for instructions, so long as commands are independent, I can
# perform the breakdowns of each instruction simultaneously.
# For example I can perform the instruction fetch for line 47
# while performing the register read  of $a0 in line 46 without
# encountering a hazard and optimizing the time of my function.
# I exploited this fact by separating dependent commands throughout
# the function.

vec_sum_sq:
	beq $a3, $zero, end	#exit function				500ps
	lw $t2, 0($a1)		# t2 = a1[i]				800ps
	addi $a1, $a1, 4	# move a1 pointer forward	around 600ps
	lw $t3, 0($a2)		# t3 = a2[i]				800ps
	addi $a2, $a2, 4	# move a2 pointer forward	around 600ps
	mul $t2, $t2, $t2	# t2 = t2 * t2
	mul $t3, $t3, $t3	# t3 = t3 * t3
	addi $a3, $a3, -1	# decrement i				around 600ps
	add $t4, $t3, $t2	# t4 = t3 + t2				600ps
	sw $t4, 0($a0)		# a0[i] = t4				700ps
	addi $a0, $a0, 4	# move a0 pointer forward	around 600ps
	j vec_sum_sq		# start loop again

end:
	jr $ra				#return to previous address


########################################################################
# Data segment: you are free to change the value of the
# n_elt variables and the contents of the vec1 and vec2 arrays
# for testing purposes.

.data
result:	.space 10000
n_elts:	.word 4
vec1:	.word 1, 2, 3, 4, 5
vec2:	.word 6, 7, 8, 9, 10
