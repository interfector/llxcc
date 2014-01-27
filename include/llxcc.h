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

MLBIT(10) load_mem = { {  /* 0x8d, 0x35, */ /* lea mem,%esi */
				     /* 0x00, 0x00, 0x00, 0x00,*/  /* Memory to load */	
					 0xe8, 0x00, 0x00, 0x00, 0x00, /* call here */
					 0x5e, /* pop %esi */
					 0x66, 0x83, 0xc6, 0x05 /* add $0x5,%esi */
				 } };

MLBIT(5) null_code = { { 0x90, 0x90, 0x90, 0x90, 0x90 } };

MLBIT(9) opcode_set = { { 0x6a, 0x00, /* push val */
					 0x6a, 0x00, /* push opcode */
					 0xe8, 0xde, 0xad, 0xc0, 0xde /* call exec_table */
				  } };

MLBIT(59) exec_table = {{
/* 0037 */	0x55,                         	/* push   %ebp */
/* 0038 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* TEST */
/* 003a */	0x8b,0x7c,0x24,0x08,          	/* mov    0x8(%esp),%edi */
/* 003e */	0x83,0xff,0x0a,               	/* cmp    $0xa,%edi */
/* 0041 */	0x7c,0x2b,                    	/* jl     6e <end> */
/* 0043 */	0x83,0xff,0x2f,               	/* cmp    $0x2f,%edi */
/* 0046 */	0x7f,0x26,                    	/* jg     6e <end> */
/* TEST */
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
/* 004f */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0051 */	0x5d,                         	/* pop    %ebp */
/* 0052 */	0xc3,                         	/* ret     */
} };

MLBIT(49) pop = { { 
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x89,0xc7,                    	/* mov    %eax,%edi */
/* 0005 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x08(%esp),%ebx */
/* 0009 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x09,%eax */
/* 000e */	0xf7,0xe3,                    	/* mul    %ebx */
/* 0010 */	0x89,0xc3,                    	/* mov    %eax,%ebx */
/* 0012 */	0x01,0xf3,                    	/* add    %esi,%ebx */
/* 0014 */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0016 */	0x25,0xff,0x00,0x00,0x00,     	/* and    $0xff,%eax */
/* 001b */	0x88,0x43,0x01,               	/* mov    %al,0x1(%ebx) */
/* 001e */	0x89,0xf8,                    	/* mov    %edi,%eax */
/* 0020 */	0x25,0x00,0xff,0x00,0x00,     	/* and    $0xff00,%eax */
/* 0003 */	0xc1,0xf8,0x08,               	/* sar    $0xc,%eax */
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
/* 0035 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x09,%eax */
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
/* 0035 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x09,%eax */
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
/* 0008 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 0008 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 0008 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 0008 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 005e */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 0033 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 0008 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 0007 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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

MLBIT(11) mchmod = { {
/* 0040 */	0x55,                         	/* push   %ebp */
/* 0041 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0043 */	0x8b,0x54,0x24,0x08,          	/* mov    0x8(%esp),%edx */
/* 0047 */	0x89,0xec,                    	/* mov    %ebp,%esp */
/* 0049 */	0x5d,                         	/* pop    %ebp */
/* 004a */	0xc3,                         	/* ret     */
} };

MLBIT(67) inc = { {
/* 0000 */	0x55,                         	/* push   %ebp */
/* 0001 */	0x89,0xe5,                    	/* mov    %esp,%ebp */
/* 0003 */	0x8b,0x5c,0x24,0x08,          	/* mov    0x8(%esp),%ebx */
/* 0007 */	0x50,                         	/* push   %eax */
/* 0008 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 0008 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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
/* 0008 */	0xb8,0x09,0x00,0x00,0x00,     	/* mov    $0x9,%eax */
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

MLBIT(20) abs_call = { { 0xe8, 0x00, 0x00, 0x00, 0x00, /* call here */
			     	0x5b, /* pop %ebx */
				     0x83, 0xc3, 0x0c, /* add $0xc,%ebx */
				     0x89, 0xdd, /* mov %ebx,%ebp */
				     0x89, 0xf3, /* mov %esi,%ebx */
				     0x01, 0xfb, /* add %edi,%ebx */
				     0xff, 0xe3, /* jmp *%ebx */
				     0x90, 0x90, 0x90 /* nops */
				 } };

MLBIT(4) ret = { { 0x90, 0x90, /* nops */
			    0xff, 0xe5  /* jmp %ebp */
			} };

MLBIT(4) stpush = { { 0x90, /* nop */
				  0xff, 0x34, 0x3e /* push (%esi,%edi) */
			   } };

MLBIT(4) stpop = { { 0x90, /* nop */
				 0x8f, 0x04, 0x3e /* pop (%esi,%edi) */
			  } };

MLBIT(24) cmp = { { 0x31, 0xc9, /* xor %ecx,%ecx */
				0x38, 0x04, 0x3e, /* cmp %al,(%esi,%edi) */
				0x74, 0x0a, /* jz 0x11 */
				0x38, 0x04, 0x3e, /* cmp %al,(%esi,%edi) */
				0x7f, 0x07, /* jg 0x13 */
				0x38, 0x04, 0x3e, /* cmp %al,(%esi,%edi) */
				0x7c, 0x05,  /* jl 0x16 */
				0xeb, 0x05,  /* jmp end */
				0x41,  /* inc %ecx */
				0xeb, 0x03, /* jmp end */
				0xb1, 0x02 /* mov $0x2,%cl */
			 } };

MLBIT(8) short_jz = { { 0x90, 0x90, 0x90, /* nops */
				    0x83, 0xf9, 0x00, /* cmp $0,%ecx */
				    0x74, 0x00 /* je short byte */
				} };

MLBIT(8) short_jn = { { 0x90, 0x90, 0x90, /* nops */
				    0x83, 0xf9, 0x00, /* cmp $0,%ecx */
				    0x75, 0x00 /* jne short byte */
				} };

MLBIT(8) short_jm = { { 0x90, 0x90, 0x90, /* nops */
				    0x83, 0xf9, 0x01, /* cmp $1,%ecx */
				    0x74, 0x00 /* je short byte */
				} };

MLBIT(8) short_jg = { { 0x90, 0x90, 0x90, /* nops */
				    0x83, 0xf9, 0x02, /* cmp $2,%ecx */
				    0x74, 0x00 /* je short byte */
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

struct lxs_code {
	int instr, opcode;

	char* code;
	int code_size;
};

struct lxs_code instruction_set[] = {
	/* read, write */
	{ 10, 0, (char*)&nop, sizeof( nop ) },
	{ 11, 0, (char*)&nop, sizeof( nop ) },
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
	{ 23, 0, (char*)&del, sizeof( del ) },
	{ 24, 0, (char*)&nop, sizeof( nop ) },
	{ 25, 0, (char*)&del, sizeof( del ) },
	{ 26, 1, (char*)&nop, sizeof( nop ) },
	{ 27, 0, (char*)&abs_jmp, sizeof( abs_jmp ) }, /* Absolute jumps using */
	{ 28, 0, (char*)&nop, sizeof( nop ) },
	{ 29, 0, (char*)&nop, sizeof( nop ) },
	{ 30, 0, (char*)&nop, sizeof( nop ) },
	{ 31, 0, (char*)&nop, sizeof( nop ) },
	{ 32, 0, (char*)&nop, sizeof( nop ) },
	{ 33, 0, (char*)&mexit, sizeof( mexit ) },
	{ 34, 0, (char*)&mchmod, sizeof( mchmod ) },
	{ 35, 0, (char*)&inc, sizeof( inc ) },
	{ 36, 0, (char*)&nop, sizeof( nop ) },
	{ 37, 0, (char*)&nop, sizeof( nop ) },
	{ 38, 1, (char*)&nop, sizeof( nop ) },
	{ 39, 0, (char*)&nop, sizeof( nop ) },
	{ 40, 0, (char*)&nop, sizeof( nop ) },
};

#define LEN (sizeof(instruction_set)/sizeof(struct lxs_code))

#endif /* _LLXCC_ */
