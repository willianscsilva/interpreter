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
#include "core_aux_regex.h"

int regex_match_syntax(char* expression, char* str )
{
        pcre *re;
        pcre_extra *pcre_ext;
        const char *error;
        int options = 0;
        int erroffset;
		int ovector[30];
        int rc;
        re = pcre_compile(expression, options, &error, &erroffset, NULL);
        pcre_ext = pcre_study(re, 0, &error);
        expression = NULL;        
        if(re == NULL) {
                printf("Could not compile re.\n");
                exit(0);
        }        
        rc = pcre_exec(re, pcre_ext, str, strlen(str), 0, 0, ovector, 30); 
               
        if(rc < 0)
        {
                pcre_free(re);
                return 0;
        }
        else
        {
				int begin;
				int end;
				int i;			
				for (i = 0; i < rc; i++)
				{
					begin = ovector[2 * i];
					end = ovector[2 * i + 1] - ovector[2 * i];
				}
				content_match = strndup(str + begin, end);
                pcre_free(re);
                return 1;
        }
}
