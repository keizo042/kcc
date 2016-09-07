#include <stdio.h>
#include "kcc.h"
#include "test.h"

#define F "lex_skip_brank"


int
main(int argc, char* argv[]) {
    
    char *test1 = "     ";
    TEST(test_lex_skip_brank(test1) != CONTINUE, F, "test1", "fail");
    return 0;
}
