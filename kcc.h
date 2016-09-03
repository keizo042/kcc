#ifndef KCC_H
#define KCC_H

struct lex_tokens_s;
typedef struct lex_tokens_s lex_tokens_t;

void compile(const char *);
lex_tokens_t *lex(char *);
#endif
