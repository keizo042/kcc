#include "test.h"
#include "kcc.h"
#include <stdio.h>

#define F "test_lex_string"

extern int test_lex_string(char *);
int main(int argc, char *argv[]) {

  char *test1 = "\"hello world\"";
  char *test2 = "\"\"";
  char *test3 = "\"123456\"";
  char *test4 = "\"%d is integer\"";
  char *test5 = "\"%s is string\"";
  char *test6 = "function";
  char *test7 = "12345";
  char *test8 = "";
  TEST(test_lex_string(test1) != CONTINUE, F, "test1", "fail");
  TEST(test_lex_string(test2) != CONTINUE, F, "test2", "fail");
  TEST(test_lex_string(test3) != CONTINUE, F, "test3", "fail");
  TEST(test_lex_string(test4) != CONTINUE, F, "test4", "fail");
  TEST(test_lex_string(test5) != CONTINUE, F, "test5", "fail");
  TEST(test_lex_string(test6) != ERR, F, "test6", "fail");
  TEST(test_lex_string(test7) != ERR, F, "test7", "fail");
  TEST(test_lex_string(test8) != ERR, F, "test8", "fail");
  return 0;
}
