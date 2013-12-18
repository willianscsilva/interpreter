#include "core_aux_variables.h"

variables_t * LIST_SEARCH( char *data ) 
{
      variables_t *pointer;
      pointer = primeiro;

      while ( ( pointer ) && ( strcmp( data, pointer->var_name ) != 0 ) ) 
      {
            pointer = pointer->next;
      }
      
      return pointer;
}

void INSERT_IN_LIST( char *data, char* value ) 
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
