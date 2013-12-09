#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core_statement.h"

/* LENGTH_OP_VEC_VAL => length of 'internal_comparison_operators' values */
#define LENGTH_OP_VEC_VAL 10

/* define comparison operators */
#define OP_EQUAL "=="
#define OP_NON_EQUAL "!="
#define OP_LESS_THAN "<"
#define OP_GREATER_THAN ">"
#define OP_LESS_EQUAL_THAN "<="
#define OP_GREATER_EQUAL_THAN ">="

/* get decimals(ascii) of operators */
#define OP_EQUAL_INT OP_EQUAL[0]
#define OP_NON_EQUAL_INT OP_NON_EQUAL[0]
#define OP_LESS_THAN_INT OP_LESS_THAN[0]
#define OP_GREATER_THAN_INT OP_GREATER_THAN[0]
#define OP_LESS_EQUAL_THAN_INT OP_LESS_EQUAL_THAN[0]
#define OP_GREATER_EQUAL_THAN_INT OP_GREATER_EQUAL_THAN[0]

/* Functions defined by user */
DEFINED_FUNC DEFINED_FUNCTION( char* function_name, char* func_attributes );

/* Checks which statement is in the script */
STATEMENT_T find_statement( char* statement_string );
