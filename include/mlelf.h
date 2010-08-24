#ifndef _LLXCC_ELF_
#define _LLXCC_ELF_

#include <elfparts.h>

/* Allocates memory (or aborts).
 */
#define	xalloc(p, n) \
    (((p) = realloc((p), (n))) ? (p) : (fputs("Out of memory!\n", stderr), \
					exit(1), NULL))

/* Allocates memory for a string and forces null-termination.
 */
#define	xstrndup(d, s, n) \
    (((char*)memcpy(xalloc((d), (n) + 1), (s), (n)))[n] = '\0')

/* The contents of the .comment section.
 *  */
static char const	comment[] = "\0ELF LXS Compiler 0.0.1";

static char* mach_buf;
static int mach_size = 0;
static int pos = 0;

/* Macros to simplify calling emit with predefined bits of code.
 *  */
#define	emitobj(obj)		(emit(&(obj), sizeof (obj)))
#define	emitarg(seq, arg)	(emitobj(seq), emitobj(arg))

/* Modifies previously emitted code at the given position.
 *  */
#define	insertobj(at, obj)	(memcpy(mach_buf + (at), &(obj), sizeof (obj)))

#define	opcode( i )	(emitobj(opcode_set), insertobj( pos - 2, i))

static void
emit(void const *bytes, int size)
{
	if (pos + size > mach_size)
	{
		mach_size = size + pos;

		if (!(mach_buf = realloc(mach_buf, mach_size)))
		{
			fputs("Out of memory!\n", stderr);
			exit(1);
		}	
	}
	
	memcpy(mach_buf + pos, bytes, size);
	pos += size;
}

enum
{
	P_EHDR = 0,
	P_PHDRTAB, P_HASH, P_DYNSYM, P_DYNSTR, P_TEXT, P_REL,
	P_GOT, P_DYNAMIC, P_DATA,
	P_SHSTRTAB, P_COMMENT, P_SYMTAB, P_STRTAB, P_SHDRTAB,
	P_COUNT
};

static elfpart const   *parttable[P_COUNT] = {
	&part_ehdr, &part_phdrtab, &part_hash, &part_dynsym, &part_dynstr,
	&part_text, &part_rel, &part_got, &part_dynamic, &part_data,
	&part_shstrtab, &part_progbits, &part_symtab, &part_strtab, &part_shdrtab
};

static char partlists[P_COUNT] = { 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 }	/* ET_EXEC */;

static char* srcfilename;
static char* outfilename;
static char* functionname;

static int compile(blueprint*,char const*);

#endif /* _LLXCC_ELF_ */
