/* typedef to functions defined by user */
typedef void DEFINED_FUNC;

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


typedef union _statement_controllers_t
{
	int count_if;
	int count_else;
	int count_def;
	
} statement_controllers_t;
