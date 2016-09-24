#include "test.h"
#include "kcc.h"
#include <stdio.h>

#define F "test_lex_skip_comment"
int main(int argc, char *argv[]) {

  char *test1 = "/* hello wold*/\n";
  char *test2 = "/* flying spaghetti monster\n//make\n//the world?\n*/";
  char *test3 = "/* */";

  TEST(test_lex_skip_comment(test1) != CONTINUE, F, "test1", "fail");
  TEST(test_lex_skip_comment(test2) != CONTINUE, F, "test2", "fail");
  TEST(test_lex_skip_comment(test3) != CONTINUE, F, "test3", "fail");

  return 0;
}
