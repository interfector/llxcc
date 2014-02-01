inc:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx

	push %eax

	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	addl	$1, 1(%ebx)

	pop %eax

	movl	%ebp, %esp
	pop	%ebp
	ret
