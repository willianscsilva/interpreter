#include "syntax_analysis.h"
#include "core_aux/core_aux_regex.h"

char* get_content_scriptfile( int argc, char **argv )
{
	char * buffer = 0;
	long length;
	FILE * fp = fopen (argv[1], "r");
	if ( fp != NULL )
	{
		fseek (fp, 0, SEEK_END);
		length = ftell (fp);
		fseek (fp, 0, SEEK_SET);
		buffer = malloc (length);
		if (buffer)
		{
			fread (buffer, 1, length, fp);
		}
		fclose (fp);
	}
	else	
	{		
		printf("ERROR: Error opening file, make sure that the file exists!\n\n");	
		exit(EXIT_FAILURE);
	}
	return buffer;
}

void validate_extesionfile( char* file_name )
{
	match = regex_match_syntax( "\\.li", file_name );
	if( match == 0 )
	{		
		exit( EXIT_FAILURE );
	}
}

void get_begin_end_block( char char_content )
{
	match = regex_match_syntax( "{", &char_content );
	if( match == 1)
	{
		count_block.count_begin++;
	}
	match = regex_match_syntax( "}", &char_content );
	if( match == 1)
	{
		count_block.count_end++;
	}
}

void validate_beginend_block()
{
	LEVEL_ERROR = "FATAL_ERROR: ";	
	if( count_block.count_begin < count_block.count_end )
	{
		printf( "%sBegin block ( { ) not found!\n", LEVEL_ERROR );
		count_block.count_begin = 0;
		count_block.count_end = 0;
		match_break_line = 0;
		exit( EXIT_FAILURE );
	}
	if( count_block.count_begin > count_block.count_end )
	{
		printf( "%sEnd block ( } ) not found!\n", LEVEL_ERROR );
		count_block.count_begin = 0;
		count_block.count_end = 0;
		match_break_line = 0;
		exit( EXIT_FAILURE );
	}
	count_block.count_begin = 0;
	count_block.count_end = 0;
	match_break_line = 0;
}

void validate_end_instructions( char char_content )
{	
	/*LEVEL_ERROR = "FATAL_ERROR: ";	
	match = regex_match_syntax( "[a-z A-Z]+;[\n]?", char_content );
	if( match == 0 )
	{
		printf( "%sEnd of instructions ( ; ) not found!\n", LEVEL_ERROR );
		exit( EXIT_FAILURE );
	}*/
}

void call_validation_functions( char* content_to_analysis )
{
	char char_content;
	/* if a conditional structure flag fl_verify_block = 1, and verify opening and closing code blocks with '{}' */
	register int fl_verify_block;
	match = regex_match_syntax( "(if|for|while)", content_to_analysis );	
	if( match == 1 )
	{	
		fl_verify_block = 1;
	}
	
	register int i = 0;
	LINE = 0;
	for ( i ; i < length-1 ; i++ )
	{
		match_break_line = regex_match_syntax( "\\n", &char_content );
		if( match_break_line == 1)
		{
			LINE++;
		}
		
		char_content = content_to_analysis[i];
		
		if( fl_verify_block == 1 )
		{
			get_begin_end_block( char_content );
		}
		
		/* validate_end_instructions( char_content ); */
	}
	validate_beginend_block();
}

void syntax_init( int argc, char **argv )
{
	char* content_to_analysis;
	match_break_line = 0;
	match = 0;
	count_block.count_begin = 0;
	count_block.count_end = 0;
	
	validate_extesionfile( argv[1] );		
	content_to_analysis = get_content_scriptfile( argc, argv );	
	length = strlen( content_to_analysis );	
	call_validation_functions( content_to_analysis );	
	
	
	free( content_to_analysis );
	content_to_analysis = NULL;
}
