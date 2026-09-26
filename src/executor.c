#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "executor.h"
int execute_simple_command(const SimpleCommand *command)
{
    if (command->argc == 0) {
        return 0;
    }

    pid_t p = fork();

    if (p < 0) {
        return -1;
    }

    if (p == 0) {
        execvp(command->argv[0], command->argv);

        /* execvp only returns on failure */
        _exit(127);
    }

    int status;

    if (waitpid(p, &status, 0) == -1) {
        return -1;
    }

    return 0;
}