#include <stdio.h>
#include "lex.h"
#include "test.h"

int
main(int argc, char* argv[]) {
    char *id1 = "id";
    char *id2 = "str";
    char *id3 = "a2b";
    char *id4 = "222";
    char *id5 = "2ac";
    char *id6 = "\"hello\"";
    char *id7 = "int";
    char *id8 = "\0";

    test(test300(id1) == LEX_CONTINUE,  __FILE__, "1");
    test(test300(id2) == LEX_CONTINUE,  __FILE__, "2");
    test(test300(id3) == LEX_CONTINUE,  __FILE__, "3");
    test(test300(id4) == LEX_ERR,       __FILE__, "4");
    test(test300(id5) == LEX_ERR,       __FILE__, "5");
    test(test300(id6) == LEX_ERR,       __FILE__, "6");
    test(test300(id7) == LEX_ERR,       __FILE__, "7");
    test(test300(id8) == LEX_ERR,       __FILE__, "8");

    
    return 0;
}
