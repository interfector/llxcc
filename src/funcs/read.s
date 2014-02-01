read:
	push	%ebp
	movl %esp, %ebp

	push	%eax
	push	%ecx

	xor	%edi, %edi

	cmp	$3,-20(%esi)
	je	read_char	

	movl	$3, %eax
	movl	$0, %ebx
	movl	%esp, %ecx
	sub	$1000, %ecx
	movl	$12, %edx

	int	$0x80

	movl	%eax, %edi

	xor	%eax, %eax
	xor	%ebx, %ebx
	xor	%edx, %edx

read_loop:
	cmpb	$0x30, (%ecx,%ebx)
	jl	read_exit

	cmpb	$0x39, (%ecx,%ebx)
	jg	read_exit

	cmp	%ebx, %edi
	je	read_exit

	push	%edi
	movl	$10, %edi
	mul	%edi
	pop	%edi

	xor	%edx, %edx
	movb	(%ecx,%ebx), %dl
	sub	$0x30, %edx
	add	%edx, %eax

	inc	%ebx

	jmp	read_loop

read_char:
	movl	$3, %eax
	movl	$0, %ebx
	movl	%esp, %ecx
	sub	$1000, %ecx
	movl	$1, %edx

	int	$0x80

	xor	%edx, %edx
	movb	(%ecx,%ebx), %dl
	movl	%edx, %eax

read_exit:
	movl	%eax, %edi

	pop	%ecx
	pop	%eax

	movl	8(%esp), %ebx
	push	%eax
	movl	$11, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	movl	%edi, 1(%ebx)
	pop	%eax

	movl	%ebp, %esp
	pop	%ebp
	ret

