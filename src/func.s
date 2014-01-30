read:
	push	%ebp
	movl %esp, %ebp

	push	%eax
	push	%ecx

	xor	%edi, %edi

	cmp	$3,-16(%esi)
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
	movl	%edi, %eax
	and	$0x00FF, %eax
	movb	%al, 1(%ebx)
	movl	%edi, %eax
	and	$0xFF00, %eax
	sar	$0x8, %eax
	movb	%al, 3(%ebx)
	pop	%eax

	movl	%ebp, %esp
	pop	%ebp
	ret

write:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push	%ecx
	push	%eax
	movl	$11, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	movl	$100, %edi
	mul	%edi
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	addl	%ebx, %eax
	movl	%eax, %edi

	xor	%eax, %eax
	xor	%ebx, %ebx

	cmp	$3,-16(%esi)
	je	write_char	

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

ret:
	push	%ebp
	movl %esp, %ebp

	movl	-12(%esi),%edi
	subl	$4, %edi
	movl	%edi, -12(%esi)

	movl	-16(%esi), %ebx
	addl	-12(%esi), %ebx

	movl	(%ebx), %edi

	movl	%edi, 4(%esp)

	movl	%ebp, %esp
	pop	%ebp
	ret

call:
	push	%ebp
	movl %esp, %ebp

	movl	4(%esp), %edi

	movl	-16(%esi), %ebx
	addl	-12(%esi), %ebx

	movl	%edi, (%ebx)

	movl	-12(%esi),%ebx
	addl	$4, %ebx
	movl	%ebx, -12(%esi)

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	pop	%eax

	movl	%ebx, 4(%esp)

	movl	%ebp, %esp
	pop	%ebp
	ret

stpop:
	push	%ebp
	movl %esp, %ebp

	movl	-16(%esi),%ebx
	addl	-12(%esi), %ebx
	subl	$4, %ebx
	movl	(%ebx),%edi

	movl	8(%esp), %ebx
	push	%eax
	movl	$11, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	movl	%edi, %eax
	and	$0x00FF, %eax
	movb	%al, 1(%ebx)
	movl	%edi, %eax
	and	$0xFF00, %eax
	sar	$0x8, %eax
	movb	%al, 3(%ebx)
	pop	%eax

	movl	-12(%esi),%edi
	subl	$4, %edi
	movl	%edi, -12(%esi)

	movl	%ebp, %esp
	pop	%ebp
	ret


stpush:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push	%eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	movl	%eax, %edi
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

jmp_g:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
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
	movl	$9, %eax
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
	movl	$9, %eax
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
	movl	$9, %eax
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

cmp:
	push	%ebp
	movl %esp, %ebp

	xor %ecx, %ecx
	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	movl	%eax, %edi
	pop	%eax

	cmp	%edi, %eax
	jz	cmp_end
	cmp	%edi, %eax
	jl	cmp_jl
	cmp	%edi, %eax
	jg	cmp_jg

	jmp	cmp_end

cmp_jl:
	inc	%ecx
	jmp	cmp_end

cmp_jg:
	inc	%ecx
	inc	%ecx

cmp_end:

	movl %ebp, %esp
	pop	%ebp
	ret

jmp:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	pop	%eax

	movl	%ebx, 4(%esp)

	movl	%ebp, %esp
	pop	%ebp
	ret


dec:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx

	push %eax

	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	push	%ebx

	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax

	pop	%ebx

	dec	%eax

	movl	%eax, %edi

	and	$0x00FF, %eax
	movb	%al, 1(%ebx)
	movl	%edi, %eax
	and	$0xFF00, %eax
	sar	$0xc, %eax
	movb	%al, 3(%ebx)

	pop %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

inc:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx

	push %eax

	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	push	%ebx

	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax

	pop	%ebx

	inc	%eax

	movl	%eax, %edi

	and	$0x00FF, %eax
	movb	%al, 1(%ebx)
	movl	%edi, %eax
	and	$0xFF00, %eax
	sar	$0xc, %eax
	movb	%al, 3(%ebx)

	pop %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

chmod:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	movl	%ebx, -16(%esi)

	movl	%ebp, %esp
	pop	%ebp
	ret


del:
	push	%ebp
	movl %esp, %ebp

	movl	%eax, %edi

	movl	8(%esp), %ebx
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx

	movb	$0, 1(%ebx)
	movb	$0, 3(%ebx)

	movl	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

not:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax

	not	%eax

	movl	%ebp, %esp
	pop	%ebp
	ret

xor:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	pop	%edi

	xorl	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

or:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	pop	%edi

	orl	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

and:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	pop	%edi

	and	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

mod:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	movl	%eax, %edi
	pop	%eax
	push	%edx
	divl	%edi
	movl	%edx, %eax
	pop	%edx

	movl	%ebp, %esp
	pop	%ebp
	ret

div:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	movl	%eax, %edi
	pop	%eax
	push	%edx
	divl	%edi
	pop	%edx

	movl	%ebp, %esp
	pop	%ebp
	ret


mul:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	pop	%edi
	mul	%edi

	movl	%ebp, %esp
	pop	%ebp
	ret


sub:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %eax
	movl	%ebx, %edi
	xor	%ebx, %ebx
	movb 1(%edi),%bl
	or	%ebx, %eax
	pop	%edi
	subl	%eax, %edi
	movl	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret



add:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	push %eax
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %al
	or 1(%ebx),%al
	pop	%edi
	addl	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

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

pop:
	push	%ebp
	movl %esp, %ebp

	movl	%eax, %edi
	movl	8(%esp), %ebx
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	movl	%edi, %eax
	and	$0x00FF, %eax
	movb	%al, 1(%ebx)
	movl	%edi, %eax
	and	$0xFF00, %eax
	movb	%al, 3(%ebx)
	sar	$0xc, %eax
	movl	%edi, %eax

	movl	%ebp, %esp
	pop	%ebp
	ret

push:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp), %ebx
	movl	$9, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	xor	%eax, %eax
	movb	3(%ebx), %al
	shl	$8, %al
	or 1(%ebx),%al

	movl	%ebp, %esp
	pop	%ebp
	ret
