#include <stdio.h>

#include "lexer.h"
#include "token.h"

int main(void)
{
    char source[] = "echo hello > out";

    TokenStream stream;

    if (scan(source, &stream) != 0) {
        fprintf(stderr, "lexer failed\n");
        return 1;
    }

    for (size_t i = 0; i < stream.count; i++) {
        Token token = stream.items[i];

        printf(
            "type=%d start=%zu length=%zu",
            token.type,
            token.start,
            token.length
        );

        if (token.lexeme != NULL) {
            printf(" lexeme=\"%s\"", token.lexeme);
        }

        printf("\n");
    }

    token_stream_destroy(&stream);

    return 0;
}