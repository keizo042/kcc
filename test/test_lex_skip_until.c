#include <stdio.h>
#include "test.h"
#include "kcc.h"

int
main(int argc, char* argv[]) {
    
    if(test_lex_skip_until() == ERR)
    {
        ERROR("test_lex_skip_until", "test", "error");
    }
}
