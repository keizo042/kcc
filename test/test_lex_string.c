#include <stdio.h>
#include "kcc.h"
#include "test.h"

extern int test_lex_string(char *);
int
main(int argc, char* argv[]) {

    char *test1 = "\"hello world\"";
    char *test2 = "\"\"";
    char *test3 = "\"123456\"";

    if(test_lex_string(test1) != CONTINUE)
    {
        ERROR("test_lex_string", "test1", "fail");
    }
    if(test_lex_string(test2) != CONTINUE)
    {
        ERROR("test_lex_string", "test2", "fail");
    }
    if(test_lex_string(test3) != CONTINUE)
    {
        ERROR("test_lex_string", "test3", "fail");
    }

    

    return 0;
}
