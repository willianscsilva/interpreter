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
		match = regex_match_syntax("(.*?)[ ]?[!]+|[=]{2}[ ]?(.*?)", line_script_code);
		if( match == 0 )
		{
			char*  name_var_extracted;
			char* value_var_extracted;
			char **list;
			size_t i, len;
			
			SPLIT_STR( line_script_code, ATTRIBUTION_OPERATOR, &list, &len);
			name_var_extracted = REPLACE_STR( list[0], " ", "" );
			value_var_extracted = REPLACE_STR( REPLACE_STR( list[1], " ", "" ), ";", "" );
			
			register_variables( name_var_extracted, value_var_extracted );
			name_var_extracted = NULL;
			value_var_extracted = NULL;
			free( name_var_extracted );
			free( value_var_extracted );
		}		
	}
}

STATEMENT_VOID_T arithmetic_operations( char** line_script_code )
{
	char **list;
	size_t len;
	char* left_val;
	char* right_val;
	
	char result_sum_char[10];
	char result_sub_char[10];
	char result_mult_char[10];
	char result_div_char[10];
	 
	register int match_sum 	= 0;	
	register int match_sub 	= 0;
	register int match_mult = 0;
	register int match_div 	= 0;
	
	long int left_val_c, right_val_c, result_sum, result_sub, result_mult, result_div = 0;	
	
	match_sum = regex_match_syntax(	"[0-9 ]+[+]+[0-9 ]+", *line_script_code );
	if( match_sum )
	{
		SPLIT_STR( content_match, "+", &list, &len);
		
		left_val = INTERNAL_TRIM_L ( (char*) list[0] );
		right_val = INTERNAL_TRIM_L ( (char*) list[1] );		
		
		AUTO_TYPE_CASTING( &left_val, &right_val );
		
		left_val_c =  ( long int ) left_val;
		right_val_c = ( long int ) right_val;
		
		result_sum = SUM(left_val_c, right_val_c);
		sprintf(result_sum_char, "%d", result_sum);
		
		*line_script_code = REPLACE_STR( *line_script_code, INTERNAL_TRIM_L( content_match ), result_sum_char );
		
		content_match 	= NULL;
		left_val		= NULL;
		right_val 		= NULL;
		list 			= NULL;		
	}
	match_sub 	= regex_match_syntax( "[0-9 ]+[-]+[0-9 ]+", *line_script_code );
	if( match_sub )
	{
		SPLIT_STR( content_match, "-", &list, &len);
		
		left_val = INTERNAL_TRIM_L ( (char*) list[0] );
		right_val = INTERNAL_TRIM_L ( (char*) list[1] );		
		
		AUTO_TYPE_CASTING( &left_val, &right_val );
		
		left_val_c =  ( long int ) left_val;
		right_val_c = ( long int ) right_val;
		
		result_sub = SUB( left_val_c, right_val_c );
		sprintf( result_sub_char, "%d", result_sub );
		
		*line_script_code = REPLACE_STR( *line_script_code, INTERNAL_TRIM_L( content_match ), result_sub_char );
		
		content_match 	= NULL;
		left_val		= NULL;
		right_val 		= NULL;
		list 			= NULL;
	}
	match_mult 	= regex_match_syntax( "[0-9 ]+[*]+[0-9 ]+", *line_script_code );
	if( match_mult )
	{
		SPLIT_STR( content_match, "*", &list, &len);
		
		left_val = INTERNAL_TRIM_L ( (char*) list[0] );
		right_val = INTERNAL_TRIM_L ( (char*) list[1] );		
		
		AUTO_TYPE_CASTING( &left_val, &right_val );
		
		left_val_c =  ( long int ) left_val;
		right_val_c = ( long int ) right_val;
		
		result_mult = MULT( left_val_c, right_val_c );
		sprintf( result_mult_char, "%d", result_mult );
		
		*line_script_code = REPLACE_STR( *line_script_code, INTERNAL_TRIM_L( content_match ), result_mult_char );
		
		content_match 	= NULL;
		left_val		= NULL;
		right_val 		= NULL;
		list 			= NULL;
	}
	match_div 	= regex_match_syntax( "[0-9 ]+[/]+[0-9 ]+", *line_script_code );
	if( match_div )
	{
		SPLIT_STR( content_match, "/", &list, &len);
		
		left_val = INTERNAL_TRIM_L ( (char*) list[0] );
		right_val = INTERNAL_TRIM_L ( (char*) list[1] );		
		
		AUTO_TYPE_CASTING( &left_val, &right_val );
		
		left_val_c =  ( long int ) left_val;
		right_val_c = ( long int ) right_val;
		
		result_div = DIV( left_val_c, right_val_c );
		sprintf( result_div_char, "%d", result_div );
		
		*line_script_code = REPLACE_STR( *line_script_code, INTERNAL_TRIM_L( content_match ), result_div_char );
		
		content_match 	= NULL;
		left_val		= NULL;
		right_val 		= NULL;
		list 			= NULL;
	}	
}

STATEMENT_VOID_T find_statement( char* statement_string )
{
	register int i;
	int operator;
	
	arithmetic_operations( &statement_string );
	
	for( i = 0; i < LENGTH_OP_INDEX_VAL; i++ )
	{
		if( statement_control.flag_if == 1 )
		{
			match = regex_match_syntax( BEGIN_BLOCK, statement_string);
			if( match == 1 )
			{				
				control_begin_block = 1;/* set flag where occur a '{' */				
			}
			match = regex_match_syntax( END_BLOCK, statement_string);
			if( match == 1 )/* set flag where occur a '}' */
			{
				statement_control.flag_if = 0;
				control_begin_block = 0;				
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
			register_variables_temp( name_var_extracted, "NULL", result_match_operator.op_int );
		}
		else
		{
			register_variables_temp( name_var_extracted, result_var_search->value, result_match_operator.op_int );
		}
		
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
	
	free( list );
}

STATEMENT_INT_T exec_comparison_operator( int operator )
{		
		char *value_left_temp	= NULL;
		char *value_right_temp	= NULL;		
		
		if( operator == OP_EQUAL_INT ) /* Execute equal operator ( == )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );
			AUTO_TYPE_CASTING( &value_left_temp, &value_right_temp );
			if( flag_typecasting_l == 1 && flag_typecasting_r == 1 )
			{
				if( value_left_temp == value_right_temp )
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
			else
			{
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
		}
		else if( operator == OP_NON_EQUAL_INT ) /* Execute non equal operator ( != )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );
			AUTO_TYPE_CASTING( &value_left_temp, &value_right_temp );
			if( flag_typecasting_l == 1 && flag_typecasting_r == 1 )
			{
				if( value_left_temp != value_right_temp )
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
			else
			{
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
		}
		else if( operator == OP_GREATER_THAN_INT ) /* Execute non equal operator ( > ) */
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );
			AUTO_TYPE_CASTING( &value_left_temp, &value_right_temp );
			if( flag_typecasting_l == 1 && flag_typecasting_r == 1 )
			{
				if( value_left_temp > value_right_temp )
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
			else
			{
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
		}
		else if( operator == OP_LESS_THAN_INT ) /* Execute non equal operator ( < )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );
			AUTO_TYPE_CASTING( &value_left_temp, &value_right_temp );
			if( flag_typecasting_l == 1 && flag_typecasting_r == 1 )
			{
				if( value_left_temp < value_right_temp )
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
			else
			{
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
}

/* try improve attribution to to this typecast: thus cause warning. */
STATEMENT_VOID_T AUTO_TYPE_CASTING( char **value_variable_l, char **value_variable_r )
{
	flag_typecasting_l = 0;
	flag_typecasting_r = 0;
	match = regex_match_syntax( "[A-Za-z!@#$%&*)(*/.,\\|_-]+", *value_variable_l );
	if( match == 0 )
	{			
		flag_typecasting_l = 1;
	}
	match = regex_match_syntax( "[A-Za-z!@#$%&*)(*/.,\\|_-]+", *value_variable_r );
	if( match == 0 )
	{
		flag_typecasting_r = 1;
	}
	if( flag_typecasting_l == 1 && flag_typecasting_r == 1 )
	{
		*value_variable_l = (long int)atoi(*value_variable_l);
		*value_variable_r = (long int)atoi(*value_variable_r);		
	}
}

STATEMENT_VOID_T PRINT_ESTATEMENT_F( char* statement_string )
{
	match = regex_match_syntax( "print (.*?);", statement_string );
	result_var_search = search_variables_registered( content_match );
	if( result_var_search > 0 )
	{
		PRINT_VAR( result_var_search->value );
	}
	else
	{
		PRINT_STRING( content_match );
	}
}

STATEMENT_VOID_T PRINT_VAR( char * var_to_print )
{
	var_to_print = REPLACE_STR( REPLACE_STR( var_to_print, "\"", "" ), "\n", "" );
	printf( "%s\n", INTERNAL_TRIM_L( var_to_print ) );
	var_to_print = NULL;
	free( var_to_print );
}

STATEMENT_VOID_T PRINT_STRING( char * string_to_print )
{
	char * clear_str_to_print = NULL;	
	clear_str_to_print = REPLACE_STR( REPLACE_STR( string_to_print, "\"", "" ), "\n", "" );	
	
	printf( "%s\n", INTERNAL_TRIM_L( clear_str_to_print ) );
	clear_str_to_print = NULL;
	free( clear_str_to_print );
}
