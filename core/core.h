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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core_statement.h"
#include "core_variables.h"

/* LENGTH_OP_VEC_VAL => length of 'internal_comparison_operators' values */
#define LENGTH_OP_VEC_VAL 10

/* LENGTH_OP_VEC_VAL => length of 'internal_comparison_operators' index */
#define LENGTH_OP_INDEX_VAL 7

/* define comparison operators */
#define OP_EQUAL 		"=="
#define OP_NON_EQUAL 		"!="
#define OP_LESS_THAN 		"<"
#define OP_GREATER_THAN 	">"
#define OP_LESS_EQUAL_THAN 	"<="
#define OP_GREATER_EQUAL_THAN 	">="

/* get decimals ( ascii ) of operators */
#define OP_EQUAL_INT 			OP_EQUAL[0]
#define OP_NON_EQUAL_INT 		OP_NON_EQUAL[0]
#define OP_LESS_THAN_INT 		OP_LESS_THAN[0]
#define OP_GREATER_THAN_INT 		OP_GREATER_THAN[0]
#define OP_LESS_EQUAL_THAN_INT 		OP_LESS_EQUAL_THAN[0]
#define OP_GREATER_EQUAL_THAN_INT 	OP_GREATER_EQUAL_THAN[0]

/* arithmetic operators */
#define OP_ADDITION 		"+"
#define OP_SUBTRACTION 		"-"
#define OP_MULTIPLICATION 	"*"
#define OP_DIVISION 		"/"

/* arithmetic operations */
#define SUM(a, b)(a + b)
#define SUB(a, b)(a - b)
#define MULT(a, b)(a * b)
#define DIV(a, b)(a / b)

/* arithmetic operators ( ascii ) */
#define OP_ADDITION_INT 	OP_ADDITION[0]
#define OP_SUBTRACTION_INT 	OP_SUBTRACTION[0]
#define OP_MULTIPLICATION_INT 	OP_MULTIPLICATION[0]
#define OP_DIVISION_INT 	OP_DIVISION[0]

/* define control struct */
#define IF_STRUCT_CTRL 		"if"
#define ELSE_STRUCT_CTRL 	"else"
#define FOR_STRUCT_CTRL 	"for"
#define WHILE_STRUCT_CTRL 	"while"
#define DEF_STRUCT_CTRL 	"def"
#define RETURN_STRUCT_CTRL 	"return"

/* define decimals(ascii) of control struct */
#define IF_STRUCT_CTRL_INT      IF_STRUCT_CTRL[0]
#define ELSE_STRUCT_CTRL_INT    ELSE_STRUCT_CTRL[0]
#define FOR_STRUCT_CTRL_INT     FOR_STRUCT_CTRL[0]
#define WHILE_STRUCT_CTRL_INT   WHILE_STRUCT_CTRL[0]
#define DEF_STRUCT_CTRL_INT     DEF_STRUCT_CTRL[0]
#define RETURN_STRUCT_CTRL_INT  RETURN_STRUCT_CTRL[0]

/* define structures */
#define ARRAY_STRUCT "array"

/* IO */
#define PRINT_ESTATEMENT "print"

/* Define token to begin and end a block of instructions. */
#define BEGIN_BLOCK "{"
#define END_BLOCK 	"}"

/* */
#define ATTRIBUTION_OPERATOR "="

/* Define token to begin and end a block of instructions.(ascii) */
#define BEGIN_BLOCK_INT BEGIN_BLOCK[0]
#define END_BLOCK_INT 	END_BLOCK[0]

/* define decimals of print */
#define PRINT_ESTATEMENT_INT PRINT_ESTATEMENT[0]

/* save result operator char and int */
struct result_operator
{
	int op_int;
	char* op_char_p;
} result_match_operator;

/* */
typedef struct _typecasting_t
{
	int flag_cast_int;
	int flag_cast_float;
	int flag_cast_double;
	int flag_cast_char;
	int flag_cast_char_p;

	int value_cast_int;
	float value_cast_float;
	double value_cast_double;
	char value_cast_char;
	char* value_cast_char_p;
} typecasting_t;

/* content of regex result */
char* content_match;

/* Result of search by variable  */
variables_t* result_var_search;

/* Controller with flags if a statement */
statement_controllers_t statement_control;

int FOR_ITERATOR;
int control_begin_block;
int control_end_block;
int result_comparison;

int flag_typecasting;

/* Functions defined by user */
DEFINED_FUNC_T DEFINED_FUNCTION( char* function_name, char* func_attributes );

/* Checks which statement is in the script */
STATEMENT_VOID_T find_statement( char* statement_string );

/* find the comparison operator in a script line */
STATEMENT_VOID_T find_comparison_operator( char* statement_string );

STATEMENT_VOID_T arithmetic_operations( char** line_script_code );

/* execute comparison with our operators we know */
STATEMENT_INT_T exec_comparison_operator( int operator );

/* extract arguments to the operator */
STATEMENT_VOID_T extract_args_to_func_operator( char* statement_string, char* statement_extract );

/* */
STATEMENT_VOID_T attribute_value_to_variables( char* line_script_code );

/* */
typecasting_t AUTO_TYPE_CASTING( char *value_variable );

/* print statement */
STATEMENT_VOID_T PRINT_ESTATEMENT_F( char* statement_string );

/* Print only value of variables */
STATEMENT_VOID_T PRINT_VAR( char * var_to_print );

/* Print only strings expl.: print "hello world!"*/
STATEMENT_VOID_T PRINT_STRING( char * string_to_print );

/*For stetament*/
STATEMENT_VOID_T FOR_STATEMENT_F(char* statement_string);
