#include <stdio.h>
#include "test.h"
#include "lex.h"

int
main(int argc, char* argv[]) {
    char *str1 = "\"hello world\"";
    char *str2 = "\"    \"";
    char *str3 = "\"a\"";
    char *str4 = "\"\"";
    char *str5 = "\"1245\"";
    char *str6 = "\"";
    char *str7 = "1234";
    char *str8 = "";
    char *f = "test102.c";
    test(test200(str1) == LEX_CONTINUE, f, "1");
    test(test200(str2) == LEX_CONTINUE, f, "2");
    test(test200(str3) == LEX_CONTINUE , f, "3");
    test(test200(str4) == LEX_CONTINUE , f, "4");
    test(test200(str5) == LEX_CONTINUE, f, "5");
    test(test200(str6) == LEX_ERR, f, "6");
    test(test200(str7) == LEX_ERR, f, "7");
    test(test200(str8) == LEX_ERR, f, "8");
    
    return 0;
}
