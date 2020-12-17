#include "shell.h"

void shell_init(void) {
    char* env_shell = getenv("SHELL");    
    shell = env_shell ? env_shell : DEFAULT_SHELL;
}

void shell_exec_cmd(char* cmd) {
    if(!shell) {
        fprintf(stderr, "ERR: uninitialized shell !\n");
        return;
    }

    pid_t cproc = fork();
    if(cproc == 0) {
        setsid();
        char* exec[] = { shell, "-c", cmd, NULL };

        int status = execvp(exec[0], exec);
        exit(status);
    } else {
        fprintf(stderr, "executing \"%s\" on child process (PID: %d)\n", cmd, cproc);
    }
}
