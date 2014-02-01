mul:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	movl 1(%ebx),%eax
	pop	%edi
	mul	%edi

	movl	%ebp, %esp
	pop	%ebp
	ret

