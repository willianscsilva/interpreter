#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Storage name and value of variables */
typedef struct variables_t 
{
        char var_name[30];
        char value[30];
        struct variables_t *next;
} variables_t;

/* Search by variables registered */
variables_t * search_variables_registered( char *data );

/* Register the variables in local struct ( linked list ) */
void register_variables( char *data, char* value );

/* */
void free_register_variables();

typedef struct register_variables_value_temporarily_t
{
	char var_name[30];
	char value[30];
	struct register_variables_value_temporarily_t *next;
} register_variables_value_temporarily_t;

/* */
register_variables_value_temporarily_t * search_variables_registered_temp( char *data );

/* */
void register_variables_temp( char *data, char* value );

/* */
void copy_temporary_value_var( char **left_value_to_copy, char **right_value_to_copy );

/* */
void free_register_temp_variables();
