not:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	movl 1(%ebx),%eax

	not	%eax

	movl	%ebp, %esp
	pop	%ebp
	ret
