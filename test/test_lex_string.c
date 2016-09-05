#include <stdio.h>
#include "kcc.h"
#include "test.h"

extern int test_lex_string(char *);
int
main(int argc, char* argv[]) {

    char *test1 = "\"hello world\"";
    char *test2 = "\"\"";
    char *test3 = "\"123456\"";

    if(test_lex_string(test1) != 0)
    {
        printf("fail");
    }
    if(test_lex_string(test2) != 0)
    {
        printf("fail");
    }
    if(test_lex_string(test3) == 0)
    {
        printf("fail");
    }

    

    return 0;
}
