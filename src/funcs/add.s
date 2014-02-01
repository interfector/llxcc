add:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movl 1(%ebx),%eax
	pop	%edi
	addl	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

