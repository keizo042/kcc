#include <stdio.h>
#include <string.h>
#include "lex.h"
#include "parse.h"
#include "gen.h"


#define CMP(lv, rv) strncmp(lv, rv, strlen(rv))

int
main(int argc, char* argv[]) {

    if(argc < 2) {
        return 1;
    }
    if(CMP(argv[1],"lex")){
        return 1;
    }
    if(CMP(argv[1], "parse")){
        return 1;
    }
    if(CMP(argv[1], "gen")){
        return 1;
    }
    
    return 0;
}
