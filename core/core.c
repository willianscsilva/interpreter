#include "core.h"
#include "core_aux/core_aux_regex.h"
#include "core_aux/core_aux_str.h"

/* Define here all keywords to  internal stetament system */
char internal_statement[LENGTH_OP_INDEX_VAL][LENGTH_OP_VEC_VAL] = { "if", "else", "for", "while", "def", "return" };

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
				//compare_comparison_operator( result_match_operator.op_int );
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
		printf("%d: %s => %s\n", i+1, list[i], statement_extract);
		var_extracted = REPLACE_STR( REPLACE_STR( REPLACE_STR( REPLACE_STR( REPLACE_STR( list[i], statement_extract, "" ), "(", "" ), ")", "" ), " ", "" ), "\n", "" );
		printf("RESULT: %s\n", var_extracted);
	}
	
	free_list( list, len );	
}

STATEMENT_VOID_T find_comparison_operator( char* statement_string )
{
	register int i;
	char operators_array[LENGTH_OP_INDEX_VAL][LENGTH_OP_VEC_VAL] = { OP_EQUAL, OP_NON_EQUAL, OP_LESS_THAN, OP_GREATER_THAN, OP_LESS_EQUAL_THAN, OP_GREATER_EQUAL_THAN };
	for( i = 0; i < LENGTH_OP_INDEX_VAL; i++ )
	{
		match = regex_match_syntax( operators_array[i], statement_string );
		if( match == 1)
		{
			result_match_operator.op_int = content_match[0];
			result_match_operator.op_char_p = content_match;
		}
	}	
}

STATEMENT_VOID_T compare_comparison_operator( int operator )
{
		if( operator == OP_EQUAL_INT )
		{	
			
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
