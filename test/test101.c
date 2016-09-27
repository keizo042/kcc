#include <stdio.h>
#include "lex.h"
#include "test.h"


int
main(int argc, char* argv[]) {
    char *str1 = "100";
    char *str2 = "0000";
    char *str3 = "1.2";
    char *str4 = "";
    char *str5 = "a100";
    char *str6 = "abc";
    int n = LEX_ERR;
    n = test100(str1);
    test(n == LEX_CONTINUE, "test101",  "1");
    n = test100(str2);
    test(n == LEX_CONTINUE, "test101",  "2");
    n = test100(str3);
    test( n == LEX_CONTINUE, "test101",  "3");
    n = test100(str4);
    test( n == LEX_ERR,      "test100",  "4");
    n = test100(str5);
    test( n == LEX_ERR,      "test100",  "5");
    n = test100(str6);
    test( n == LEX_ERR,      "test100",  "6");
    
    return 0;
}
