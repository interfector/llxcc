#ifndef _LLXCC_
#define _LLXCC_

/* eax     Accumulator */
/* ebx     Use for calculating */
/* ecx     Flags */
/* edx     Mode */
/* ebp     Old EIP */
/* esp     Stack */

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
	0x89,0x5e,0xf0,               	/* *** mov    %ebx,-0x10(%esi) */
} };

MLBIT(5) null_code = { { 0x90, 0x90, 0x90, 0x90, 0x90 } };

MLBIT(11) opcode_set = { { 0x6a, 0x00, /* push val */
					 0x6a, 0x00, /* push opcode */
					 0xe8, 0xde, 0xad, 0xc0, 0xde, /* call exec_table */
					 0x5b, 0x5b /* pop %ebx (x2) */
				  } };

MLBIT(60) exec_table = {{
/* 0037 */	0x55,                         	/* push   %ebp */
/* 0038 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 003a */	0x8b,0x7c,0x24,0x08,          	/* mov    0x8(%esp),%edi */
/* 003e */	0x83,0xff,0x0a,               	/* cmp    $0xa,%edi */
/* 0041 */	0x7c,0x2b,                    	/* jl     6e <end> */
/* 0043 */	0x83,0xff,0x2f,               	/* cmp    $0x2f,%edi */
/* 0046 */	0x7f,0x26,                    	/* jg     6e <end> */
/* 003a */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 003c */	0x8b,0x44,0x24,0x08,          	/* mov    0x8(%esp),%eax */
/* 004b */	0x83,0xe8,0x0a,               	/* sub    $10(12),%eax */
/* 0040 */	0xbb,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%ebx */
/* 0045 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0047 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0049 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 003e */	0xff,0x74,0x24,0x0c,          	/* pushl  0xc(%esp) */
/* 0042 */	0x52,                         	/* push   %edx */
/* 0043 */	0xba,0xde,0xad,0xc0,0xde,     	/* mov    $0x53,%edx */
/* 0048 */	0x01,0xd3,                    	/* add    %edx,%ebx */
/* 004a */	0x8b,0x1b,                    	/* mov    (%ebx),%ebx */
/* 004c */	0x5a,                         	/* pop    %edx */
/* 004d */	0xff,0xd3,                    	/* call   *%ebx */
/* 004d */	0x5b,						/* pop	%ebx */
/* 004d */	0x5b,						/* pop	%ebx */
/* 004f */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0051 */	0x5d,                         	/* pop    %ebp */
/* 0052 */	0xc3,                         	/* ret     */
} };

MLBIT(151) mwrite = { { 
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x51,                         	/* push   %ecx */
/* 0008 */	0x50,                         	/* push   %eax */
/* 0009 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0xb,%eax */
/* 000e */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0010 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0012 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0014 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0016 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0019 */	0xbf,0x64,0x00,0x00,0x00,     	/* mov    $0x64,%edi */
/* 001e */	0xf7,0xe7,                    	/* mul    %edi */
/* 0020 */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 0022 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0024 */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0027 */	0x01,0xd8,                    	/* add    %ebx,%eax */
/* 0029 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 002b */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 002d */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 002f */	0x83,0x7e,0xf0,0x03,          	/* cmpl   $0x3,-0x10(%esi) */
/* 0033 */	0x74,0x47,                    	/* je     7c <write_char> */
/* 0035 */	0x83,0xff,0x00,               	/* cmp    $0x0,%edi */
/* 0038 */	0x7e,0x13,                    	/* jle    4d <write_loop_init> */
/* 003a */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 003c */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 003e */	0xb9,0x0a,0x00,0x00,0x00,     	/* mov    $0xa,%ecx */
/* 0043 */	0xf7,0xf1,                    	/* div    %ecx */
/* 0045 */	0x89,0xd7,                    	/* mov    %edx,%edi */
/* 0047 */	0x57,                         	/* push   %edi */
/* 0048 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 004a */	0x43,                         	/* inc    %ebx */
/* 004b */	0xeb,0xe8,                    	/* jmp    35 <push_loop> */
/* 004d */	0x31,0xff,                    	/* xor    %edi,%edi */
/* 004f */	0x39,0xfb,                    	/* cmp    %edi,%ebx */
/* 0051 */	0x74,0x23,                    	/* je     76 <write_exit> */
/* 0053 */	0x83,0x04,0x24,0x30,          	/* addl   $0x30,(%esp) */
/* 0057 */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 0059 */	0x53,                         	/* push   %ebx */
/* 005a */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 005c */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 005e */	0x31,0xd2,                    	/* xor    %edx,%edx */
/* 0060 */	0xb8,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%eax */
/* 0065 */	0xbb,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%ebx */
/* 006a */	0xba,0x02,0x00,0x00,0x00,     	/* mov    $0x2,%edx */
/* 006f */	0xcd,0x80,                    	/* int    $0x80 */
/* 0071 */	0x5b,                         	/* pop    %ebx */
/* 0072 */	0x59,                         	/* pop    %ecx */
/* 0073 */	0x47,                         	/* inc    %edi */
/* 0074 */	0xeb,0xd9,                    	/* jmp    4f <write_loop> */
/* 0076 */	0x6a,0x0a,                    	/* push   $0xa */
/* 0078 */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 007a */	0xeb,0x03,                    	/* jmp    7f <wexit> */
/* 007c */	0x57,                         	/* push   %edi */
/* 007d */	0x89,0xe1,                    	/* mov    %esp,%ecx */
/* 007f */	0xb8,0x04,0x00,0x00,0x00,     	/* mov    $0x4,%eax */
/* 0084 */	0xbb,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%ebx */
/* 0089 */	0xba,0x01,0x00,0x00,0x00,     	/* mov    $0x1,%edx */
/* 008e */	0xcd,0x80,                    	/* int    $0x80 */
/* 0090 */	0x5b,                         	/* pop    %ebx */
/* 0091 */	0x58,                         	/* pop    %eax */
/* 0092 */	0x59,                         	/* pop    %ecx */
/* 0093 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0095 */	0x5d,                         	/* pop    %ebp */
/* 0096 */	0xc3,                         	/* ret     */
} };

MLBIT(164) mread = { { 
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x50,                         	/* push   %eax */
/* 0004 */	0x51,                         	/* push   %ecx */
/* 0005 */	0x31,0xff,                    	/* xor    %edi,%edi */
/* 0007 */	0x83,0x7e,0xf0,0x03,          	/* cmpl   $0x3,-0x10(%esi) */
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
/* 007d */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0xb,%eax */
/* 0082 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0084 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0086 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0088 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 008a */	0x25,0xff,0x00,0x00,0x00,     	/* and    $0xff,%eax */
/* 008f */	0x88,0x43,0x01,               	/* mov    %al,0x1(%ebx) */
/* 0092 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0094 */	0x25,0x00,0xff,0x00,0x00,     	/* and    $0xff00,%eax */
/* 0099 */	0xc1,0xf8,0x08,               	/* sar    $0x8,%eax */
/* 009c */	0x88,0x43,0x03,               	/* mov    %al,0x3(%ebx) */
/* 009f */	0x58,                         	/* pop    %eax */
/* 00a0 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 00a2 */	0x5d,                         	/* pop    %ebp */
/* 00a3 */	0xc3,                         	/* ret     */
} };

MLBIT(49) pop = { { 
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0005 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x08(%esp),%ebx */
/* 0009 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000e */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0010 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0012 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0014 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0016 */	0x25,0xff,0x00,0x00,0x00,     	/* and    $0xff,%eax */
/* 001b */	0x88,0x43,0x01,               	/* mov    %al,0x1(%ebx) */
/* 001e */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0020 */	0x25,0x00,0xff,0x00,0x00,     	/* and    $0xff00,%eax */
/* 0003 */	0xc1,0xf8,0x08,               	/* sar    $0x08,%eax */
/* 0025 */	0x88,0x43,0x03,               	/* mov    %al,0x3(%ebx) */
/* 0028 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 002a */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 002c */	0x5d,                         	/* pop    %ebp */
/* 002d */	0xc3,                         	/* ret     */	
} };

MLBIT(39) push = { {
/* 002e */	0x55,                         	/* push   %ebp */
/* 002f */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0031 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x08(%esp),%ebx */
/* 0035 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 003a */	0xf7,0xe3,                    	/* mul    %ebx */
/* 003c */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 003e */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0040 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0042 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0045 */	0xc1,0xe0,0x08,               	/* shl    $0x08,%al */
/* 0020 */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 0022 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0024 */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0027 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 004b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 004d */	0x5d,                         	/* pop    %ebp */
/* 004e */	0xc3,                         	/* ret     */
} };

MLBIT(43) add = { {
/* 002e */	0x55,                         	/* push   %ebp */
/* 002f */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0031 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x08(%esp),%ebx */
/* 0003 */	0x50,                         	/* push   %eax */
/* 0035 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 003a */	0xf7,0xe3,                    	/* mul    %ebx */
/* 003c */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 003e */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0040 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0042 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0045 */	0xc1,0xe0,0x08,               	/* shl    $0x08,%al */
/* 0020 */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 0022 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0024 */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0027 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0020 */	0x5f,                         	/* pop    %edi */
/* 001f */	0x01,0xf8,                    	/* add    %edi,%eax */
/* 004b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 004d */	0x5d,                         	/* pop    %ebp */
/* 004e */	0xc3,                         	/* ret     */
} };

MLBIT(45) sub = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0015 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0018 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001b */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001d */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 001f */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0022 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0024 */	0x5f,                         	/* pop    %edi */
/* 0025 */	0x29,0xc7,                    	/* sub    %eax,%edi */
/* 0027 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0029 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 002b */	0x5d,                         	/* pop    %ebp */
/* 002c */	0xc3,                         	/* ret     */
} };

MLBIT(43) mul = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0015 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0018 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001b */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001d */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 001f */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0022 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0024 */	0x5f,                         	/* pop    %edi */
/* 0025 */	0xf7,0xe7,                    	/* mul    %edi */
/* 0027 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0029 */	0x5d,                         	/* pop    %ebp */
/* 002a */	0xc3,                         	/* ret     */
} };

MLBIT(47) mdiv = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0015 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0018 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001b */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001d */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 001f */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0022 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0024 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0026 */	0x58,                         	/* pop    %eax */
/* 0058 */	0x52,                         	/* push   %edx */
/* 0027 */	0xf7,0xf7,                    	/* div    %edi */
/* 0061 */	0x5a,                         	/* pop    %edx */
/* 0029 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 002b */	0x5d,                         	/* pop    %ebp */
/* 002c */	0xc3,                         	/* ret     */
} };

MLBIT(49) mod = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0015 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0018 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001b */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001d */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 001f */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0022 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0024 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0026 */	0x58,                         	/* pop    %eax */
/* 0027 */	0x52,                         	/* push   %edx */
/* 0028 */	0xf7,0xf7,                    	/* div    %edi */
/* 002a */	0x89,0xd0,                    	/* mov    %edx,%eax */
/* 002c */	0x5a,                         	/* pop    %edx */
/* 002d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 002f */	0x5d,                         	/* pop    %ebp */
/* 0030 */	0xc3,                         	/* ret     */
} };

MLBIT(43) and = { {
/* 0056 */	0x55,                         	/* push   %ebp */
/* 0057 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0059 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 005d */	0x50,                         	/* push   %eax */
/* 005e */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 0063 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0065 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0067 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0069 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 006b */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 006e */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 0071 */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 0073 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0075 */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0078 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 007a */	0x5f,                         	/* pop    %edi */
/* 007b */	0x21,0xf8,                    	/* and    %edi,%eax */
/* 007d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 007f */	0x5d,                         	/* pop    %ebp */
/* 0080 */	0xc3,                         	/* ret     */
} };

MLBIT(43) or = { {
/* 002b */	0x55,                         	/* push   %ebp */
/* 002c */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 002e */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0032 */	0x50,                         	/* push   %eax */
/* 0033 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 0038 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 003a */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 003c */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 003e */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0040 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0043 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 0046 */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 0048 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 004a */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 004d */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 004f */	0x5f,                         	/* pop    %edi */
/* 0050 */	0x09,0xf8,                    	/* or     %edi,%eax */
/* 0052 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0054 */	0x5d,                         	/* pop    %ebp */
/* 0055 */	0xc3,                         	/* ret     */
} };

MLBIT(43) xor = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0015 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0018 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001b */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001d */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 001f */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0022 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0024 */	0x5f,                         	/* pop    %edi */
/* 0025 */	0x31,0xf8,                    	/* xor    %edi,%eax */
/* 0027 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0029 */	0x5d,                         	/* pop    %ebp */
/* 002a */	0xc3,                         	/* ret     */
} };

MLBIT(41) not = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000c */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000e */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0010 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0012 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0014 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0017 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001a */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001c */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 001e */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0021 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0023 */	0xf7,0xd0,                    	/* not    %eax */
/* 0025 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0027 */	0x5d,                         	/* pop    %ebp */
/* 0028 */	0xc3,                         	/* ret     */
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
/* 0014 */	0xc6,0x43,0x01,0x00,          	/* movb   $0x0,0x1(%ebx) */
/* 0018 */	0xc6,0x43,0x03,0x00,          	/* movb   $0x0,0x3(%ebx) */
/* 001c */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 001e */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0020 */	0x5d,                         	/* pop    %ebp */
/* 0021 */	0xc3,                         	/* ret     */
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
/* 0308 */	0x89,0x5e,0xf0,               	/* mov    %ebx,-0x10(%esi) */
/* 030b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 030d */	0x5d,                         	/* pop    %ebp */
/* 030e */	0xc3,                         	/* ret     */
} };

MLBIT(67) inc = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x53,                         	/* push   %ebx */
/* 0014 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0016 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0019 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001c */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001e */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0020 */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0023 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0025 */	0x5b,                         	/* pop    %ebx */
/* 0026 */	0x40,                         	/* inc    %eax */
/* 0027 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0029 */	0x25,0xff,0x00,0x00,0x00,     	/* and    $0xff,%eax */
/* 002e */	0x88,0x43,0x01,               	/* mov    %al,0x1(%ebx) */
/* 0031 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0033 */	0x25,0x00,0xff,0x00,0x00,     	/* and    $0xff00,%eax */
/* 0003 */	0xc1,0xf8,0x08,               	/* sar    $0xc,%eax */
/* 0038 */	0x88,0x43,0x03,               	/* mov    %al,0x3(%ebx) */
/* 003b */	0x58,                         	/* pop    %eax */
/* 003c */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 003e */	0x5d,                         	/* pop    %ebp */
/* 003f */	0xc3,                         	/* ret     */
} };

MLBIT(67) dec = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000d */	0xf7,0xe3,                    	/* mul    %ebx */
/* 000f */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0011 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0013 */	0x53,                         	/* push   %ebx */
/* 0014 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0016 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 0019 */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001c */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001e */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0020 */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0023 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0025 */	0x5b,                         	/* pop    %ebx */
/* 0026 */	0x48,                         	/* dec    %eax */
/* 0027 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0029 */	0x25,0xff,0x00,0x00,0x00,     	/* and    $0xff,%eax */
/* 002e */	0x88,0x43,0x01,               	/* mov    %al,0x1(%ebx) */
/* 0031 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0033 */	0x25,0x00,0xff,0x00,0x00,     	/* and    $0xff00,%eax */
/* 0038 */	0xc1,0xf8,0x0c,               	/* sar    $0xc,%eax */
/* 003b */	0x88,0x43,0x03,               	/* mov    %al,0x3(%ebx) */
/* 003e */	0x58,                         	/* pop    %eax */
/* 003f */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0041 */	0x5d,                         	/* pop    %ebp */
/* 0042 */	0xc3,                         	/* ret     */
} };

MLBIT(28) abs_jmp = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
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

MLBIT(49) abs_call = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x7c,0x24,0x10,          	/* mov    0x10(%esp),%edi */
/* 0007 */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
/* 000a */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
/* 000d */	0x89,0x3b,                    	/* mov    %edi,(%ebx) */
/* 000f */	0x8b,0x5e,0xf4,               	/* mov    -0xc(%esi),%ebx */
/* 0012 */	0x83,0xc3,0x04,               	/* add    $0x4,%ebx */
/* 0015 */	0x89,0x5e,0xf4,               	/* mov    %ebx,-0xc(%esi) */
/* 0018 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 001c */	0x50,                         	/* push   %eax */
/* 001d */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
/* 0022 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0024 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0026 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0028 */	0x58,                         	/* pop    %eax */
/* 0029 */	0x89,0x5c,0x24,0x04,          	/* mov    %ebx,0x4(%esp) */
/* 002d */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 002f */	0x5d,                         	/* pop    %ebp */
/* 0030 */	0xc3,                         	/* ret     */
} };

MLBIT(28) ret = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x7e,0xf4,               	/* mov    -0xc(%esi),%edi */
/* 0006 */	0x83,0xef,0x04,               	/* sub    $0x4,%edi */
/* 0009 */	0x89,0x7e,0xf4,               	/* mov    %edi,-0xc(%esi) */
/* 000c */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
/* 000f */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
/* 0012 */	0x8b,0x3b,                    	/* mov    (%ebx),%edi */
/* 0014 */	0x89,0x7c,0x24,0x04,          	/* mov    %edi,0x4(%esp) */
/* 0018 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 001a */	0x5d,                         	/* pop    %ebp */
/* 001b */	0xc3,                         	/* ret     */
} };

MLBIT(60) stpush = { {
/* 0033 */	0x55,                         	/* push   %ebp */
/* 0034 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0036 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 003a */	0x50,                         	/* push   %eax */
/* 003b */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0xb,%eax */
/* 0040 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0042 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0044 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0046 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0048 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 004b */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 004e */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 0050 */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0052 */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0055 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0057 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0059 */	0x58,                         	/* pop    %eax */
/* 005a */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
/* 005d */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
/* 0060 */	0x89,0x3b,                    	/* mov    %edi,(%ebx) */
/* 0062 */	0x8b,0x5e,0xf4,               	/* mov    -0xc(%esi),%ebx */
/* 0065 */	0x83,0xc3,0x04,               	/* add    $0x4,%ebx */
/* 0068 */	0x89,0x5e,0xf4,               	/* mov    %ebx,-0xc(%esi) */
/* 006b */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 006d */	0x5d,                         	/* pop    %ebp */
/* 006e */	0xc3,                         	/* ret     */
} };

MLBIT(67) stpop = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5e,0xf0,               	/* mov    -0x10(%esi),%ebx */
/* 0006 */	0x03,0x5e,0xf4,               	/* add    -0xc(%esi),%ebx */
/* 0009 */	0x83,0xeb,0x04,               	/* sub    $0x4,%ebx */
/* 000c */	0x8b,0x3b,                    	/* mov    (%ebx),%edi */
/* 000e */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0012 */	0x50,                         	/* push   %eax */
/* 0013 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0xb,%eax */
/* 0018 */	0xf7,0xe3,                    	/* mul    %ebx */
/* 001a */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 001c */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 001e */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0020 */	0x25,0xff,0x00,0x00,0x00,     	/* and    $0xff,%eax */
/* 0025 */	0x88,0x43,0x01,               	/* mov    %al,0x1(%ebx) */
/* 0028 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 002a */	0x25,0x00,0xff,0x00,0x00,     	/* and    $0xff00,%eax */
/* 002f */	0xc1,0xf8,0x08,               	/* sar    $0x8,%eax */
/* 0032 */	0x88,0x43,0x03,               	/* mov    %al,0x3(%ebx) */
/* 0035 */	0x58,                         	/* pop    %eax */
/* 0036 */	0x8b,0x7e,0xf4,               	/* mov    -0xc(%esi),%edi */
/* 0039 */	0x83,0xef,0x04,               	/* sub    $0x4,%edi */
/* 003c */	0x89,0x7e,0xf4,               	/* mov    %edi,-0xc(%esi) */
/* 003f */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0041 */	0x5d,                         	/* pop    %ebp */
/* 0042 */	0xc3,                         	/* ret     */
} };

MLBIT(64) cmp = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x31,0xc9,                    	/* xor    %ecx,%ecx */
/* 0005 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0009 */	0x50,                         	/* push   %eax */
/* 000a */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
/* 000f */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0011 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0013 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0015 */	0x31,0xc0,                    	/* xor    %eax,%eax */
/* 0017 */	0x8a,0x43,0x03,               	/* mov    0x3(%ebx),%al */
/* 001a */	0xc1,0xe0,0x08,               	/* shl    $0x8,%eax */
/* 001d */	0x89,0xdf,                    	/* mov    %ebx,%edi */
/* 001f */	0x31,0xdb,                    	/* xor    %ebx,%ebx */
/* 0021 */	0x8a,0x5f,0x01,               	/* mov    0x1(%edi),%bl */
/* 0024 */	0x09,0xd8,                    	/* or     %ebx,%eax */
/* 0026 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0028 */	0x58,                         	/* pop    %eax */
/* 0029 */	0x39,0xf8,                    	/* cmp    %edi,%eax */
/* 002b */	0x74,0x0f,                    	/* je     3c <cmp_end> */
/* 002d */	0x39,0xf8,                    	/* cmp    %edi,%eax */
/* 002f */	0x7c,0x06,                    	/* jl     37 <cmp_jl> */
/* 0031 */	0x39,0xf8,                    	/* cmp    %edi,%eax */
/* 0033 */	0x7f,0x05,                    	/* jg     3a <cmp_jg> */
/* 0035 */	0xeb,0x05,                    	/* jmp    3c <cmp_end> */
/* 0037 */	0x41,                         	/* inc    %ecx */
/* 0038 */	0xeb,0x02,                    	/* jmp    3c <cmp_end> */
/* 003a */	0x41,                         	/* inc    %ecx */
/* 003b */	0x41,                         	/* inc    %ecx */
/* 003c */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 003e */	0x5d,                         	/* pop    %ebp */
/* 003f */	0xc3,                         	/* ret     */
} };

MLBIT(33) abs_jz = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
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
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
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
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
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
/* 0008 */	0xb8,0x0b,0x00,0x00,0x00,     	/* mov    $0x0b,%eax */
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
