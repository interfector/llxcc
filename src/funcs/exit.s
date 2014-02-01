exit:
	push	%ebp
	movl	%ebp, %esp

	movl	8(%esp), %ebx

	xor	%eax, %eax
	movb	$1, %eax
	int	$0x80

	movl	%ebp, %esp
	pop	%ebp
	ret
