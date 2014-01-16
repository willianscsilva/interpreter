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

char* INTERNAL_TRIM ( char* str );
