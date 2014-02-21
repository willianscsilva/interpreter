/*
	+----------------------------------------------------------------------------------------------------+
	|Author	 : Willians Costa da Silva																	 |
	|Email	 : willianscsilva@gmail.com																	 |
	+----------------------------------------------------------------------------------------------------+
	|License : GNU General Public License version 2.0 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html |
	|Created : 2013-12-01												                                 |
	|Note    : Copy, distribute, modify freely, but keep the credits, please.							 |
	+----------------------------------------------------------------------------------------------------+
*/
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
	int operator_id;
	struct register_variables_value_temporarily_t *next;
} register_variables_value_temporarily_t;

/* */
register_variables_value_temporarily_t * search_variables_registered_temp( char *data );

/* */
void register_variables_temp( char *data, char* value, int operator_id );

/* */
void copy_temporary_value_op_var( char **left_value_to_copy, char **right_value_to_copy, int operator_id );

/* */
void free_register_temp_variables();
