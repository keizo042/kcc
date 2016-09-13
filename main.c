#include <stdio.h>
#include <stdlib.h>
#include "kcc.h"
#include <string.h>

static char* text[] = {
    "usage : kcc [file] ",
    " ",
    " ",
    " ",
    " ",
    NULL
};

typedef struct field_s {
    char *opt;
    char *value;
}field_t;

typedef struct optargs_s {
    field_t** filed;
    uint64_t mode;
}optargs_t;

void usage()
{
    for(int i = 0; i <  7; i++)
    {
        puts(text[i]);
    }
}

optargs_t* optparse(int argc, char**argv)
{
    return NULL;
}

int
main(int argc, char* argv[]) {

    optargs_t* ARGS = optparse(argc, argv);

    
    return 0;
}
