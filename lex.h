#ifndef LEX_H
#define LEX_H

struct lex_state;
typedef struct lex_state lex_state;

typedef struct lex_state {
        char *src;
        int pos;
        int width;
        int len;
        int line;
        int err;

}lex_state;

lex_state* lex_init(char *src);
int lex_state_run(lex_state *);
int lex_state_error(lex_state*state);
#endif // LEX_H
