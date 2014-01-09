#include "core_script.h"
#include "core.h"

void read_script_file()
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	register int i;

	fp = fopen( arg_val[1], "r" );
	if (fp == NULL)
	{	
		printf( "Script file not found!\n" );
		exit(EXIT_FAILURE);
	}
	i = 1;
	while ( (read = getline(&line, &len, fp)) != -1 ) 
	{
		attribute_value_to_variables( line );
		find_statement( line );
		//break;//tirar isso depois
		i++;
	}

	if ( line )
	{
		free(line);
	}		
}

void core_script_init()
{
	read_script_file();	
	free_register_variables();
	free_register_temp_variables();
}
