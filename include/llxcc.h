#ifndef _LLXCC_
#define _LLXCC_

/* eax     Accumulator */
/* ebx     Use for calculating */
/* ecx     Flags */
/* -0x8(%esi)     Stack Pointer */
/* -0xc(%esi)     Stack index */
/* -0x10(%esi)    Mode */

#define MLBIT(size) static struct { unsigned char _dummy[size]; } const

MLBIT(48) init = { { 0xe8, 0x00, 0x00, 0x00, 0x00, /* call here */  /* mprotect( _start, 4096, PROT_READ|PROT_WRITE|PROT_EXEC ); */
				 0x31, 0xc0, /* xor %eax,%eax */ 
				 0xb0, 0x7d, /* mov $125,%eax */
				 0xb9, 0xff, 0x0f, 0x00, 0x00, /* mov $0x0fff,%ecx */
				 0xf7, 0xd1, /* not %ecx */
				 0x5b, /* pop %ebx */
				 0x83, 0xeb, 0x05, /* sub $5,%ebx */
				 0x21, 0xcb, /* and %ecx,%ebx */
				 0xb9, 0x00, 0x10, 0x00, 0x00, /* mov $4096,%ecx */
				 0x31, 0xd2, /* xor %edx,%edx */
				 0xb2, 0x07, /* mov $7,%edx */
				 0xcd, 0x80, /* int $0x80 */

				 0x31, 0xc0, /* xor %eax,%eax */
				 0x31, 0xdb, /* xor %ebx,%ebx */
				 0x31, 0xc9, /* xor %ecx,%ecx */
				 0x31, 0xd2, /* xor %edx,%edx */
				 0x31, 0xf6, /* xor %esi,%esi */
				 0x31, 0xff, /* xor %edi,%edi */
				 0x90, 0x90, 0x90 /* nops */
			  } };

MLBIT(29) load_mem = { {  
	/* 0x8d, 0x35, */ /* lea mem,%esi */
	/* 0x00, 0x00, 0x00, 0x00,*/  /* Memory to load */	
	0xe8, 0x00, 0x00, 0x00, 0x00, /* call here */
	0x5e, /* pop %esi */
	0x66, 0x83, 0xc6, 0x18, /* add $0xc(0x5),%esi */
	0x89,0xe3,                    	/* *** mov    %esp,%ebx */
	0x81,0xc3,0xe8,0x03,0x00,0x00,	/* *** add    $0x3e8,%ebx */
	0x89,0x5e,0xf0,               	/* *** mov    %ebx,-0x10(%esi) */
	0x31,0xdb,                    	/* *** xor    %ebx,%ebx */
	0x89,0x5e,0xf4,               	/* *** mov    %ebx,-0xc(%esi) */
	0x89,0x5e,0xec,               	/* *** mov    %ebx,-0x14(%esi) */
} };

MLBIT(5) null_code = { { 0x90, 0x90, 0x90, 0x90, 0x90 } };

MLBIT(10) opcode_set = { {
/* 0000 */	0x68,0xde,0xad,0xc0,0xde,     	/* push   $0xdeadc0de */
/* 0005 */	0xe8,0xde,0xad,0xc0,0xde,     	/* call   a <here> */
} };

MLBIT(59) exec_table = {{
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x7c,0x24,0x08,          	/* mov    0x8(%esp),%edi */
/* 0007 */	0x97,                         	/* xchg   %eax,%edi */
/* 0008 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 000a */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 000c */	0xb3,0x64,                    	/* mov    $0x64,%bl */
/* 000e */	0xf7,0xf3,                    	/* div    %ebx */
/* 0010 */	0x97,                         	/* xchg   %eax,%edi */
/* 0011 */	0x83,0xff,0x0a,               	/* cmp    $0xa,%edi */
/* 0014 */	0x7c,0x23,                    	/* jl     39 <end> */
/* 0016 */	0x83,0xff,0x2f,               	/* cmp    $0x2f,%edi */
/* 0019 */	0x7f,0x1e,                    	/* jg     39 <end> */
/* 001b */	0x52,                         	/* push   %edx */
/* 001c */	0x97,                         	/* xchg   %eax,%edi */
/* 001d */	0x83,0xe8,0x0a,               	/* sub    $0xa,%eax */
/* 0020 */	0xbb,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%ebx */
/* 0025 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0027 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0029 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 002d */	0xbf,0xde,0xad,0xc0,0xde,     	/* mov    $0xdeadc0de,%edi */
/* 0032 */	0x01,0xfb,                    	/* add    %edi,%ebx */
/* 0034 */	0x8b,0x1b,                    	/* mov    (%ebx),%ebx */
/* 0036 */	0xff,0xd3,                    	/* call   *%ebx */
/* 0038 */	0x5b,                         	/* pop    %ebx */
/* 0039 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 003b */	0x5d,                         	/* pop    %ebp */
/* 003c */	0xc3,                         	/* ret     */
} };

//MLBIT(68) exec_table = {{
//* 0000 */	0x55,                         	/* push   %ebp */
//* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
//* 0003 */	0x8b,0x7c,0x24,0x08,          	/* mov    0x8(%esp),%edi */
//* 001f */	0x97,                         	/* xchg   %eax,%edi */
//* 0008 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
//* 000a */	0xb3,0x64,                    	/* mov    $0x64,%bl */
//* 000c */	0xf6,0xf3,                    	/* div    %bl */
//* 000f */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
//* 0011 */	0x88,0xc3,                    	/* mov    %al,%bl */
//* 0013 */	0x97,                         	/* xchg   %eax,%edi */
//* 0013 */	0x89,0xfa,                    	/* mov    %edi,%edx */
//* 0014 */	0x89,0xdf,                    	/* mov    %ebx,%edi */
//* 0014 */	0x83,0xff,0x0a,               	/* cmp    $0xa,%edi */
//* 0017 */	0x7c,0x23,                    	/* jl     3c <end> */
//* 0019 */	0x83,0xff,0x2f,               	/* cmp    $0x2f,%edi */
//* 001c */	0x7f,0x1e,                    	/* jg     3c <end> */
//* 0021 */	0xc1,0xfa,0x08,               	/* sar    $0x8,%edx */
//* 001e */	0x52,                         	/* push   %edx */
//* 001f */	0x97,                         	/* xchg   %eax,%edi */
//* 0020 */	0x83,0xe8,0x0a,               	/* sub    $0xa,%eax */
//* 0023 */	0xbb,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%ebx */
//* 0028 */	0xf7,0xe3,                    	/* mul    %ebx */
//* 002a */	0x89,0xc3,                    	/* mov    %eax,%ebx */
//* 002c */	0x89,0xf8,                    	/* mov    %edi,%eax */
//* 0030 */	0xbf,0xde,0xad,0xc0,0xde,     	/* mov    $0xdeadc0de,%edi */
//* 0035 */	0x01,0xfb,                    	/* add    %edi,%ebx */
//* 0037 */	0x8b,0x1b,                    	/* mov    (%ebx),%ebx */
//* 0039 */	0xff,0xd3,                    	/* call   *%ebx */
//* 003b */	0x5b,                         	/* pop    %ebx */
//* 003c */	0x89,0xec,                    	/* mov    %ebp,%esp */
//* 003e */	0x5d,                         	/* pop    %ebp */
//* 003f */	0xc3,                         	/* ret     */
//} };


MLBIT(131) mwrite_old = { { 
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x51,                         	/* push   %ecx */
/* 0008 */	0x50,                         	/* push   %eax */
/* 0009 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000e */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0010 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0012 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0014 */	0x8b,0x7b,0x01,               	/* mov    0x1(%ebx),%edi */
/* 0017 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0019 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 001b */	0x83,0x7e,0xec,0x03,          	/* cmpl   $0x3,-0x14(%esi) */
/* 001f */	0x74,0x47,                    	/* je     68 <write_char> */
/* 0021 */	0x83,0xff,0x00,               	/* cmp    $0x0,%edi */
/* 0024 */	0x7e,0x13,                    	/* jle    39 <write_loop_init> */
/* 0026 */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 0028 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 002a */	0xb9,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%ecx */
/* 002f */	0xf7,0xf1,                    	/* div    %ecx */
/* 0031 */	0x89,0xd7,                    	/* mov    %edx,%edi */
/* 0033 */	0x57,                         	/* push   %edi */
/* 0034 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0036 */	0x43,                         	/* inc    %ebx */
/* 0037 */	0xeb,0xe8,                    	/* jmp    21 <push_loop> */
/* 0039 */	0x31,0xff,                    	/* xor    %edi,%edi */
/* 003b */	0x39,0xfb,                    	/* cmp    %edi,%ebx */
/* 003d */	0x74,0x23,                    	/* je     62 <write_exit> */
/* 003f */	0x83,0x04,0x24,0x30,          	/* addl   $0x30,(%esp) */
/* 0043 */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 0045 */	0x53,                         	/* push   %ebx */
/* 0046 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0048 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 004a */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 004c */	0xb8,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%eax */
/* 0051 */	0xbb,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%ebx */
/* 0056 */	0xba,0x02,0x00,0x00,0x00,     	/* mov    $0x2,%edx */
/* 005b */	0xcd,0x80,                    	/* int    $0x80 */
/* 005d */	0x5b,                         	/* pop    %ebx */
/* 005e */	0x59,                         	/* pop    %ecx */
/* 005f */	0x47,                         	/* inc    %edi */
/* 0060 */	0xeb,0xd9,                    	/* jmp    3b <write_loop> */
/* 0062 */	0x6a,0x0a,                    	/* push   $0xa */
/* 0064 */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 0066 */	0xeb,0x03,                    	/* jmp    6b <wexit> */
/* 0068 */	0x57,                         	/* push   %edi */
/* 0069 */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 006b */	0xb8,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%eax */
/* 0070 */	0xbb,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%ebx */
/* 0075 */	0xba,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%edx */
/* 007a */	0xcd,0x80,                    	/* int    $0x80 */
/* 007c */	0x5b,                         	/* pop    %ebx */
/* 007d */	0x58,                         	/* pop    %eax */
/* 007e */	0x59,                         	/* pop    %ecx */
/* 007f */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0081 */	0x5d,                         	/* pop    %ebp */
/* 0082 */	0xc3,                         	/* ret     */
} };

MLBIT(142) mwrite = { { 
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x51,                         	/* push   %ecx */
/* 0008 */	0x50,                         	/* push   %eax */
/* 0009 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000e */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0010 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0012 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0014 */	0x8b,0x7b,0x01,               	/* mov    0x1(%ebx),%edi */
/* 0017 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0019 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 001b */	0x83,0x7e,0xec,0x03,          	/* cmpl   $0x3,-0x14(%esi) */
/* 001f */	0x74,0x52,                    	/* je     73 <write_char> */
/* 0021 */	0x83,0xff,0x00,               	/* cmp    $0x0,%edi */
/* 0024 */	0x74,0x02,                    	/* je     28 <zero_push> */
/* 0026 */	0xeb,0x04,                    	/* jmp    2c <push_loop> */
/* 0028 */	0x57,                         	/* push   %edi */
/* 0029 */	0x43,                         	/* inc    %ebx */
/* 002a */	0xeb,0x18,                    	/* jmp    44 <write_loop_init> */
/* 002c */	0x83,0xff,0x00,               	/* cmp    $0x0,%edi */
/* 002f */	0x7e,0x13,                    	/* jle    44 <write_loop_init> */
/* 0031 */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 0033 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0035 */	0xb9,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%ecx */
/* 003a */	0xf7,0xf1,                    	/* div    %ecx */
/* 003c */	0x89,0xd7,                    	/* mov    %edx,%edi */
/* 003e */	0x57,                         	/* push   %edi */
/* 003f */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0041 */	0x43,                         	/* inc    %ebx */
/* 0042 */	0xeb,0xe8,                    	/* jmp    2c <push_loop> */
/* 0044 */	0x31,0xff,                    	/* xor    %edi,%edi */
/* 0046 */	0x39,0xfb,                    	/* cmp    %edi,%ebx */
/* 0048 */	0x74,0x23,                    	/* je     6d <write_exit> */
/* 004a */	0x83,0x04,0x24,0x30,          	/* addl   $0x30,(%esp) */
/* 004e */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 0050 */	0x53,                         	/* push   %ebx */
/* 0051 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0053 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0055 */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 0057 */	0xb8,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%eax */
/* 005c */	0xbb,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%ebx */
/* 0061 */	0xba,0x02,0x00,0x00,0x00,     	/* mov    $0x2,%edx */
/* 0066 */	0xcd,0x80,                    	/* int    $0x80 */
/* 0068 */	0x5b,                         	/* pop    %ebx */
/* 0069 */	0x59,                         	/* pop    %ecx */
/* 006a */	0x47,                         	/* inc    %edi */
/* 006b */	0xeb,0xd9,                    	/* jmp    46 <write_loop> */
/* 006d */	0x6a,0x0a,                    	/* push   $0xa */
/* 006f */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 0071 */	0xeb,0x03,                    	/* jmp    76 <wexit> */
/* 0073 */	0x57,                         	/* push   %edi */
/* 0074 */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 0076 */	0xb8,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%eax */
/* 007b */	0xbb,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%ebx */
/* 0080 */	0xba,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%edx */
/* 0085 */	0xcd,0x80,                    	/* int    $0x80 */
/* 0087 */	0x5b,                         	/* pop    %ebx */
/* 0088 */	0x58,                         	/* pop    %eax */
/* 0089 */	0x59,                         	/* pop    %ecx */
/* 008a */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 008c */	0x5d,                         	/* pop    %ebp */
/* 008d */	0xc3,                         	/* ret     */
} };

MLBIT(144) mread = { { 
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x50,                         	/* push   %eax */
/* 0004 */	0x51,                         	/* push   %ecx */
/* 0005 */	0x31,0xff,                    	/* xor    %edi,%edi */
/* 0007 */	0x83,0x7e,0xec,0x03,          	/* cmpl   $0x3,-0x14(%esi) */
/* 000b */	0x74,0x47,                    	/* je     54 <read_char> */
/* 000d */	0xb8,0x03,0x00,0x00,0x00,     	/* mov    $0x3,%eax */
/* 0012 */	0xbb,0x00,0x00,0x00,0x00,     	/* mov    $0x0,%ebx */
/* 0017 */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 0019 */	0x81,0xe9,0xe8,0x03,0x00,0x00,	/* sub    $0x3e8,%ecx */
/* 001f */	0xba,0x0c,0x00,0x00,0x00,     	/* mov    $0xc,%edx */
/* 0024 */	0xcd,0x80,                    	/* int    $0x80 */
/* 0026 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0028 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 002a */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 002c */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 002e */	0x80,0x3c,0x19,0x30,          	/* cmpb   $0x30,(%ecx,%ebx,1) */
/* 0032 */	0x7c,0x40,                    	/* jl     74 <read_exit> */
/* 0034 */	0x80,0x3c,0x19,0x39,          	/* cmpb   $0x39,(%ecx,%ebx,1) */
/* 0038 */	0x7f,0x3a,                    	/* jg     74 <read_exit> */
/* 003a */	0x39,0xdf,                    	/* cmp    %ebx,%edi */
/* 003c */	0x74,0x36,                    	/* je     74 <read_exit> */
/* 003e */	0x57,                         	/* push   %edi */
/* 003f */	0xbf,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%edi */
/* 0044 */	0xf7,0xe7,                    	/* mul    %edi */
/* 0046 */	0x5f,                         	/* pop    %edi */
/* 0047 */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 0049 */	0x8a,0x14,0x19,               	/* mov    (%ecx,%ebx,1),%dl */
/* 004c */	0x83,0xea,0x30,               	/* sub    $0x30,%edx */
/* 004f */	0x01,0xd0,                    	/* add    %edx,%eax */
/* 0051 */	0x43,                         	/* inc    %ebx */
/* 0052 */	0xeb,0xda,                    	/* jmp    2e <read_loop> */
/* 0054 */	0xb8,0x03,0x00,0x00,0x00,     	/* mov    $0x3,%eax */
/* 0059 */	0xbb,0x00,0x00,0x00,0x00,     	/* mov    $0x0,%ebx */
/* 005e */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 0060 */	0x81,0xe9,0xe8,0x03,0x00,0x00,	/* sub    $0x3e8,%ecx */
/* 0066 */	0xba,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%edx */
/* 006b */	0xcd,0x80,                    	/* int    $0x80 */
/* 006d */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 006f */	0x8a,0x14,0x19,               	/* mov    (%ecx,%ebx,1),%dl */
/* 0072 */	0x89,0xd0,                    	/* mov    %edx,%eax */
/* 0074 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0076 */	0x59,                         	/* pop    %ecx */
/* 0077 */	0x58,                         	/* pop    %eax */
/* 0078 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 007c */	0x50,                         	/* push   %eax */
/* 007d */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 0082 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0084 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0086 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0088 */	0x89,0x7b,0x01,               	/* mov    %edi,0x1(%ebx) */
/* 008b */	0x58,                         	/* pop    %eax */
/* 008c */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 008e */	0x5d,                         	/* pop    %ebp */
/* 008f */	0xc3,                         	/* ret     */
} };

MLBIT(29) pop = { { 
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0005 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0009 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000e */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0010 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0012 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0014 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0016 */	0x89,0x43,0x01,               	/* mov    %eax,0x1(%ebx) */
/* 0019 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001b */	0x5d,                         	/* pop    %ebp */
/* 001c */	0xc3,                         	/* ret     */
} };

MLBIT(25) push = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000c */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000e */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0010 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0012 */	0x8b,0x43,0x01,               	/* mov    0x1(%ebx),%eax */
/* 0015 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0017 */	0x5d,                         	/* pop    %ebp */
/* 0018 */	0xc3,                         	/* ret     */
} };

MLBIT(31) add = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0015 */	0x8b,0x43,0x01,               	/* mov    0x1(%ebx),%eax */
/* 0018 */	0x5f,                         	/* pop    %edi */
/* 0019 */	0x01,0xf8,                    	/* add    %edi,%eax */
/* 001b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001d */	0x5d,                         	/* pop    %ebp */
/* 001e */	0xc3,                         	/* ret     */
} };

MLBIT(31) sub = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x8b,0x43,0x01,               	/* mov    0x1(%ebx),%eax */
/* 0016 */	0x5f,                         	/* pop    %edi */
/* 0017 */	0x29,0xc7,                    	/* sub    %eax,%edi */
/* 0019 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 001b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001d */	0x5d,                         	/* pop    %ebp */
/* 001e */	0xc3,                         	/* ret     */
} };

MLBIT(29) mul = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x8b,0x43,0x01,               	/* mov    0x1(%ebx),%eax */
/* 0016 */	0x5f,                         	/* pop    %edi */
/* 0017 */	0xf7,0xe7,                    	/* mul    %edi */
/* 0019 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001b */	0x5d,                         	/* pop    %ebp */
/* 001c */	0xc3,                         	/* ret     */
} };

MLBIT(31) mdiv = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x8b,0x7b,0x01,               	/* mov    0x1(%ebx),%edi */
/* 0016 */	0x58,                         	/* pop    %eax */
/* 0017 */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 0019 */	0xf7,0xf7,                    	/* div    %edi */
/* 001b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001d */	0x5d,                         	/* pop    %ebp */
/* 001e */	0xc3,                         	/* ret     */
} };

MLBIT(33) mod = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x8b,0x7b,0x01,               	/* mov    0x1(%ebx),%edi */
/* 0016 */	0x58,                         	/* pop    %eax */
/* 0017 */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 0019 */	0xf7,0xf7,                    	/* div    %edi */
/* 001b */	0x89,0xd0,                    	/* mov    %edx,%eax */
/* 001d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001f */	0x5d,                         	/* pop    %ebp */
/* 0020 */	0xc3,                         	/* ret     */
} };

MLBIT(29) and = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x8b,0x43,0x01,               	/* mov    0x1(%ebx),%eax */
/* 0016 */	0x5f,                         	/* pop    %edi */
/* 0017 */	0x21,0xf8,                    	/* and    %edi,%eax */
/* 0019 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001b */	0x5d,                         	/* pop    %ebp */
/* 001c */	0xc3,                         	/* ret     */
} };

MLBIT(29) or = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x8b,0x43,0x01,               	/* mov    0x1(%ebx),%eax */
/* 0016 */	0x5f,                         	/* pop    %edi */
/* 0017 */	0x09,0xf8,                    	/* or     %edi,%eax */
/* 0019 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001b */	0x5d,                         	/* pop    %ebp */
/* 001c */	0xc3,                         	/* ret     */
} };

MLBIT(29) xor = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x8b,0x43,0x01,               	/* mov    0x1(%ebx),%eax */
/* 0016 */	0x5f,                         	/* pop    %edi */
/* 0017 */	0x31,0xf8,                    	/* xorl   %edi,%eax */
/* 0019 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001b */	0x5d,                         	/* pop    %ebp */
/* 001c */	0xc3,                         	/* ret     */
} };

MLBIT(27) not = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000c */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000e */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0010 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0012 */	0x8b,0x43,0x01,               	/* mov    0x1(%ebx),%eax */
/* 0015 */	0xf7,0xd0,                    	/* not    %eax */
/* 0017 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0019 */	0x5d,                         	/* pop    %ebp */
/* 001a */	0xc3,                         	/* ret     */
} };

MLBIT(34) del = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0005 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0009 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000e */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0010 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0012 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0014 */	0xc7,0x43,0x01,0x00,0x00,0x00,0x00,	/* movl   $0x0,0x1(%ebx) */
/* 001b */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 001d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001f */	0x5d,                         	/* pop    %ebp */
/* 0020 */	0xc3,                         	/* ret     */
} };

MLBIT(8) nop = {{
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x90,						/* nop */
/* 0004 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0006 */	0x5d,                         	/* pop    %ebp */
/* 0007 */	0xc3,                         	/* ret     */
} };

MLBIT(17) mexit = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0009 */	0xb0,0x01,                    	/* mov    $0x1,%al */
/* 000b */	0xcd,0x80,                    	/* int    $0x80 */
/* 000d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 000f */	0x5d,                         	/* pop    %ebp */
/* 0010 */	0xc3,                         	/* ret     */
} };

MLBIT(14) mchmod = { {
/* 0301 */	0x55,                         	/* push   %ebp */
/* 0302 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0304 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0308 */	0x89,0x5e,0xec,               	/* mov    %ebx,-0x14(%esi) */
/* 030b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 030d */	0x5d,                         	/* pop    %ebp */
/* 030e */	0xc3,                         	/* ret     */
} };

MLBIT(28) inc = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x83,0x43,0x01,0x01,          	/* addl   $0x1,0x1(%ebx) */
/* 0017 */	0x58,                         	/* pop    %eax */
/* 0018 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001a */	0x5d,                         	/* pop    %ebp */
/* 001b */	0xc3,                         	/* ret     */
} };

MLBIT(28) dec = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x83,0x6b,0x01,0x01,          	/* subl   $0x1,0x1(%ebx) */
/* 0017 */	0x58,                         	/* pop    %eax */
/* 0018 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001a */	0x5d,                         	/* pop    %ebp */
/* 001b */	0xc3,                         	/* ret     */
} };

MLBIT(28) abs_jmp = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x0a,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x58,                         	/* pop    %eax */
/* 0014 */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
/* 0018 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001a */	0x5d,                         	/* pop    %ebp */
/* 001b */	0xc3,                         	/* ret     */
} };

//MLBIT(16) short_call = { { 0x90, 0x90, 0x90, /* nops */
//					  0xe8, 0x00, 0x00, 0x00, 0x00, /* call here */
//					  0x5b, /* pop %ebx */
//					  0x83, 0xc3, 0x08, /* add $0x08,%ebx */
//					  0x89, 0xdd, /* mov %ebx,%ebp */
//					  0xeb, 0x00 /* jmp short */
//				   } };

//MLBIT(49) abs_call = { {
//* 0000 */	0x55,                         	/* push   %ebp */
//* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
//* 0003 */	0x8b,0x7c,0x24,0x10,          	/* mov    0x10(%esp),%edi */
//* 0007 */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
//* 000a */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
//* 000d */	0x89,0x3b,                    	/* mov    %edi,(%ebx) */
//* 000f */	0x8b,0x5e,0xf4,               	/* mov    -0xc(%esi),%ebx */
//* 0012 */	0x83,0xc3,0x04,               	/* add    $0x4,%ebx */
//* 0015 */	0x89,0x5e,0xf4,               	/* mov    %ebx,-0xc(%esi) */
//* 0018 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
//* 001c */	0x50,                         	/* push   %eax */
//* 001d */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
//* 0022 */	0xf7,0xe3,                    	/* mul    %ebx */
//* 0024 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
//* 0026 */	0x01,0xf3,                    	/* add    %esi,%ebx */
//* 0028 */	0x58,                         	/* pop    %eax */
//* 0029 */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
//* 002d */	0x89,0xec,                    	/* mov    %ebp,%esp */
//* 002f */	0x5d,                         	/* pop    %ebp */
//* 0030 */	0xc3,                         	/* ret     */
//} };

MLBIT(66) abs_call = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x7c,0x24,0x10,          	/* mov    0x10(%esp),%edi */
/* 0007 */	0x29,0xf7,                    	/* sub    %esi,%edi */
/* 000c */	0x50,                         	/* push   %eax */
/* 000d */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 000f */	0xbf,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%edi */
/* 0011 */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 0014 */	0xf7,0xf7,                    	/* div    %edi */
/* 0016 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0018 */	0x58,                         	/* pop    %eax */
/* 0019 */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
/* 001c */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
/* 001f */	0x89,0x3b,                    	/* mov    %edi,(%ebx) */
/* 0021 */	0x8b,0x5e,0xf4,               	/* mov    -0xc(%esi),%ebx */
/* 0024 */	0x83,0xc3,0x04,               	/* add    $0x4,%ebx */
/* 0027 */	0x89,0x5e,0xf4,               	/* mov    %ebx,-0xc(%esi) */
/* 002a */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 002e */	0x50,                         	/* push   %eax */
/* 002f */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 0034 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0036 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0038 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 003a */	0x58,                         	/* pop    %eax */
/* 003b */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
/* 003f */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0041 */	0x5d,                         	/* pop    %ebp */
/* 0042 */	0xc3,                         	/* ret     */
} };

MLBIT(43) ret = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x7e,0xf4,               	/* mov    -0xc(%esi),%edi */
/* 0006 */	0x83,0xef,0x04,               	/* sub    $0x4,%edi */
/* 0009 */	0x89,0x7e,0xf4,               	/* mov    %edi,-0xc(%esi) */
/* 000c */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
/* 000f */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
/* 0012 */	0x8b,0x3b,                    	/* mov    (%ebx),%edi */
/* 0014 */	0x89,0xfb,                    	/* mov    %edi,%ebx */
/* 0016 */	0x50,                         	/* push   %eax */
/* 0017 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xb,%eax */
/* 001c */	0xf7,0xe3,                    	/* mul    %ebx */
/* 001e */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0020 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0022 */	0x58,                         	/* pop    %eax */
/* 0023 */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
/* 0027 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0029 */	0x5d,                         	/* pop    %ebp */
/* 002a */	0xc3,                         	/* ret     */
} };

MLBIT(44) stpush = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x8b,0x7b,0x01,               	/* mov    0x1(%ebx),%edi */
/* 0016 */	0x58,                         	/* pop    %eax */
/* 0017 */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
/* 001a */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
/* 001d */	0x89,0x3b,                    	/* mov    %edi,(%ebx) */
/* 001f */	0x8b,0x5e,0xf4,               	/* mov    -0xc(%esi),%ebx */
/* 0022 */	0x83,0xc3,0x04,               	/* add    $0x4,%ebx */
/* 0025 */	0x89,0x5e,0xf4,               	/* mov    %ebx,-0xc(%esi) */
/* 0028 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 002a */	0x5d,                         	/* pop    %ebp */
/* 002b */	0xc3,                         	/* ret     */
} };

MLBIT(47) stpop = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
/* 0006 */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
/* 0009 */	0x83,0xeb,0x04,               	/* sub    $0x4,%ebx */
/* 000c */	0x8b,0x3b,                    	/* mov    (%ebx),%edi */
/* 000e */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0012 */	0x50,                         	/* push   %eax */
/* 0013 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 0018 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 001a */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 001c */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 001e */	0x89,0x7b,0x01,               	/* mov    %edi,0x1(%ebx) */
/* 0021 */	0x58,                         	/* pop    %eax */
/* 0022 */	0x8b,0x7e,0xf4,               	/* mov    -0xc(%esi),%edi */
/* 0025 */	0x83,0xef,0x04,               	/* sub    $0x4,%edi */
/* 0028 */	0x89,0x7e,0xf4,               	/* mov    %edi,-0xc(%esi) */
/* 002b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 002d */	0x5d,                         	/* pop    %ebp */
/* 002e */	0xc3,                         	/* ret     */
} };

MLBIT(48) cmp = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x31,0xc9,                    	/* xor    %ecx,%ecx */
/* 0005 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0009 */	0x50,                         	/* push   %eax */
/* 000a */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%eax */
/* 000f */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0011 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0013 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0015 */	0x8b,0x7b,0x01,               	/* mov    0x1(%ebx),%edi */
/* 0018 */	0x58,                         	/* pop    %eax */
/* 0019 */	0x39,0xf8,                    	/* cmp    %edi,%eax */
/* 001b */	0x74,0x0f,                    	/* je     2c <cmp_end> */
/* 001d */	0x39,0xf8,                    	/* cmp    %edi,%eax */
/* 001f */	0x7c,0x06,                    	/* jl     27 <cmp_jl> */
/* 0021 */	0x39,0xf8,                    	/* cmp    %edi,%eax */
/* 0023 */	0x7f,0x05,                    	/* jg     2a <cmp_jg> */
/* 0025 */	0xeb,0x05,                    	/* jmp    2c <cmp_end> */
/* 0027 */	0x41,                         	/* inc    %ecx */
/* 0028 */	0xeb,0x02,                    	/* jmp    2c <cmp_end> */
/* 002a */	0x41,                         	/* inc    %ecx */
/* 002b */	0x41,                         	/* inc    %ecx */
/* 002c */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 002e */	0x5d,                         	/* pop    %ebp */
/* 002f */	0xc3,                         	/* ret     */
} };

MLBIT(33) abs_jz = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x58,                         	/* pop    %eax */
/* 0014 */	0x83,0xf9,0x00,               	/* cmp    $0x0,%ecx */
/* 0017 */	0x75,0x04,                    	/* jne    1d <jmp_z_end> */
/* 0019 */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
/* 001d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001f */	0x5d,                         	/* pop    %ebp */
/* 0020 */	0xc3,                         	/* ret     */
} };

MLBIT(33) abs_jn = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x58,                         	/* pop    %eax */
/* 0014 */	0x83,0xf9,0x00,               	/* cmp    $0x0,%ecx */
/* 0017 */	0x74,0x04,                    	/* je     1d <jmp_n_end> */
/* 0019 */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
/* 001d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001f */	0x5d,                         	/* pop    %ebp */
/* 0020 */	0xc3,                         	/* ret     */
} };

MLBIT(33) abs_jm = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x58,                         	/* pop    %eax */
/* 0014 */	0x83,0xf9,0x01,               	/* cmp    $0x1,%ecx */
/* 0017 */	0x75,0x04,                    	/* jne    1d <jmp_m_end> */
/* 0019 */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
/* 001d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001f */	0x5d,                         	/* pop    %ebp */
/* 0020 */	0xc3,                         	/* ret     */
} };

MLBIT(33) abs_jg = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0a,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x58,                         	/* pop    %eax */
/* 0014 */	0x83,0xf9,0x02,               	/* cmp    $0x2,%ecx */
/* 0017 */	0x75,0x04,                    	/* jne    1d <jmp_g_end> */
/* 0019 */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
/* 001d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001f */	0x5d,                         	/* pop    %ebp */
/* 0020 */	0xc3,                         	/* ret     */
} };

MLBIT(12) shl = { { 0x89, 0xcb, /* mov %ecx,%ebx */
			     0x31, 0xc9, /* xor %ecx,%ecx */
			     0x8a, 0x0c, 0x3e, /* mov (%esi,%edi),%ecx */
			     0xd3, 0xe0, /* shl %cl,%eax */
			     0x89, 0xd9, /* mov %ebx,%ecx */
			     0x90 /* nop */
			 } };
			
MLBIT(12) sar = { { 0x89, 0xcb, /* mov %ecx,%ebx */
			     0x31, 0xc9, /* xor %ecx,%ecx */
			     0x8a, 0x0c, 0x3e, /* mov (%esi,%edi),%ecx */
			     0xd3, 0xf8, /* sar %cl,%eax */
			     0x89, 0xd9, /* mov %ebx,%ecx */
			     0x90 /* nop */
			 } };

MLBIT(28) addsp = { {
/* 001c */	0x55,                         	/* push   %ebp */
/* 001d */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 001f */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0023 */	0x50,                         	/* push   %eax */
/* 0024 */	0xb8,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%eax */
/* 0029 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 002b */	0x8b,0x7e,0xf4,               	/* mov    -0xc(%esi),%edi */
/* 002e */	0x01,0xc7,                    	/* add    %eax,%edi */
/* 0030 */	0x89,0x7e,0xf4,               	/* mov    %edi,-0xc(%esi) */
/* 0033 */	0x58,                         	/* pop    %eax */
/* 0034 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0036 */	0x5d,                         	/* pop    %ebp */
/* 0037 */	0xc3,                         	/* ret     */
} };

MLBIT(28) subsp = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x8b,0x7e,0xf4,               	/* mov    -0xc(%esi),%edi */
/* 0012 */	0x29,0xc7,                    	/* sub    %eax,%edi */
/* 0014 */	0x89,0x7e,0xf4,               	/* mov    %edi,-0xc(%esi) */
/* 0017 */	0x58,                         	/* pop    %eax */
/* 0018 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001a */	0x5d,                         	/* pop    %ebp */
/* 001b */	0xc3,                         	/* ret     */
} };

struct lxs_code {
	int instr, opcode;

	char* code;
	int code_size;
};

struct lxs_code instruction_set[] = {
	/* read, write */
	{ 10, 0, (char*)&mread, sizeof( mread ) },
	{ 11, 0, (char*)&mwrite, sizeof( mwrite ) },
	{ 12, 0, (char*)&pop, sizeof( pop ) },
	{ 13, 0, (char*)&push, sizeof( push ) },
	{ 14, 0, (char*)&add, sizeof( add ) },
	{ 15, 0, (char*)&sub, sizeof( sub ) },
	{ 16, 0, (char*)&mul, sizeof( mul ) },
	{ 17, 0, (char*)&mdiv, sizeof( mdiv ) },
	{ 18, 0, (char*)&mod, sizeof( mod ) },
	{ 19, 0, (char*)&and, sizeof( and ) },
	{ 20, 0, (char*)&or, sizeof( or ) },
	{ 21, 0, (char*)&xor, sizeof( xor ) },
	{ 22, 0, (char*)&not, sizeof( not ) },
	{ 23, 0, (char*)&nop, sizeof( nop ) },
	{ 24, 0, (char*)&nop, sizeof( nop ) },
	{ 25, 0, (char*)&del, sizeof( del ) },
	{ 26, 1, (char*)&nop, sizeof( nop ) },
	{ 27, 0, (char*)&abs_jmp, sizeof( abs_jmp ) }, /* Absolute jumps using */
	{ 28, 0, (char*)&cmp, sizeof( cmp ) },
	{ 29, 0, (char*)&abs_jn, sizeof( abs_jn ) },
	{ 30, 0, (char*)&abs_jz, sizeof( abs_jz ) },
	{ 31, 0, (char*)&abs_jm, sizeof( abs_jm ) },
	{ 32, 0, (char*)&abs_jg, sizeof( abs_jg ) },
	{ 33, 0, (char*)&mexit, sizeof( mexit ) },
	{ 34, 0, (char*)&mchmod, sizeof( mchmod ) },
	{ 35, 0, (char*)&inc, sizeof( inc ) },
	{ 36, 0, (char*)&dec, sizeof( dec ) },
	{ 37, 0, (char*)&abs_call, sizeof( abs_call ) },
	{ 38, 1, (char*)&ret, sizeof( ret ) },
	{ 39, 0, (char*)&stpush, sizeof( stpush ) },
	{ 40, 0, (char*)&stpop, sizeof( stpop ) },
	{ 41, 0, (char*)&addsp, sizeof( addsp ) },
	{ 42, 0, (char*)&subsp, sizeof( subsp ) },
	{ 43, 0, (char*)&not, sizeof( not ) },
};

#define LEN (sizeof(instruction_set)/sizeof(struct lxs_code))

#endif /* _LLXCC_ */
