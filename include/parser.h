#ifndef MINISH_PARSER_H
#define MINISH_PARSER_H

#include <stddef.h>
#include "token.h"

typedef struct {
    char **argv;
    size_t argc;
} SimpleCommand;

int parse_simple_command(
    const TokenStream *tokens,
    SimpleCommand *command
);

void simple_command_destroy(SimpleCommand *command);

#endif