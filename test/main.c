#include <stdio.h>
#include "kcc.h"
#define BUF_LEN 10240 
#define TEST_FILE "./test/test.c"

int
main(int argc, char* argv[]) {
    
    FILE *fp;
    char buf[BUF_LEN];
    lex_tokens_t *l;
    fp = fopen(TEST_FILE, "r");
    if(fp == NULL)
    {
        goto fail;
    }
    fread(buf, BUF_LEN, BUF_LEN -1,fp);
    l = lex(buf);
    if(l == NULL)
    {
        goto fail;
    }
        

sucess:
    printf("test pass!\n");
    return 0;
    
fail:
    printf("test fail...\n");
    return -1;
}
