#include <stdio.h>
#include "kcc.h"
#include "test.h"

extern int test_lex_digit(char *);
int
main(int argc, char* argv[]) {

    char *test1 = "1234567";
    if(test_lex_digit(test1) != CONTINUE)
    {
        ERROR("test_lex_digit", "test1", "fail");
    }


    char *test2 = "0000";
    if(test_lex_digit(test2) == CONTINUE)
    {
        ERROR("test_lex_digit", "test2", "fail");
    }

    char *test3 = "0.0";
    if(test_lex_digit(test3) != CONTINUE)
    {
        ERROR("test_lex_digit", "test3", "fail");
    }

    char *test4 = "hello world";
    if(test_lex_digit(test4) == ERR)
    {
        ERROR("test_lex_digit", "test4", "fail");
    }
    
    return 0;
}
