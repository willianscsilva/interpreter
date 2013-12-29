#include "core.h"
#include "core_aux/core_aux_regex.h"
#include "core_aux/core_aux_str.h"


/* Define here all keywords to  internal stetament system */
char internal_statement[LENGTH_OP_INDEX_VAL][LENGTH_OP_VEC_VAL] = { "if", "else", "for", "while", "def", "return", "print" };

/* built-in functions */
char internal_functions[1][LENGTH_OP_VEC_VAL] = { "" };

DEFINED_FUNC_T DEFINED_FUNCTION( char* function_name, char* func_attributes )
{
	
	
}

STATEMENT_VOID_T attribute_value_to_variables( char* line_script_code )
{
	match = regex_match_syntax( ATTRIBUTION_OPERATOR, line_script_code);
	if( match == 1 )
	{
		char **list;
		size_t i, len;
		SPLIT_STR( line_script_code, ATTRIBUTION_OPERATOR, &list, &len);
	}
}

STATEMENT_VOID_T find_statement( char* statement_string )
{	
	register int i;
	int operator;	
	
	for( i = 0; i < LENGTH_OP_INDEX_VAL; i++ )
	{
		if( statement_control.flag_if == 1 )
		{
			match = regex_match_syntax( BEGIN_BLOCK, statement_string);
			if( match == 1 )
			{				
				control_begin_block = 1;/* set flag where occur a '{' */				
			}
		}
		
		match = regex_match_syntax( internal_statement[i], statement_string );
		if( match == 1 )
		{
			if( internal_statement[i][0] == IF_STRUCT_CTRL_INT )
			{
				find_comparison_operator( statement_string );				
				extract_args_to_func_operator( statement_string, IF_STRUCT_CTRL );
				result_comparison = exec_comparison_operator( result_match_operator.op_int );
				
				statement_control.flag_if = 1;/* set flag where occur a if statement */
			}
			
			if( internal_statement[i][0] == PRINT_ESTATEMENT_INT )
			{
				if( statement_control.flag_if == 1 && control_begin_block == 1 )
				{
					if( result_comparison == 1 )
					{
						PRINT_ESTATEMENT_F( statement_string );
					}
					statement_control.flag_if = 0;
					control_begin_block = 0;
				}
				else
				{
					PRINT_ESTATEMENT_F( statement_string );
				}
			}
		}
	}	
}

STATEMENT_VOID_T find_comparison_operator( char* statement_string )
{
	register int i;
	char operators_array[LENGTH_OP_INDEX_VAL][LENGTH_OP_VEC_VAL] = { OP_EQUAL, OP_NON_EQUAL, OP_LESS_THAN, OP_GREATER_THAN, OP_LESS_EQUAL_THAN, OP_GREATER_EQUAL_THAN };
	for( i = 0; i < LENGTH_OP_INDEX_VAL; i++ )
	{		
		if( strcmp( operators_array[i], "") != 0 )
		{
			match = regex_match_syntax( operators_array[i], statement_string );
			if( match == 1)
			{
				result_match_operator.op_int = content_match[0];
				result_match_operator.op_char_p = content_match;			
			}
		}
	}	
}

STATEMENT_VOID_T extract_args_to_func_operator( char* statement_string, char* statement_extract )
{
	char **list;
	size_t i, len;
	SPLIT_STR( statement_string, result_match_operator.op_char_p, &list, &len);
	char* name_var_extracted;/* name of variable defined or not in script */
	char* var_rep1 = NULL;
	char* var_rep2 = NULL;
	char* var_rep3 = NULL;
	char* var_rep4 = NULL;
	for(i = 0; i < len; ++i)
	{
		var_rep1 = REPLACE_STR( list[i], statement_extract, "" );
		var_rep2 = REPLACE_STR( var_rep1, "(", ""  );
		var_rep3 = REPLACE_STR( var_rep2, ")", "" );
		var_rep4 = REPLACE_STR( var_rep3, " ", "" );		
		name_var_extracted = REPLACE_STR( var_rep4, "\n", "" );
		
		result_var_search = search_variables_registered( name_var_extracted );
		
		if( result_var_search == 0 )
		{	
			register_variables( name_var_extracted, "NULL" );			
		}
		register_variables_temp( name_var_extracted, "NULL", result_match_operator.op_int );
		
		var_rep1 = NULL;
		var_rep2 = NULL;
		var_rep3 = NULL;
		var_rep4 = NULL;
		name_var_extracted = NULL;
		
	}
	
	free( var_rep1 );
	free( var_rep2 );
	free( var_rep3 );
	free( var_rep4 );
	free( name_var_extracted );
	
	free(list);
}

STATEMENT_INT_T exec_comparison_operator( int operator )
{		
		char *value_left_temp	= NULL;
		char *value_right_temp	= NULL;		
		
		if( operator == OP_EQUAL_INT ) /* Execute equal operator ( == )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );			
			if ( strcmp( value_left_temp, value_right_temp ) == 0 )
			{
				value_left_temp = NULL;
				value_right_temp = NULL;
				return 1;
			}
			else
			{
				value_left_temp = NULL;
				value_right_temp = NULL;
				return 0;
			}
		}
		else if( operator == OP_NON_EQUAL_INT ) /* Execute non equal operator ( != )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );			
			if ( strcmp( value_left_temp, value_right_temp ) != 0 )
			{
				value_left_temp = NULL;
				value_right_temp = NULL;			
				return 1;
			}
			else
			{
				value_left_temp = NULL;
				value_right_temp = NULL;
				return 0;
			}
		}
		else if( operator == OP_GREATER_THAN_INT ) /* Execute non equal operator ( > ) */
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );
			if ( strcmp( value_left_temp, value_right_temp ) > 0 )
			{
				value_left_temp = NULL;
				value_right_temp = NULL;			
				return 1;
			}
			else
			{
				value_left_temp = NULL;
				value_right_temp = NULL;
				return 0;
			}
		}
		else if( operator == OP_LESS_THAN_INT ) /* Execute non equal operator ( < )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );			
			if ( strcmp( value_left_temp, value_right_temp ) < 0 )
			{	
				value_left_temp = NULL;
				value_right_temp = NULL;			
				return 1;
			}
			else
			{	
				value_left_temp = NULL;
				value_right_temp = NULL;
				return 0;
			}
		}
}

STATEMENT_VOID_T PRINT_ESTATEMENT_F( char* statement_string )
{
	match = regex_match_syntax( "print (.*?);", statement_string );
	result_var_search = search_variables_registered( content_match );
	if( result_var_search > 0 )
	{
		VAR_PRINT( result_var_search->value );
	}
	else
	{
		STRING_PRINT( content_match );
	}
}

STATEMENT_VOID_T VAR_PRINT( char * var_to_print )
{
	printf( "%s\n", var_to_print );
}

STATEMENT_VOID_T STRING_PRINT( char * string_to_print )
{
	char * clear_str_to_print = NULL;	
	clear_str_to_print = REPLACE_STR( string_to_print, "\"", "" );	
	printf( "%s\n", clear_str_to_print );	
	free( clear_str_to_print );
}
