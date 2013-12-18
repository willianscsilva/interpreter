/* Storage name and value of variables */
typedef struct variables_t 
{
        char var_name[30];
        char value[30];
        struct variables_t *next;
} variables_t;

variables_t *FIRST = NULL; /* Pointer to the first list element */
variables_t *LAST = NULL; /* Pointer to the last list element */
variables_t *ALLOCA; /* Pointer to make allocation */
