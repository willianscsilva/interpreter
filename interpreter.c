#include "core/syntax_analysis.h"
#include "core/core_script.h"

int main( int argc, char **argv )
{
	if ( argc <= 1 )
	{
		printf( "Expected Script File!\n\nUse:%s myscript.li\n", argv[0] );
		exit(EXIT_FAILURE);
	}
	arg_count = argc;
	arg_val = argv;
	//syntax_init(argc, argv);
	core_script_init();
	return 0;
}
