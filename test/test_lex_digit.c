#include <stdio.h>
#include "kcc.h"
#include "test.h"

#define F "test_lex_digit"
extern int test_lex_digit(char *);
int
main(int argc, char* argv[]) {

    char *test1 = "1234567";
    char *test2 = "0000";
    char *test3 = "0.0";
    char *test4 = "hello world";

    TEST(test_lex_digit(test1) != CONTINUE, F, "test1", "fail");
    TEST(test_lex_digit(test2) != CONTINUE, F, "test2", "fail");
    TEST(test_lex_digit(test3) != CONTINUE, F, "test3", "fail");
    TEST(test_lex_digit(test4) != ERR, F, "test4", "fail");
    
    return 0;
}
