chmod:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	movl	%ebx, -16(%esi)

	movl	%ebp, %esp
	pop	%ebp
	ret

