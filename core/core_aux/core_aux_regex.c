#include "core_aux_regex.h"

int regex_match_syntax(char* expression, char* str )
{
        pcre *re;
        const char *error;
        int options = 0;
        int erroffset;
		int ovector[30];
        int rc;
        //printf("expression => %s\n", expression);
        //printf("str => %s\n", str);        
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
                pcre_free(re);                			
                return 1;
        }
}
