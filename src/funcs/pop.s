pop:
	push	%ebp
	movl %esp, %ebp

	movl	%eax, %edi
	movl	8(%esp), %ebx
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	movl	%edi, %eax

	movl	%eax, 1(%ebx)

	movl	%ebp, %esp
	pop	%ebp
	ret

