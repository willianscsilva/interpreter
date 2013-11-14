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
	ERRORS = ERROR_EXTESIONFILE = 1;
	match = regex_match_syntax( "\\.li", file_name );
	if( match == 0 )
	{		
		exit( EXIT_FAILURE );
	}
	ERROR_EXTESIONFILE = 0;
}

void validate_be_block( char* content_to_analysis )
{		
	LEVEL_ERROR = "FATAL_ERROR: ";	
	register int i = 0;		
	char char_content;
	LINE = 0;
	for ( i ; i < tam-1 ; i++ )
	{
		char_content = content_to_analysis[i];
		match_break_line = regex_match_syntax( "\\n", &char_content );
		if( match_break_line == 1)
		{
			LINE++;
		}
		match = regex_match_syntax( "{", &char_content );
		if( match == 1)
		{
			count_begin++;			
			match = 0;
		}
		match = regex_match_syntax( "}", &char_content );
		if( match == 1)
		{
			count_end++;			
			match = 0;
		}		
	}
	
	if( count_begin < count_end )
	{
		printf( "%sBegin block ( { ) not found!\n", LEVEL_ERROR );
		count_begin = 0;
		count_end = 0;
		match_break_line = 0;
		exit( EXIT_FAILURE );
	}
	if( count_begin > count_end )
	{
		printf( "%sEnd block ( } ) not found!\n", LEVEL_ERROR );
		count_begin = 0;
		count_end = 0;
		match_break_line = 0;
		exit( EXIT_FAILURE );
	}
	count_begin = 0;
	count_end = 0;
	match_break_line = 0;
}

void validate_end_instructions( char* content_to_analysis )
{	
	match = regex_match_syntax( ";[\n]?", content_to_analysis );
	if( match == 0 )
	{
		exit( EXIT_FAILURE );
	}
}

void init( int argc, char **argv )
{
	char* content_to_analysis;	
	EXTENSION  = "\\.li";
	count_begin = 0;
	count_end = 0;
	match_break_line = 0;
	
	validate_extesionfile( argv[1] );
	
	content_to_analysis = get_content_scriptfile( argc, argv );
	tam = strlen( content_to_analysis );
	
	match = regex_match_syntax( "(if|for|while)", content_to_analysis );	
	if( match == 1 )
	{	
		validate_be_block( content_to_analysis );
	}
	/*validate_end_instructions( content_to_analysis );*/
	
	free( content_to_analysis );
}
