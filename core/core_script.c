/*
	+----------------------------------------------------------------------------------------------------+
	|Author	 : Willians Costa da Silva																	 |
	|Email	 : willianscsilva@gmail.com																	 |
	+----------------------------------------------------------------------------------------------------+
	|License : GNU General Public License version 2.0 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html |
	|Created : 2013-12-01												                                 |
	|Note    : Copy, distribute, modify freely, but keep the credits, please.							 |
	+----------------------------------------------------------------------------------------------------+
*/
#include "core_script.h"
#include "core.h"
#include "core_aux/core_aux_regex.h"
#include "syntax_analysis.h"

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
		int match = regex_match_syntax( "^[\n]+", line );
		if( match == 0 )
		{
			validate_end_instructions( line );
		}
		attribute_value_to_variables( line );
		find_statement( line );
		i++;
		LINE_ERROR++;
	}

	if ( line )
	{
		free(line);
	}
}

void core_script_init()
{
	LINE_ERROR = 1;
	read_script_file();

	free_register_variables();
	free_register_temp_variables();
}
