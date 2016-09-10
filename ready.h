typedef struct reserved_s {
        char *sym;
        uint64_t typ;
}reserved_t;

reserved_t resword[] = {
        { .sym = "if", .typ = LEX_TOKEN_IF},
        { .sym = "while", .typ = LEX_TOKEN_WHILE },
        { .sym = "sizeof", .typ = LEX_TOKEN_SIZEOF },
        { .sym = "return", .typ = LEX_TOKEN_RETURN },
        { .sym = "goto", .typ = LEX_TOKEN_GOTO},
        { .sym = "switch", .typ = LEX_TOKEN_SWITCH},
        { .sym = "continue", .typ = LEX_TOKEN_CONTINUE},
        { .sym = "else", .typ = LEX_TOKEN_ELSE},
        { .sym = "for", .typ = LEX_TOKEN_FOR},
        { .sym = "typefef", .typ = LEX_TOKEN_TYPEDEF},
        { .sym = "struct", .typ = LEX_TOKEN_STRUCT},
        {}
};

const char *type[] = {
        "int",
        "char",
        "long",
        "short",
        "float",
        "void",
        "double",
        ""
};

const char *specifier[] = {
        "signed",
        "unsigned",
        "volatile",
        "extern",
        "static",
        "register",
        "union",
        ""

};
