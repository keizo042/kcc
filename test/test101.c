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

    test(test100(str1) == LEX_CONTINUE, "test101",  "1");
    test(test100(str2) == LEX_CONTINUE, "test101",  "2");
    test(test100(str3) == LEX_CONTINUE, "test101",  "3");
    test(test100(str4) == LEX_ERR,      "test100",  "4");
    test(test100(str5) == LEX_ERR,      "test100",  "5");
    test(test100(str6) == LEX_ERR,      "test100",  "6");
    
    return 0;
}
