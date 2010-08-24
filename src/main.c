#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <sys/stat.h>
#include <elf.h>

#include <mlelf.h>
#include <llxcc.h>

#define opcode_set( op, value )  (op = value, opcode( op ))

void
sample_code()
{
	int op = 0;

	emitobj( init );
	emitobj( load_mem );

	emitobj( push );

	opcode_set( op, 1 );

	emitobj( add );

	opcode_set( op, 0 );

	emitobj( pop );

	opcode_set( op, 42 );

	emitobj( mexit );
}

static void
addrelocations(blueprint const *bp, int codetype, char const *function)
{
	addtosymtab(bp->parts + P_SYMTAB, function, STB_GLOBAL, STT_FUNC, P_TEXT);
	addtosymtab(bp->parts + P_SYMTAB, "memory", STB_LOCAL,  STT_OBJECT, P_DATA);
} 

void
createfixups(blueprint const *bp, int codetype, char const *function)
{
	((Elf32_Ehdr*)bp->parts[P_EHDR].part)->e_entry = bp->parts[P_TEXT].addr;

	setsymvalue( &bp->parts[P_SYMTAB], "_start", bp->parts[P_TEXT].addr );
	setsymvalue( &bp->parts[P_SYMTAB], "memory", bp->parts[P_DATA].addr );

	insertobj( 14, bp->parts[P_DATA].addr );
}

static int
setnames(blueprint const *bp, int codetype, char const *filename)
{
	char const *base;
	int n;

	base = strrchr(filename, '/');
	base = base ? base + 1 : filename;
	n = strlen(base);

	if (!srcfilename)
		xstrndup(srcfilename, base, n);

	if (base[n - 2] == '.' && base[n - 1] == 'l' && n > 2)
		n -= 2;

	if (!outfilename)
	{
		if (!base[n])
			xstrndup(outfilename, "a.out", sizeof "a.out");
		else
			xstrndup(outfilename, base, n);
	}

	xstrndup(functionname, "_start", 6);

	return 1;
}

/* Creates and initializes the various parts of the object file.
 */
static int
createparts(blueprint const *bp)
{
	newparts(bp);

	if (bp->parts[P_HASH].shtype)
		bp->parts[P_HASH].link = &bp->parts[P_DYNSYM];

	if (bp->parts[P_DYNSYM].shtype)
		bp->parts[P_DYNSYM].link = &bp->parts[P_DYNSTR];

	if (bp->parts[P_REL].shtype)
	{
		bp->parts[P_REL].link = &bp->parts[P_SYMTAB];
		bp->parts[P_REL].info = P_TEXT;
	}

	if (bp->parts[P_SYMTAB].shtype)
		bp->parts[P_SYMTAB].link = &bp->parts[P_STRTAB];

	if (bp->parts[P_SHDRTAB].shtype && bp->parts[P_SHSTRTAB].shtype)
		bp->parts[P_SHDRTAB].link = &bp->parts[P_SHSTRTAB];

	initparts(bp);

	return 1;
}

/* Creates the contents of the various parts of the object file.
 */
static int
populateparts(blueprint const *bp, int codetype, char const *filename, int compressed)
{
	if (bp->parts[P_COMMENT].shtype)
	{
		bp->parts[P_COMMENT].shname = ".comment";
		bp->parts[P_COMMENT].size = sizeof comment;
		xstrndup(bp->parts[P_COMMENT].part, comment, sizeof comment);
	}
	
	if (bp->parts[P_SYMTAB].shtype)
		addtosymtab(bp->parts + P_SYMTAB, srcfilename, STB_LOCAL, STT_FILE, SHN_ABS);

	mach_buf = bp->parts[P_TEXT].part;
   	mach_size = bp->parts[P_TEXT].size;
   	
   	sample_code();

	bp->parts[P_TEXT].size = pos;
	bp->parts[P_TEXT].part = mach_buf;
	bp->parts[P_DATA].size = 1000;

	if (!(bp->parts[P_DATA].part = calloc(1000, 1)))
		return 0;

	addrelocations(bp, ET_EXEC, functionname);

	fillparts(bp);

	if (!computeoffsets(bp))
		return 0;

	createfixups(bp, codetype, functionname);

	completeparts(bp);

	return 1;
}

static int
compile(blueprint *bp,char const *filename)
{
	struct stat s;

	if (!createparts(bp))
		return 0;

	if (!setnames(bp, ET_EXEC, filename))
		return 0;

	if (!populateparts(bp, ET_EXEC, filename, 0))
		return 0;

	if (!outputelf(bp, outfilename))
	{
		remove(outfilename);
		return 0;
	}

	if (!stat(outfilename, &s))
	{
		if (bp->filetype == ET_EXEC)
		    s.st_mode |= S_IXUSR | S_IXGRP | S_IXOTH;

		chmod(outfilename, s.st_mode);
	}

	return 1;
}

void
usage(char * file)
{
	fprintf( stderr,
			"Usage: %s <lxs file>\n", file);

	exit(1);
}

int
main(int argc,char *argv[])
{
	int i,n;
	blueprint b = { 0 };

	if(!argv[1])
		usage( argv[0] );

	b.filetype = ET_EXEC;
	b.partcount = P_COUNT;
	
	xalloc(b.parts, P_COUNT * sizeof(*b.parts));
	
	for (n = 0 ; n < P_COUNT ; ++n)
		    b.parts[n] = *parttable[n];

	b.parts[P_COMMENT].shtype = 0;

	compile( &b, argv[1]);

	return 0;
}
