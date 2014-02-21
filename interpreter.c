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
#include "core/syntax_analysis.h"
#include "core/core_script.h"

int main( int argc, char **argv )
{
	if ( argc <= 1 )
	{
		printf( "Expected Script File!\n\nUse:%s myscript.mav\n", argv[0] );
		exit(EXIT_FAILURE);
	}
	arg_count = argc;
	arg_val = argv;
	syntax_init(argc, argv);
	core_script_init();	
	return 0;
}
