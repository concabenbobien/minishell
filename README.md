# Minish
## Overview
This is a small Unix-style shell written in C as a learning project.

## Goals
The project aims to implement a documented subset of Unix shell syntax while exploring process creation, program execution, parsing, file descriptors, pipelines, signals, and terminal job control.

The codebase is intended to remain modular and extensible as new shell features are introduced.

## v0.1 Scope
This preliminary version executes simple prompts and simple functions:
- External commands with arguments
- Normalize single and double quote words
- pw, exit, cd
- input redirection <
- output redirection >
- append redirection >>
- clear syntax/runtime errors
- lexer and parser tests
## Non-Goals
- full POSIX/Bash compatibility
- environment-variable expansion
- globbing
- command substitution
- background jobs
- job control
- && / || / ;
- scripting
## Architecture
source line
    ↓
lexer
    ↓
token stream
    ↓
parser
    ↓
AST / command representation
    ↓
executor
    ↓
POSIX process and file-descriptor APIs

v0.1 uses a lexer with quote-flag-machine word scanning and prefix-grouped longest-match algorithm for operator handling. A trie-based operator matcher is planned as a later version as the grammar grows.

## Build and Run
To be added once the initial executable and build system are implemented.
## Testing
To be added once the lexer and parser test harness is implemented.
## Roadmap
v0.1 — simple commands, quoting, builtins, redirection
v0.2 — pipelines and higher-level expression parsing
v0.3 — background jobs and signals
v1.0 — process groups and terminal job control