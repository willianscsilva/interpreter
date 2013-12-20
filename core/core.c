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

STATEMENT_VOID_T find_statement( char* statement_string )
{
	register int i;
	int operator;
	
	for( i = 0; i < LENGTH_OP_INDEX_VAL; i++ )
	{
		match = regex_match_syntax( internal_statement[i], statement_string );
		if( match == 1 )
		{
			if( internal_statement[i][0] == IF_STRUCT_CTRL_INT )
			{
				find_comparison_operator( statement_string );				
				extract_args_to_func_operator( statement_string, IF_STRUCT_CTRL );				
				exec_comparison_operator( result_match_operator.op_int );
			}			
			if( internal_statement[i][0] == PRINT_ESTATEMENT_INT )
			{
				match = regex_match_syntax( "print (.*?);", statement_string );
				result_var_search = search_variables_registered( content_match );
				if( result_var_search > 0 )
				{
					VAR_PRINT( result_var_search->value );
				}
				else
				{
					STRING_PRINT( REPLACE_STR( content_match, "\"", "" ) );
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
	char* var_extracted;
	
	for(i = 0; i < len; ++i)
	{	
		var_extracted = REPLACE_STR( REPLACE_STR( REPLACE_STR( REPLACE_STR( REPLACE_STR( list[i], statement_extract, "" ), "(", "" ), ")", "" ), " ", "" ), "\n", "" );
		
		result_var_search = search_variables_registered( var_extracted );
		
		if( result_var_search == 0 )
		{
			register_variables( var_extracted, "NULL" );
			register_variables_temp( var_extracted, "NULL" );
		}		
	}
	
	free_list( list, len );	
}

STATEMENT_INT_T exec_comparison_operator( int operator )
{
		char *value_left_temp	= NULL;
		char *value_right_temp	= NULL;
		
		if( operator == OP_EQUAL_INT )
		{	
			copy_temporary_value_var( &value_left_temp, &value_right_temp );			
			if ( strcmp( value_left_temp, value_right_temp ) == 0 )
			{
				//free_register_temp_variables();				
				return 1;
			}
			else
			{
				//free_register_temp_variables();
				return 0;
			}
		}
		else if( operator == OP_NON_EQUAL_INT )
		{
			
		}
		else if( operator == OP_LESS_THAN_INT )
		{
			
		}
		else if( operator == OP_GREATER_EQUAL_THAN_INT )
		{
			
		}
}

STATEMENT_VOID_T VAR_PRINT( char * var_to_print )
{
	printf( "%s\n", var_to_print );
}

STATEMENT_VOID_T STRING_PRINT( char * string_to_print )
{
	printf( "%s\n", string_to_print );
}
