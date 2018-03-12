write:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push	%ecx
	push	%eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	mov	1(%ebx), %edi

	xor	%eax, %eax
	xor	%ebx, %ebx

	cmp	$3,-20(%esi)
	je	write_char

	cmp	$0, %edi
	je	zero_push

	jmp	push_loop

zero_push:
	push	%edi
	inc	%ebx
	jmp	write_loop_init

push_loop:
	cmp	$0, %edi 
	jle	write_loop_init

	xor	%edx, %edx
	movl	%edi, %eax
	movl	$10, %ecx
	divl	%ecx
	movl	%edx, %edi
	push	%edi
	movl	%eax, %edi

	inc	%ebx

	jmp	push_loop

write_loop_init:
	xor	%edi, %edi

write_loop:
	cmp	%edi, %ebx
	je	write_exit

	addl	$0x30, (%esp)
	movl	%esp, %ecx

	push	%ebx

	xor	%eax, %eax
	xor	%ebx, %ebx
	xor	%edx, %edx

	movl	$4, %eax
	movl	$1, %ebx
	movl	$2, %edx

	int	$0x80

	pop	%ebx
	pop	%ecx

	inc	%edi

	jmp	write_loop

write_exit:
	push	$0xa
	movl	%esp, %ecx

	jmp	wexit

write_char:
	push	%edi
	movl	%esp, %ecx

wexit:
	movl	$4, %eax
	movl	$1, %ebx
	movl	$1, %edx

	int	$0x80

	pop	%ebx

	pop	%eax
	pop	%ecx

	movl	%ebp, %esp
	pop	%ebp
	ret

