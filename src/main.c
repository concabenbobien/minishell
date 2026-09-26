#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "token.h"

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;

    while (1) {
        printf("minish$ ");
        fflush(stdout);

        ssize_t read = getline(&line, &capacity, stdin);

        if (read == -1) {
            break;  /* EOF or input error */
        }

        /* Remove newline added when Enter was pressed. */
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        TokenStream tokens;

        if (scan(line, &tokens) != 0) {
            fprintf(stderr, "lexer error\n");
            continue;
        }

        SimpleCommand command;

        if (parse_simple_command(&tokens, &command) != 0) {
            fprintf(stderr, "parse error\n");
            token_stream_destroy(&tokens);
            continue;
        }

        if (execute_simple_command(&command) != 0) {
            fprintf(stderr, "execution error\n");
        }

        simple_command_destroy(&command);
        token_stream_destroy(&tokens);
    }

    free(line);
    return 0;
}