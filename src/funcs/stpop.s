stpop:
	push	%ebp
	movl %esp, %ebp

	movl	-16(%esi),%ebx
	addl	-12(%esi), %ebx
	subl	$4, %ebx
	movl	(%ebx),%edi

	movl	8(%esp), %ebx
	push	%eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	movl	%edi, 1(%ebx)
	pop	%eax

	movl	-12(%esi),%edi
	subl	$4, %edi
	movl	%edi, -12(%esi)

	movl	%ebp, %esp
	pop	%ebp
	ret

