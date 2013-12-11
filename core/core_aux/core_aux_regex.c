#include "core_aux_regex.h"

int regex_match_syntax(char* expression, char* str )
{
        pcre *re;
        const char *error;
        int options = 0;
        int erroffset;
		int ovector[30];
        int rc;
        re = pcre_compile(expression, options, &error, &erroffset, NULL);
        if(re == NULL) {
                printf("Could not compile re.\n");
                exit(0);
        }        
        rc = pcre_exec(re, NULL, str, strlen(str), 0, 0, ovector, 30);        
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
