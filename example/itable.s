.text

.globl _start

_start:
	push	$4
	push	$0
	call exec_table
	
	mov	$1,%eax
	int	$0x80

func1:
	push	%ebp
	movl %esp, %ebp

	mov	8(%esp), %ebx
	mov	$1,%eax
	int	$0x80

	movl	%ebp, %esp
	pop	%ebp
	ret


func2:
	push	%ebp
	movl %esp, %ebp

	mov	8(%esp), %ebx
	mov	$1, %eax
	addl	$1, %ebx
	int	$0x80

	movl	%ebp, %esp
	pop	%ebp
	ret

exec_table:
	push	%ebp
	movl %esp, %ebp

	movl	8(%esp),%edi

	cmp	$10, %edi
	jl	end

	cmp	$47, %edi
	jg	end

	movl	%eax, %edi
	movl	8(%esp),%eax
	movl	$4, %ebx
	mul	%ebx
	movl	%eax, %ebx
	movl	%edi, %eax

	sub	$12, %eax

	push	12(%esp)
	push	%edx

	movl	$table, %edx
	addl	%edx,%ebx
	movl	(%ebx),%ebx

	pop	%edx

	call	%ebx

	pop	%ebx
end:
	movl	%ebp, %esp
	pop	%ebp
	ret

table:
.long func1
.long func2
