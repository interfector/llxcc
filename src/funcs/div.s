div:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	movl 1(%ebx),%edi
	pop	%eax
	xor	%edx, %edx
	divl	%edi

	movl	%ebp, %esp
	pop	%ebp
	ret

