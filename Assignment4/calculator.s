# FileName: calculator.s
# Purpose: write function for plus, minus and mul and find out what XX does.
# Name: Foo Jun Pin 301414336
# Date: 15/2/2022 

	.globl	XX # Make sure you change the name of this function - see XX function below
	.globl	plus
	.globl	minus
	.globl	mul

# x in edi, y in esi

XX: # Change the name of this function to something more descriptive and add a description
	xorl	%eax, %eax
	cmpl	%esi, %edi
	setl	%al         # See Section 3.6.2 of our textbook for a description of the set* instructions
	ret

plus:  # performs integer addition
	xorl %eax, %eax
	leal (%esi, %edi), %eax
	ret

minus: # performs integer subtraction
		xorl %eax, %eax
	negl %esi
	leal (%edi, %esi), %eax
	ret

mul: # performs integer multiplication - when both operands are non-negative!
	
	xorl %eax, %eax
	jmp test

test:
	cmpl $2, %esi
	jg loop
	addl %edi, %eax
	ret
	
loop:
	subl $2, %esi
	addl %edi, %eax
	jmp test