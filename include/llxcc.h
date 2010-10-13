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

MLBIT(4) opcode_set = { { 0x66, 0xbf, /* mov opcode,%edi */
					 0x00, 0x00 /* opcode */
				  } };

MLBIT(4) pop = { { 0x90, 0x88, 0x04, 0x3e  /* mov %al,(%esi,%edi) */
		     } };

MLBIT(4) push = { { 0x90, 0x8a, 0x04, 0x3e /* mov (%esi,%edi),%al */
		 	 } };

MLBIT(4) add = { { 0x90, 0x02, 0x04, 0x3e /* add (%esi,%edi),%al */
			} };

MLBIT(4) sub = { { 0x90, 0x2a, 0x04, 0x3e /* sub (%esi,%edi),%al */
			} };

MLBIT(4) mul = { { 0x90, 0xf6, 0x24, 0x3e /* mul (%esi,%edi) */
			} };

MLBIT(4) mdiv = { { 0x90, 0xf6, 0x34, 0x3e /* div (%esi,%edi) */
		      } };

MLBIT(12) mod = { { 0x88, 0xc3, /* mov %al,%bl */
			     0xf6, 0x34, 0x3e, /* div (%esi,%edi) */
			     0xf6, 0x24, 0x3e, /* mul (%esi,%edi) */
			     0x28, 0xc3,  /* sub %al, %bl */
			     0x86, 0xc3 /* xchg %bl,%al */
			} };

MLBIT(4) and = { { 0x90, 0x22, 0x04, 0x3e /* and (%esi,%edi),%eax */
			} };

MLBIT(4) or = { { 0x90, 0x0a, 0x04, 0x3e /* or (%esi,%edi),%eax */
		    } };

MLBIT(4) xor = { { 0x90, 0x32, 0x04, 0x3e /* xor (%esi,%edi),%eax */
			} };

MLBIT(8) not = { { 0x90, 0x90, 0x90, /* nops */
			    0x8a, 0x04, 0x3e, /* mov (%esi,%edi),%eax */
			    0xf6, 0xd0 /* not %eax */
			} };

MLBIT(8) del = { { 0x90, 0x90, 0x90, /* nops */
			    0x31, 0xdb, /* xor %ebx,%ebx */
			    0x89, 0x1c, 0x3e /* mov %ebx,(%esi,%edi) */
			 } };

MLBIT(4) nop = { { 0x90, 0x90, 0x90, 0x90 /* nop */
			} };

MLBIT(8) mexit = { { 0x31, 0xc0, /* xor %eax,%eax */
				0xb0, 0x01, /* mov $0x1,%al */
				0x89, 0xfb, /* mov %edi,%ebx */
				0xcd, 0x80  /* int $0x80 */
			 } };

MLBIT(4) mchmod = { { 0x90, 0x90, /* nops */
				  0x89, 0xfa  /* mov %edi,%edx */
			   } };


MLBIT(8) inc = { { 0x8a, 0x04, 0x3e, /* mov (%esi,%edi),%eax */
			    0x40, /* inc %eax */ 
			    0x88, 0x04, 0x3e, /* mov %eax,(%esi,%edi) */
			    0x90 /* nop */
			} };

MLBIT(8) dec = { { 0x8a, 0x04, 0x3e, /* mov (%esi,%edi),%eax */
			    0x48, /* dec %eax */ 
			    0x88, 0x04, 0x3e, /* mov %eax,(%esi,%edi) */
			    0x90 /* nop */
			} };

//MLBIT(4) short_jmp = { { 0x90, 0x90, /* nops */
//					0xeb, 0x00 /* jmp short byte */
//			      } };

MLBIT(8) abs_jmp = { { 0x90, 0x90, /* nops */
				   0x89, 0xf3, /* mov %esi,%ebx */
				   0x01, 0xfb, /* add %edi,%ebx */
				   0xff, 0xe3  /* jmp *%ebx */
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
	{ 10, 0, NULL, 0 },
	{ 11, 0, NULL, 0 },
	{ 12, 0, (char*)&pop, sizeof( pop ) },
	{ 13, 0, (char*)&push, sizeof ( push ) },
	{ 14, 0, (char*)&add, sizeof( add ) },
	{ 15, 0, (char*)&sub, sizeof( sub ) },
	{ 16, 0, (char*)&mul, sizeof( mul ) },
	{ 17, 0, (char*)&mdiv, sizeof( mdiv ) },
	{ 18, 0, (char*)&mod, sizeof( mod ) },
	{ 19, 0, (char*)&and, sizeof( and ) },
	{ 20, 0, (char*)&or, sizeof( or ) },
	{ 21, 0, (char*)&xor, sizeof( xor ) },
	{ 22, 0, (char*)&not, sizeof( not ) },
	{ 23, 0, (char*)&shl, sizeof( shl ) },
	{ 24, 0, (char*)&sar, sizeof( sar ) },
	{ 25, 0, (char*)&del, sizeof( del ) },
	{ 26, 1, (char*)&nop, sizeof( nop ) },
	{ 27, 0, (char*)&abs_jmp, sizeof( abs_jmp ) }, /* Absolute jumps using */
	{ 28, 0, (char*)&cmp, sizeof( cmp ) },
	{ 29, 0, (char*)&short_jn, sizeof( short_jn ) },
	{ 30, 0, (char*)&short_jz, sizeof( short_jz ) },
	{ 31, 0, (char*)&short_jm, sizeof( short_jm ) },
	{ 32, 0, (char*)&short_jg, sizeof( short_jg ) },
	{ 33, 0, (char*)&mexit, sizeof( mexit ) },
	{ 34, 0, (char*)&mchmod, sizeof( mchmod ) },
	{ 35, 0, (char*)&inc, sizeof( inc ) },
	{ 36, 0, (char*)&dec, sizeof( dec ) },
	{ 37, 0, (char*)&abs_call, sizeof( abs_call ) },
	{ 38, 1, (char*)&ret, sizeof( ret ) },
	{ 39, 0, (char*)&stpush, sizeof( stpush ) },
	{ 40, 0, (char*)&stpop, sizeof( stpop ) },
};

#endif /* _LLXCC_ */
