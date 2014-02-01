exec_table:

	push	%ebp 
	mov	%esp,%ebp 

	mov	0x8(%esp),%edi 

	xchg	%eax, %edi
	xor	%ebx, %ebx
	xor	%edx, %edx
	movb	$100, %ebx
	divl	%ebx
	xchg	%eax, %edi

	cmp	$0xa,%edi 
	jl	end
	cmp	$0x2f,%edi 
	jg	end

	push	%edx
	xchg	%eax, %edi
	sub	$10,%eax 
	mov	$0x4,%ebx 
	mul	%ebx 
	mov	%eax,%ebx 
	mov	%edi,%eax 
	pop	%edx

	push	%edx
	mov	$0xdeadc0de,%edi
	add	%edi,%ebx 
	mov	(%ebx),%ebx 
	call	*%ebx 
	pop	%ebx 

end:
	mov    %ebp,%esp 
	pop    %ebp 
	ret     

