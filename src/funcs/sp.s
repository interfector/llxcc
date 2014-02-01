subsp:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push	%eax
	movl	$4, %eax
	mul	%ebx
	movl	-12(%esi),%edi
	subl	%eax, %edi
	movl	%edi, -12(%esi)
	pop	%eax

	movl	%ebp, %esp
	pop	%ebp
	ret

addsp:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push	%eax
	movl	$4, %eax
	mul	%ebx
	movl	-12(%esi),%edi
	addl	%eax, %edi
	movl	%edi, -12(%esi)
	pop	%eax

	movl	%ebp, %esp
	pop	%ebp
	ret

