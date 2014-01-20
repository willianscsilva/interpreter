#include "core_aux_str.h"

char* REPLACE_STR(char *string, char *sub, char *replace)
{
	if(!string || !sub || !replace) 
	{
		return NULL;
	}
	char *pos = string; 
	int found = 0;
	while( ( pos = strstr( pos, sub ) ) )
	{
		pos += strlen(sub);
		found++;
	}
	if(found == 0) 
	{
		return string;
	}
	int size = ( ( strlen( string ) + ( strlen( sub ) * found ) ) + ( strlen( replace ) * found ) ) * 10;/* 10 is a magic nunber */
	char *result = ( char* ) malloc( size );
	pos = string;
	char *pos1;
	int len = 0;
	while( ( pos1 = strstr( pos, sub ) ) )
	{
		len = (pos1 - pos);
		strncat( result, pos, len );
		strncat( result, replace, strlen( replace ) );
		pos = ( pos1 + strlen( sub ) );
	}
	if( pos != ( string + strlen( string ) ) )
	{
		strncat( result, pos, ( string - pos ) );
	}	
	return result;
}

char *strdup(const char *src)
{
    char *tmp = malloc(strlen(src) + 1);
    if(tmp)
        strcpy(tmp, src);
    return tmp;
}

void SPLIT_STR(const char *src, const char *tokens, char ***list, size_t *len)
{   
    if(src == NULL || list == NULL || len == NULL)
        return;

    char *str, *copy, **_list = NULL, **tmp;
    *list = NULL;
    *len  = 0;

    copy = strdup(src);
    if(copy == NULL)
        return;

    str = strtok(copy, tokens);
    if(str == NULL)
        goto free_and_exit;

    _list = realloc(NULL, sizeof *_list);
    if(_list == NULL)
        goto free_and_exit;

    _list[*len] = strdup(str);
    if(_list[*len] == NULL)
        goto free_and_exit;
    (*len)++;


    while((str = strtok(NULL, tokens)))
    {   
        tmp = realloc(_list, (sizeof *_list) * (*len + 1));
        if(tmp == NULL)
            goto free_and_exit;

        _list = tmp;

        _list[*len] = strdup(str);
        if(_list[*len] == NULL)
            goto free_and_exit;
        (*len)++;
    }


free_and_exit:
    *list = _list;
    free(copy);
}

char* INTERNAL_TRIM_L ( char* str )
{
	register int str_length = 0;
	register int i;
	char* space = " ";
	int space_int = space[0];	
	
	str_length = strlen( str );	
	char* str_new = (char*) malloc( ( str_length ) * sizeof( char ) );
	char* str_swap = (char*) malloc( ( str_length ) * sizeof( char ) );
	for( i = 0; i < str_length; i++ )
	{
			if( str[i] != space_int )
			{
					str_swap = &str[i];
					strcpy( str_new, str_swap );
					break;
			}
	}
	str_swap = NULL;
	free( str_swap );
	return str_new;
}
