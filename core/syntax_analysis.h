#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Is a flag to result matched or not in regex. */
int match;

/* Identify level error: "warning", "fatal error", etc. */
char* LEVEL_ERROR;

/* Identify line of a error. */
int LINE_ERROR;

/* Iterating of code lines. */
int LINE;

/* match when find a \n. */
int match_break_line;

/* length of code block. */
int length;

/* Define extension name to validation of extensions. */
#ifndef EXTENSION
#define EXTENSION "\\.mav";
#endif

/* struct to count begin and end of code block. */
struct count_begin_end_block
{
	int count_begin;
	int count_end;
};

struct count_begin_end_block count_block;

/* Get script file content */
char* get_content_scriptfile( int argc, char **argv );

/* Validate the extension file *.li */
void validate_extesionfile( char* file_name );

/* Get begin and end of code block */
void get_begin_end_block( char char_content );

/* Validate begin and end of code block */
void validate_beginend_block();

/* Validate end of instructions */
void validate_end_instructions( char char_content );

/* Read line by line of code block and call all function of validation here */
void call_validation_functions( char* content_to_analysis );

/* main function equivalent */
void syntax_init( int argc, char **argv );
