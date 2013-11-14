#include "core/syntax_analysis.h"
/* gcc interpreter.c core/syntax_analysis.c core/core_aux/core_aux_regex.c -lpcre -o wli */
int main(int argc, char **argv)
{
	if ( argc <= 1 ) 
	{
		printf( "Expected Script File!\n\nUse:%s myscript.li", argv[0] );
		exit(EXIT_FAILURE);
	}	
	init(argc, argv);
	return 0;
}
