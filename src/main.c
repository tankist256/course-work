#include <stdio.h>
#include <stdlib.h>
#include "../headers/data_structures.h"
#include "../headers/technical_requirements.h"
#include "../headers/cli.h"

int main(int argc, char** argv) {
    Inventory inv;
    inventory_init(&inv);
    srand(123456);
    char* db_dir = "db";
    load_all(&inv, db_dir);
    if (argc <= 1) {
        cli_print_usage();
        inventory_free(&inv);
        return 0;
    }
    int rc = cli_dispatch(&inv, argc, argv, db_dir);
    inventory_free(&inv);
    return rc;
}
