#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

int cli_dispatch(Inventory* inv, int argc, char** argv, char* db_dir);
void cli_print_help(void);
void cli_print_usage(void);

#endif
