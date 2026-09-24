#ifndef COMMANDS_H
#define COMMANDS_H

#include "parser.h"

int is_exit(struct cmd *cmds, int numCmds);

void run_pipeline(struct cmd *cmds, int numt);

#endif