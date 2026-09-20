#include <stdlib.h>   
#include <string.h>   
#include "lexer.h"
static int match_operator(
    const char *source,
    size_t pos,
    TokenType *type,
    size_t *length
) {
    if (source[pos] == '>') {
        if (source[pos + 1] == '>') {
            *type = TOK_REDIRECT_APPEND;
            *length = 2;
        } else {
            *type = TOK_REDIRECT_OUT;
            *length = 1;
        }
        return 1;
    }

    if (source[pos] == '<') {
        *type = TOK_REDIRECT_IN;
        *length = 1;
        return 1;
    }

    return 0;
}

static int scan(const char *source, TokenStream *stream)
{
    token_stream_init(stream);

    size_t pos = 0;
    size_t start = 0;
    size_t length = 0;

    char *lexeme = NULL;

    while (source[pos] != '\0') {
        TokenType cur_type;
        size_t cur_length;

        int op_status =
            match_operator(source, pos, &cur_type, &cur_length);

        /*
        Whitespace or an operator ends the current word.
         */
        if ((source[pos] == ' ' || op_status == 1) && length > 0) {
            lexeme[length] = '\0';

            Token token = {
                .type = TOK_WORD,
                .lexeme = lexeme,
                .start = start,
                .length = length
            };

            if (token_stream_push(stream, token) != 0) {
                /*
                push failed, stream doesn't own lexeme
                free lexeme then return
                 */
                free(lexeme);
                token_stream_destroy(stream);
                return -1;
            }

            /*
            stream now owns this.
            Do not free lexeme.
             */
            lexeme = NULL;
            length = 0;
        }

        /*
        Whitespace does not produce a token.
         */
        if (source[pos] == ' ') {
            pos++;
            continue;
        }

        /*
        Operator.
         */
        if (op_status == 1) {
            Token token = {
                .type = cur_type,
                .lexeme = NULL,
                .start = pos,
                .length = cur_length
            };

            if (token_stream_push(stream, token) != 0) {
                token_stream_destroy(stream);
                return -1;
            }

            pos += cur_length;
            continue;
        }

        /*
        Beginning of a new word.
         */
        if (length == 0) {
            start = pos;

            /*
            Temporary: allocate enough space for the rest of the source.
             */
            lexeme = malloc(strlen(source + pos) + 1);

            if (lexeme == NULL) {
                token_stream_destroy(stream);
                return -1;
            }
        }

        lexeme[length] = source[pos];
        length++;
        pos++;
    }

    /*
    EOF can terminate the final word.
     */
    if (length > 0) {
        lexeme[length] = '\0';

        Token token = {
            .type = TOK_WORD,
            .lexeme = lexeme,
            .start = start,
            .length = length
        };

        if (token_stream_push(stream, token) != 0) {
            free(lexeme);
            token_stream_destroy(stream);
            return -1;
        }

        /*
        Stream now owns this.
        Do not free lexeme.
         */
        lexeme = NULL;
    }

    /*
    Successful stream end with TOK_EOF.
     */
    Token eof = {
        .type = TOK_EOF,
        .lexeme = NULL,
        .start = pos,
        .length = 0
    };

    if (token_stream_push(stream, eof) != 0) {
        token_stream_destroy(stream);
        return -1;
    }

    return 0;
}