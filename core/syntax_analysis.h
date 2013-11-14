#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int match;
char* LEVEL_ERROR;
int ERROR_BEGINEND_BLOCK;
int ERROR_EXTESIONFILE;
int ERROR_ENDINSTRUCTION;
int ERRORS;
int LINE_ERROR;
int LINE;
int count_begin;
int count_end;
int match_break_line;
int tam;
char* EXTENSION;
extern int total_matchs;
/* Get script file content */
char* get_content_scriptfile( int argc, char **argv );

/* Validate the extension file *.li */
void validate_extesionfile( char* file_name );

/* Validate begin and end of code block */
void validate_be_block( char* content_to_analysis );

/* Validate end of instrauction */
void validate_end_instructions( char* content_to_analysis );

/* Initializes all functions */
void init( int argc, char **argv );
