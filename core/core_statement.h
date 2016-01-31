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
/* typedef to functions defined by user */
typedef void DEFINED_FUNC_T;

/* typedef void to internal functions to statement */
typedef void STATEMENT_VOID_T;

/* typedef int to internal functions to statement */
typedef int STATEMENT_INT_T;

/* typedef char to internal functions to statement */
typedef char STATEMENT_CHAR_T;

/* typedef char* to internal functions to statement */
typedef char* STATEMENT_CHAR_P_T;


/* When function return a string, attribute here and return */
char* RETURNED_STRING_VAL;

/* When function return a integer, attribute here and return */
int* RETURNED_INT_VAL;

/* When function return a float, attribute here and return */
int* RETURNED_FLOAT_VAL;

/* When function return a double, attribute here and return */
int* RETURNED_DOUBLE_VAL;

/* When function not return, attribute here the NULL value and return */
void* RETURNED_NULL_VAL;


typedef struct _statement_controllers_t
{
	int flag_if;
	int flag_else;
	int flag_def;
	int flag_for;
	int flag_while;
	int flag_return;
	int flag_print;	
} statement_controllers_t;
