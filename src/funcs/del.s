del:
	push	%ebp
	movl %esp, %ebp

	movl	%eax, %edi

	movl	8(%esp), %ebx
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	movl	$0, 1(%ebx)

	movl	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret
