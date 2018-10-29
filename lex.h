#ifndef __KCC_LEXL_H
#define __KCC_LEXL_H

struct kcc_lex_context_s {
  size_t pos;
  size_t len;
};

typedef struct kcc_lex_context_s kcc_lex_context;
kcc_lex_context *kcc_lex_context_new(char *);
#endif
