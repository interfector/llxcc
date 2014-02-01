ret:
	push	%ebp
	movl %esp, %ebp

	movl	-12(%esi),%edi
	subl	$4, %edi
	movl	%edi, -12(%esi)

	movl	-16(%esi), %ebx
	addl	-12(%esi), %ebx

	movl	(%ebx), %edi
	movl	%edi, %ebx

	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	pop	%eax

	movl	%ebx, 4(%esp)

	movl	%ebp, %esp
	pop	%ebp
	ret

