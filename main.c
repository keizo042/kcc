#include <stdio.h>
#include <stdlib.h>
#include "kcc.h"

static char* text[] = {
    "usage : kcc [file] ",
    " ",
    " ",
    " ",
    " ",
    NULL
};

void usage()
{
    for(int i = 0; i <  7; i++)
    {
        puts(text[i]);
    }
}

int
main(int argc, char* argv[]) {
    
    return 0;
}
