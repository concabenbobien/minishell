#include <stdlib.h>

#include "parser.h"

int parse_simple_command(
    const TokenStream *tokens,
    SimpleCommand *command
) {
    size_t argc = 0;

    /* First pass: count WORD tokens. */
    while (tokens->items[argc].type == TOK_WORD) {
        argc++;
    }

    /* For v0.1, anything except EOF after the words is unsupported. */
    if (tokens->items[argc].type != TOK_EOF) {
        return -1;
    }

    command->argv = malloc((argc + 1) * sizeof(*command->argv));

    /*malloc error*/
    if (command->argv == NULL) {
        return -1;
    }

    command->argc = argc;

    /* Second pass: borrow each lexeme pointer. */
    for (size_t i = 0; i < argc; i++) {
        command->argv[i] = tokens->items[i].lexeme;
    }

    command->argv[argc] = NULL;

    return 0;
}

void simple_command_destroy(SimpleCommand *command)
{
    free(command->argv);
    command->argv = NULL;
    command->argc = 0;
}