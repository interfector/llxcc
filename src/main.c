#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <elf.h>

#include <mlelf.h>
#include <llxcc.h>

#define opcode_set( op, value )  (op = value, emit_opcode( op ))

int table[LEN];
int table_pos = 0;
int exec_table_pos = 0;

void
parse_code(blueprint const *bp, const char* filename )
{
	int opcode, i;
	int pages = getpagesize() - 1;
	struct lxs_code in;
	FILE* fp;
	char* line = malloc( 256 );

	memset( line, 0, 256 );

	if(!(fp = fopen( filename, "r")))
	{
		perror("fopen");
		exit(1);
	}

	/* mprotect memory prelude */

	emitobj( init );
	insertobj( 10, pages );
	pages = getpagesize();
	insertobj( 23, pages );
	emitobj( load_mem );

	while(fgets( line, 256, fp ))
	{
		if(line[0] == 0 || line[0] == '#' || line[0] == '\n')
			continue;

		line[strlen(line)-1] = 0;

	#ifdef _DEBUG
		printf("[line \"%s\"]\n", line );
	#endif

		opcode = atoi( line );

	/*	if( op < 10 || op > 40 )
		{
			emit( &null_code, 4 );
			insertobj( pos - 3, code);
			insertobj( pos - 1, op);
			emitobj( null_code );

			memset( line, 0, 256 );

			continue;
		}*/

		emit_opcode( opcode );
		
		memset( line, 0, 256 );
	}

	/* write all the instruction table then search for 0xe8deadc0de and substitute deadc0de with table addr*/

#ifdef _DEBUG
	printf("size: %d\n", LEN);
#endif

	for(i = 0;i < LEN;i++)
	{
		in = instruction_set[i];

		table[i] = pos;

		emit( in.code, in.code_size );
	}

	exec_table_pos = pos;

	emitobj( exec_table );

	table_pos = pos;

	for(i = 0;i < LEN;i++)
		emitobj( table[i] );

	free( line );
}

static void
addrelocations(blueprint const *bp, int codetype, char const *function)
{
	addtosymtab(bp->parts + P_SYMTAB, function, STB_GLOBAL, STT_FUNC, P_TEXT);
} 

void
createfixups(blueprint const *bp, int codetype, char const *function)
{
	((Elf32_Ehdr*)bp->parts[P_EHDR].part)->e_entry = bp->parts[P_TEXT].addr;

	setsymvalue( &bp->parts[P_SYMTAB], "_start", bp->parts[P_TEXT].addr );
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
populateparts(blueprint const *bp, int codetype, char const *filename )
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
   	
   	parse_code( bp, filename  );

	bp->parts[P_TEXT].size = pos;
	bp->parts[P_TEXT].part = mach_buf;
	bp->parts[P_DATA].size = 1000;

	if (!(bp->parts[P_DATA].part = calloc(1000, 1)))
		return 0;

	bp->parts[P_DATA].part = mach_buf;

	addrelocations(bp, ET_EXEC, functionname);

	fillparts(bp);

	if (!computeoffsets(bp))
		return 0;

#ifdef _DEBUG
	printf("0x%x\n", bp->parts[P_TEXT].addr );
#endif

	int i, addr;
	char call[] = { 0xe8, 0xde, 0xad, 0xc0, 0xde };
	char mov[] = { 0xbf, 0xde, 0xad, 0xc0, 0xde };
	char* text = bp->parts[P_TEXT].part;

	for(i = 0;i < pos;i++) {
		if(!memcmp( text+i, call, 5 )) {
			addr = exec_table_pos - (i + 5);
			memcpy( text+i+1, &addr, sizeof(int));
		}
	}

	for(i = 0;i < pos;i++) {
		if(!memcmp( text+i, mov, 5 )) {
			addr = table_pos + bp->parts[P_TEXT].addr;
			memcpy( text+i+1, &addr, sizeof(int));
		}
	}

	for(i = 0;i < LEN;i++)
	{
		table[i] += bp->parts[P_TEXT].addr;

		memcpy( text + table_pos + (i*4), &table[i], sizeof(int));

#ifdef _DEBUG
		printf("table[%d]:\t0x%x\n", i, table[i] );
#endif
	}

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

	if (!populateparts(bp, ET_EXEC, filename))
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
			"Usage: %s <lxs file> [-o <output file>]\n", file);

	exit(1);
}

int
main(int argc,char *argv[])
{
	int i;
	blueprint b = { 0 };

	if(!argv[1])
		usage( argv[0] );

	while ((i = getopt(argc, argv, "ho:")) != EOF)
	{
		switch (i)
		{
			case 'o':
				xstrndup(outfilename, optarg, strlen(optarg));
				break;
			case 'h':
			default:
				usage( argv[0] );
				return 0;
		}
	}

	if (optind + 1 != argc)
	{
		puts( (optind == argc) ? "llxcc: no input file specified." : "llxcc: multiple input files specified.");
		return 1;
	}

	b.filetype = ET_EXEC;
	b.partcount = P_COUNT;
	
	xalloc(b.parts, P_COUNT * sizeof(*b.parts));
	
	for (i = 0 ; i < P_COUNT ; ++i)
		    b.parts[i] = *parttable[i];

	b.parts[P_COMMENT].shtype = 0;

	compile( &b, argv[optind]);

	return 0;
}
