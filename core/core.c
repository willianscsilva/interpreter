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
	char* internal_content_match;
	
	char result_sum_char[10];
	char result_sub_char[10];
	char result_mult_char[10];
	char result_div_char[10];
	 
	register int match_sum 	= 0;	
	register int match_sub 	= 0;
	register int match_mult = 0;
	register int match_div 	= 0;
	
	typecasting_t result_type_cast_l;
	typecasting_t result_type_cast_r;
	
	int result_sum_int = 0, result_sub_int = 0, result_mult_int = 0, result_div_int = 0;	
	float result_sum_float = 0, result_sub_float = 0, result_mult_float = 0, result_div_float = 0;	
	
	match_sum = regex_match_syntax(	"[0-9. ]+[+]+[0-9. ]+", *line_script_code );
	internal_content_match = content_match;
	if( match_sum == 1 )
	{
		
		SPLIT_STR( internal_content_match, "+", &list, &len);
		
		left_val	= INTERNAL_TRIM_L( list[0] );		
		right_val 	= INTERNAL_TRIM_L( list[1] );
		
		result_type_cast_l = AUTO_TYPE_CASTING( left_val);
		result_type_cast_r = AUTO_TYPE_CASTING( right_val );
					
		if( result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_int == 1 )
		{
			result_sum_int = SUM(result_type_cast_l.value_cast_int, result_type_cast_r.value_cast_int);
		}
		else if( result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_float == 1 )
		{
			result_sum_int = SUM(result_type_cast_l.value_cast_int, result_type_cast_r.value_cast_float);
		}
		else if( result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_int == 1 )
		{
			result_sum_int = SUM(result_type_cast_l.value_cast_float, result_type_cast_r.value_cast_int);
		}
		else if( result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_float == 1 )
		{
			result_sum_float = SUM(result_type_cast_l.value_cast_float, result_type_cast_r.value_cast_float);
		}
		
		if( result_sum_float != 0 )
		{
			sprintf( result_sum_char, "%f", result_sum_float );
		}
		else if( result_sum_int != 0 )
		{
			sprintf( result_sum_char, "%d", result_sum_int );
		}
		else
		{
			sprintf( result_sum_char, "%d", 0 );
		}
		*line_script_code = REPLACE_STR( *line_script_code, INTERNAL_TRIM_L( internal_content_match ), result_sum_char );
		
		internal_content_match 	= NULL;
		content_match 			= NULL;
		
		result_type_cast_l.flag_cast_int 	= 0;
		result_type_cast_r.flag_cast_int 	= 0;
		result_type_cast_l.value_cast_float = 0;
		result_type_cast_r.value_cast_float = 0;
		flag_typecasting = 0;
		
		left_val	= NULL;
		right_val 	= NULL;
		list 		= NULL;
		len			= 0;
	}
	
	match_sub = regex_match_syntax( "[0-9. ]+[-]+[0-9. ]+", *line_script_code );
    internal_content_match = content_match;
	if( match_sub )
	{
		SPLIT_STR( internal_content_match, "-", &list, &len);
		
		left_val	= INTERNAL_TRIM_L( list[0] );		
		right_val 	= INTERNAL_TRIM_L( list[1] );
		
		result_type_cast_l = AUTO_TYPE_CASTING( left_val);
		result_type_cast_r = AUTO_TYPE_CASTING( right_val );
					
		if( result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_int == 1 )
		{
			result_sub_int = SUB(result_type_cast_l.value_cast_int, result_type_cast_r.value_cast_int);			
		}
		else if( result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_float == 1 )
		{
			result_sub_int = SUB(result_type_cast_l.value_cast_int, result_type_cast_r.value_cast_float);
		}
		else if( result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_int == 1 )
		{
			result_sub_int = SUB(result_type_cast_l.value_cast_float, result_type_cast_r.value_cast_int);
		}
		else if( result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_float == 1 )
		{
			result_sub_float = SUB(result_type_cast_l.value_cast_float, result_type_cast_r.value_cast_float);
		}
		
		if( result_sub_float != 0 )
		{
			sprintf( result_sub_char, "%f", result_sub_float );
		}
		else if( result_sub_int != 0 )
		{
			sprintf( result_sub_char, "%d", result_sub_int );
		}
		else
		{
			sprintf( result_sub_char, "%d", 0 );
		}
		
		*line_script_code = REPLACE_STR( *line_script_code, INTERNAL_TRIM_L( internal_content_match ), result_sub_char );
				
		internal_content_match 	= NULL;
		content_match 			= NULL;
		
		result_type_cast_l.flag_cast_int 	= 0;
		result_type_cast_r.flag_cast_int 	= 0;
		result_type_cast_l.value_cast_float = 0;
		result_type_cast_r.value_cast_float = 0;
		flag_typecasting = 0;
		
		left_val	= NULL;
		right_val 	= NULL;
		list 		= NULL;
		len			= 0;
	}
	match_mult 	= regex_match_syntax( "[0-9. ]+[*]+[0-9. ]+", *line_script_code );
	internal_content_match = content_match;
	if( match_mult )
	{
		SPLIT_STR( internal_content_match, "*", &list, &len);
		
		left_val	= INTERNAL_TRIM_L( list[0] );		
		right_val 	= INTERNAL_TRIM_L( list[1] );
		
		result_type_cast_l = AUTO_TYPE_CASTING( left_val);
		result_type_cast_r = AUTO_TYPE_CASTING( right_val );
					
		if( result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_int == 1 )
		{
			result_mult_int = MULT(result_type_cast_l.value_cast_int, result_type_cast_r.value_cast_int);
		}
		else if( result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_float == 1 )
		{
			result_mult_int = MULT(result_type_cast_l.value_cast_int, result_type_cast_r.value_cast_float);
		}
		else if( result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_int == 1 )
		{
			result_mult_int = MULT(result_type_cast_l.value_cast_float, result_type_cast_r.value_cast_int);
		}
		else if( result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_float == 1 )
		{
			result_mult_float = MULT(result_type_cast_l.value_cast_float, result_type_cast_r.value_cast_float);
		}
		
		if( result_mult_float != 0 )
		{
			sprintf( result_mult_char, "%f", result_mult_float );
		}
		else if( result_mult_int != 0 )
		{
			sprintf( result_mult_char, "%d", result_mult_int );
		}
		else
		{
			sprintf( result_mult_char, "%d", 0 );
		}
		*line_script_code = REPLACE_STR( *line_script_code, INTERNAL_TRIM_L( internal_content_match ), result_mult_char );
		
		internal_content_match 	= NULL;
		content_match 			= NULL;
		
		result_type_cast_l.flag_cast_int 	= 0;
		result_type_cast_r.flag_cast_int 	= 0;
		result_type_cast_l.value_cast_float = 0;
		result_type_cast_r.value_cast_float = 0;
		flag_typecasting = 0;
		
		left_val	= NULL;
		right_val 	= NULL;
		list 		= NULL;
		len			= 0;
	}
	match_div 	= regex_match_syntax( "[0-9. ]+[/]+[0-9. ]+", *line_script_code );
	internal_content_match = content_match;
	if( match_div )
	{
		SPLIT_STR( content_match, "/", &list, &len);
		
		left_val	= INTERNAL_TRIM_L( list[0] );		
		right_val 	= INTERNAL_TRIM_L( list[1] );
		
		result_type_cast_l = AUTO_TYPE_CASTING( left_val);
		result_type_cast_r = AUTO_TYPE_CASTING( right_val );
					
		if( result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_int == 1 )
		{
			result_div_int = DIV(result_type_cast_l.value_cast_int, result_type_cast_r.value_cast_int);
		}
		else if( result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_float == 1 )
		{
			result_div_int = DIV(result_type_cast_l.value_cast_int, result_type_cast_r.value_cast_float);
		}
		else if( result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_int == 1 )
		{
			result_div_int = DIV(result_type_cast_l.value_cast_float, result_type_cast_r.value_cast_int);
		}
		else if( result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_float == 1 )
		{
			result_div_float = DIV(result_type_cast_l.value_cast_float, result_type_cast_r.value_cast_float);
		}
		
		if( result_div_float != 0 )
		{
			sprintf( result_div_char, "%f", result_div_float );
		}
		else if( result_div_int != 0 )
		{
			sprintf( result_div_char, "%d", result_div_int );
		}
		else
		{
			sprintf( result_div_char, "%d", 0 );
		}
		*line_script_code = REPLACE_STR( *line_script_code, INTERNAL_TRIM_L( internal_content_match ), result_div_char );
		
		internal_content_match 	= NULL;
		content_match 			= NULL;
		
		result_type_cast_l.flag_cast_int 	= 0;
		result_type_cast_r.flag_cast_int 	= 0;
		result_type_cast_l.value_cast_float = 0;
		result_type_cast_r.value_cast_float = 0;
		flag_typecasting = 0;		
		
		left_val	= NULL;
		right_val 	= NULL;
		list 		= NULL;
		len			= 0;
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
		
		flag_typecasting = 0;
		
		typecasting_t result_type_cast_l;
		typecasting_t result_type_cast_r;
		
		if( operator == OP_EQUAL_INT ) /* Execute equal operator ( == )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );			
			
			result_type_cast_l = AUTO_TYPE_CASTING( value_left_temp);
			result_type_cast_r = AUTO_TYPE_CASTING( value_right_temp );
			
			if( flag_typecasting == 1 )
			{				
				if( (result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_int == 1) )
				{
					if( result_type_cast_l.value_cast_int == result_type_cast_r.value_cast_int )
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
				else if( (result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_float == 1) )
				{
					if( result_type_cast_l.value_cast_float == result_type_cast_r.value_cast_float )
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
					value_left_temp = NULL;
					value_right_temp = NULL;
					return 0;
				}
			}
			else
			{
				if ( strlen( value_left_temp ) == strlen( value_right_temp ) )
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
			result_type_cast_l.flag_cast_int 	= 0;
			result_type_cast_l.value_cast_float = 0;
			result_type_cast_r.flag_cast_int 	= 0;			
			result_type_cast_r.value_cast_float = 0;
			flag_typecasting = 0;
		}
		else if( operator == OP_GREATER_THAN_INT ) /* Execute non equal operator ( > ) */
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );
						
			result_type_cast_l = AUTO_TYPE_CASTING( value_left_temp);
			result_type_cast_r = AUTO_TYPE_CASTING( value_right_temp );
			
			if( flag_typecasting == 1 )
			{
				if( (result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_int == 1) )
				{
					if( result_type_cast_l.value_cast_int > result_type_cast_r.value_cast_int )
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
				else if( (result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_float == 1) )
				{
					if( result_type_cast_l.value_cast_float > result_type_cast_r.value_cast_float )
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
					value_left_temp = NULL;
					value_right_temp = NULL;
					return 0;
				}
			}
			else
			{
				if ( strlen( value_left_temp ) > strlen( value_right_temp ) )
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
			result_type_cast_l.flag_cast_int 	= 0;
			result_type_cast_l.value_cast_float = 0;
			result_type_cast_r.flag_cast_int 	= 0;			
			result_type_cast_r.value_cast_float = 0;
			flag_typecasting = 0;
		}
		else if( operator == OP_NON_EQUAL_INT ) /* Execute non equal operator ( != )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );
			
			result_type_cast_l = AUTO_TYPE_CASTING( value_left_temp);
			result_type_cast_r = AUTO_TYPE_CASTING( value_right_temp );
			
			if( flag_typecasting == 1 )
			{
				if( (result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_int == 1) )
				{
					if( result_type_cast_l.value_cast_int != result_type_cast_r.value_cast_int )
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
				else if( (result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_float == 1) )
				{
					if( result_type_cast_l.value_cast_float != result_type_cast_r.value_cast_float )
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
					value_left_temp = NULL;
					value_right_temp = NULL;
					return 0;
				}
			}
			else
			{
				if ( strlen( value_left_temp ) != strlen( value_right_temp ) )
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
			result_type_cast_l.flag_cast_int 	= 0;
			result_type_cast_l.value_cast_float = 0;
			result_type_cast_r.flag_cast_int 	= 0;			
			result_type_cast_r.value_cast_float = 0;
			flag_typecasting = 0;
		}		
		else if( operator == OP_LESS_THAN_INT ) /* Execute non equal operator ( < )*/
		{
			copy_temporary_value_op_var( &value_left_temp, &value_right_temp, operator );
			
			result_type_cast_l = AUTO_TYPE_CASTING( value_left_temp);
			result_type_cast_r = AUTO_TYPE_CASTING( value_right_temp );
			
			if( flag_typecasting == 1 )
			{
				if( (result_type_cast_l.flag_cast_int == 1 && result_type_cast_r.flag_cast_int == 1) )
				{
					if( result_type_cast_l.value_cast_int < result_type_cast_r.value_cast_int )
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
				else if( (result_type_cast_l.flag_cast_float == 1 && result_type_cast_r.flag_cast_float == 1) )
				{
					if( result_type_cast_l.value_cast_float < result_type_cast_r.value_cast_float )
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
					value_left_temp = NULL;
					value_right_temp = NULL;
					return 0;
				}
			}
			else
			{
				if ( strlen( value_left_temp ) < strlen( value_right_temp ) )
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
			result_type_cast_l.flag_cast_int 	= 0;
			result_type_cast_l.value_cast_float = 0;
			result_type_cast_r.flag_cast_int 	= 0;			
			result_type_cast_r.value_cast_float = 0;
			flag_typecasting = 0;			
		}
}

typecasting_t AUTO_TYPE_CASTING( char *value_variable )
{
        typecasting_t value_casted;
        value_casted.flag_cast_float = 0;
        value_casted.flag_cast_int = 0;
        match = regex_match_syntax( "[A-Za-z!@#$%&*)(*/,\\|_-]+", value_variable );
        if( match == 0 )
        {
			flag_typecasting = 1;
			match = regex_match_syntax( "[.]+", value_variable );
			if( match == 1 )
			{
					value_casted.flag_cast_float = 1;
					value_casted.value_cast_float = atof( value_variable );
			}
			else
			{
					value_casted.flag_cast_int = 1;
					value_casted.value_cast_int = atoi( value_variable );
			}
        }
        else
        {
			value_casted.value_cast_char_p = value_variable;
		}
        return value_casted;
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
