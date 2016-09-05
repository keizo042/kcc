#include <stdio.h>
#include "kcc.h"
#include "test.h"

extern int test_lex_digit(char *);
int
main(int argc, char* argv[]) {

    char *test1 = "1234567";
    if(test_lex_digit(test1) != 0)
    {
        printf("lex_digit fail");
    }


    char *test2 = "0000";
    if(test_lex_digit(test2) == 0)
    {
        printf("fail\n");
    }

    char *test3 = "0.0";
    if(test_lex_digit(test3) != 0)
    {
        printf("fail\n");
    }

    char *test4 = "hello world";
    if(test_lex_digit(test4) == 0)
    {
        printf("fail\n");
    }
    
    return 0;
}
