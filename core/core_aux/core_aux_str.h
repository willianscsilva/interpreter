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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
 * Credit this:
 * http://stackoverflow.com/questions/12789883/parallel-to-phps-explode-in-c-split-char-into-char-using-delimiter
 * the wheel has already been invented, use it, if it is possible to improve it!
 * */
char *strdup(const char *src);
void SPLIT_STR(const char *src, const char *tokens, char ***list, size_t *len);

/* 
 * Credit this:
 * http://www.rohitab.com/discuss/topic/25126-str-replace-equivalent-in-c/
 * */
char *REPLACE_STR(char *string, char *sub, char *replace);

/* remove space from begin of string */
char* INTERNAL_TRIM_L ( char* str );
