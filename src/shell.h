#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define DEFAULT_SHELL "/bin/bash"

//todo: cmd timeout
//      capture debug output (to file? observe mode)

static char* shell = NULL;

void shell_init(void);
void shell_exec_cmd(char* cmd);
