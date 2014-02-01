cmp:
	push	%ebp
	movl %esp, %ebp

	xor %ecx, %ecx
	movl	8(%esp), %ebx
	push %eax
	movl	$10, %eax
	mul	%ebx
	movl	%eax, %ebx
	addl	%esi, %ebx
	movl 1(%ebx),%edi
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

