call:
	push	%ebp
	movl %esp, %ebp

	movl	16(%esp), %edi

# Calculate the relative ip
	subl	%esi, %edi

	push	%eax

	movl	%edi, %eax
	movl	$10, %edi
	xor	%edx, %edx
	divl	%edi

	movl	%eax, %edi

	pop	%eax

# Save the rip
	movl	-16(%esi), %ebx
	addl	-12(%esi), %ebx

	movl	%edi, (%ebx)

	movl	-12(%esi),%ebx
	addl	$4, %ebx
	movl	%ebx, -12(%esi)

# Call 
	movl	8(%esp), %ebx
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

