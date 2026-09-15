#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>
typedef enum {
    TOK_WORD,
    TOK_DIRECT_APPEND,
    TOK_DIRECT_OUT,
    TOK_DIRECT_IN,
    TOK_EOF
} 
TokenType;

typedef struct 
{
    TokenType type;
    char *lexeme;
    size_t start;   /* Starting position in the source line. */
    size_t length;  /* Length of the token in the source line. 
                    Length after normalized is strlen(token.lexeme)*/
} Token;

typedef struct 
{
    Token *items;
    size_t capacity;
    size_t count;
} TokenStream;
void token_stream_init(TokenStream *stream);
int token_stream_push(TokenStream *stream, Token token);
void token_stream_destroy(TokenStream *stream);
#endif