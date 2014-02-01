stpush:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push	%eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	movl 1(%ebx),%edi
	pop	%eax

	movl	-16(%esi),%ebx
	addl	-12(%esi),%ebx

	movl	%edi, (%ebx)

	movl	-12(%esi),%ebx
	addl	$4, %ebx
	movl	%ebx, -12(%esi)

	movl	%ebp, %esp
	pop	%ebp
	ret

