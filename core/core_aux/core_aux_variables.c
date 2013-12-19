#include "core_aux_variables.h"

variables_t *FIRST = NULL; /* Pointer to the first list element */
variables_t *LAST = NULL; /* Pointer to the last list element */
variables_t *ALLOCA; /* Pointer to make allocation */

register_variables_value_temporarily_t *FIRST_TEMP = NULL; /* Pointer to the first list element */
register_variables_value_temporarily_t *LAST_TEMP = NULL; /* Pointer to the last list element */
register_variables_value_temporarily_t *ALLOCA_TEMP; /* Pointer to make allocation */

variables_t * search_variables_registered( char *data )
{
      variables_t *pointer;
      pointer = FIRST;

      while ( ( pointer ) && ( strcmp( data, pointer->var_name ) != 0 ) ) 
      {
            pointer = pointer->next;
      }
      
      return pointer;
}

void register_variables( char *data, char* value )
{
    ALLOCA = ( struct variables_t * ) malloc( sizeof( struct variables_t ) ); 
    if ( !ALLOCA ) 
    {
       printf( "Insufficient memory!\n" );
       exit(0);
    }

    strcpy( ALLOCA->var_name, data );    
	strcpy( ALLOCA->value, value );
    
	if ( !FIRST ) 
	{                
		FIRST = ALLOCA;
		LAST = ALLOCA;
	}
	else
	{
		LAST->next = ALLOCA;
		LAST = ALLOCA;
	}
	LAST->next = NULL;
}

register_variables_value_temporarily_t * search_variables_registered_temp( char *data )
{
      register_variables_value_temporarily_t *pointer;
      pointer = FIRST_TEMP;

      while ( ( pointer ) && ( strcmp( data, pointer->var_name ) != 0 ) ) 
      {
            pointer = pointer->next;
      }
      
      return pointer;
}

void register_variables_temp( char *data, char* value )
{
    ALLOCA_TEMP = ( struct register_variables_value_temporarily_t * ) malloc( sizeof( struct register_variables_value_temporarily_t ) ); 
    if ( !ALLOCA_TEMP ) 
    {
       printf( "Insufficient memory!\n" );
       exit(0);
    }

    strcpy( ALLOCA_TEMP->var_name, data );    
	strcpy( ALLOCA_TEMP->value, value );
    
	if ( !FIRST_TEMP ) 
	{                
		FIRST_TEMP = ALLOCA_TEMP;
		LAST_TEMP = ALLOCA_TEMP;
	}
	else
	{
		LAST_TEMP->next = ALLOCA_TEMP;
		LAST_TEMP = ALLOCA_TEMP;
	}
	LAST_TEMP->next = NULL;
}

void copy_temporary_value_var( char **left_value_to_copy, char **right_value_to_copy )
{
	register_variables_value_temporarily_t *pointer = FIRST_TEMP;
	while (pointer) 
	{
		if( *left_value_to_copy == NULL )
		{
			*left_value_to_copy = pointer->value;
		}
		else if( *right_value_to_copy == NULL)
		{
			*right_value_to_copy = pointer->value;
		}
		pointer = pointer->next;
	}
}

void free_register_temp_variables()
{
	free( ALLOCA_TEMP );
}

void free_register_variables()
{
	free( ALLOCA );
}
