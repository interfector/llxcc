.text

.globl _start

_start:
	mov	$2,%ecx
	call *(table+4)
	
	mov	$1,%eax
	int	$0x80

func1:
	mov	%ecx, %ebx
	mov	$1,%eax
	int	$0x80

func2:
	mov	%ecx, %ebx
	mov	$1, %eax
	addl	$1, %ebx
	int	$0x80

exec_table:
	movl	4(%esp),%ebx
	addl	table,%ebx
	call	%ebx

table:
.long func1
.long func2
