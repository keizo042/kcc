#include "test.h"
#include "kcc.h"
#include <stdio.h>

#define F "test_lex_token"

int main(int argc, char *argv[]) {
  char *test1 = "func";
  char *test2 = "f";
  char *test3 = "convert2pic";
  char *test4 = "1help";
  char *test5 = "";
  TEST(test_lex_token(test1) != CONTINUE, F, "test1", "fail");
  TEST(test_lex_token(test2) != CONTINUE, F, "test2", "fail");
  TEST(test_lex_token(test3) != CONTINUE, F, "test3", "fail");
  TEST(test_lex_token(test4) != ERR, F, "test4", "fail");
  TEST(test_lex_token(test5) != ERR, F, "test5", "fail");
  return 0;
}
