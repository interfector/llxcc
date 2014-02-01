jmp:
	push	%ebp
	movl %esp, %ebp

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

jmp_g:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	pop	%eax

	cmp	$2, %ecx
	jne	jmp_g_end
	
	movl	%ebx, 4(%esp)

jmp_g_end:
	movl	%ebp, %esp
	pop	%ebp
	ret

jmp_m:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	pop	%eax

	cmp	$1, %ecx
	jne	jmp_m_end
	
	movl	%ebx, 4(%esp)

jmp_m_end:
	movl	%ebp, %esp
	pop	%ebp
	ret


jmp_n:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	pop	%eax

	cmp	$0, %ecx
	je	jmp_n_end
	
	movl	%ebx, 4(%esp)

jmp_n_end:
	movl	%ebp, %esp
	pop	%ebp
	ret


jmp_z:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	pop	%eax

	cmp	$0, %ecx
	jne	jmp_z_end
	
	movl	%ebx, 4(%esp)

jmp_z_end:
	movl	%ebp, %esp
	pop	%ebp
	ret
