#include "test.h"

char *test2_code_comment = "// yuyushiki is awesome. //";
char *test2_code_comments = "/* Domo Geek=san.\nNinja Slayer desu\n*/";
static lex_token_t test2_expect_tokens[] = {{.typ = LEX_TOKEN_EOL}, {}

};

static int lex_test2_comment(lex_tokens_t *tokens) {
  lex_tokens_t *expect = build_expect_tokens(test2_expect_tokens);
  if (tokens == NULL) {
    ERROR("test2", "init", "fail to build expect tokens");
    return -1;
  }

  lex_tokens_t *e = expect, *t = tokens;
  while (t != NULL) {

    if (strcmp(e->token->sym, t->token->sym) != 0) {
      ERROR("test2", "lex_test2_comment", "mismatch symbol");
      return -4;
    }
    if (e->token->typ != t->token->typ) {
      ERROR("test2", "lex_test2_comment", "mismatch type");
      return -6;
    }
    e = e->next;
    t = t->next;
  }
  expect_tokens_free(expect);
  return 0;
}

static lex_token_t test2_comments_expect_tokens[] = {{.typ = LEX_TOKEN_EOL}};

static int lex_test2_comments(lex_tokens_t *tokens) {
  lex_tokens_t *expect = build_expect_tokens(test2_comments_expect_tokens);
  expect_tokens_free(expect);
  return -1;
}

int main() {
  lex_state *l2comment = NULL, *l2comments = NULL;
  int flag = 0;

  l2comment = lex(test2_code_comment);
  if (l2comment == NULL) {
    flag = 1;
    ERROR("test2", "test2_code_comment", "fail to lex");
    goto test2_end;
  }

  if (lex_test2_comment(l2comment->head)) {
    flag = 1;
    goto test2_end;
  }

  l2comments = lex(test2_code_comments);
  if (l2comments == NULL) {
    ERROR("test2", "test2_code_comments", "fail to lex");
    goto test2_end;
  }

  if (lex_test2_comments(l2comments->head) != 0) {
    goto test2_end;
  }

test2_end:

  if (flag == 0) {
    return 0;
  } else {
    return -1;
  }
}
