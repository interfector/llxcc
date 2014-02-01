push:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	mov	1(%ebx), %eax

	movl	%ebp, %esp
	pop	%ebp
	ret
