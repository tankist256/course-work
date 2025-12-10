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
    char* env_db = getenv("INVENTORY_DB_DIR");
    if (env_db && env_db[0] != '\0') {
        db_dir = env_db;
    }

    int new_argc = 1;
    char** new_argv = (char**)malloc(sizeof(char*) * (argc > 0 ? argc : 1));
    int db_missing_arg = 0;
    if (!new_argv) {
        new_argv = argv;
        new_argc = argc;
    } else {
        new_argv[0] = argv[0];
        int i = 1;
        while (i < argc) {
            if (str_cmp(argv[i], "--db") == 0) {
                if (i + 1 < argc) {
                    db_dir = argv[i + 1];
                    i += 2;
                    continue;
                } else {
                    db_missing_arg = 1;
                    i += 1;
                    continue;
                }
            }
            new_argv[new_argc++] = argv[i++];
        }
    }

    if (db_missing_arg) {
        fprintf(stderr, "Missing path after --db.\n");
        cli_print_usage();
        inventory_free(&inv);
        if (new_argv != argv) free(new_argv);
        return 1;
    }

    load_all(&inv, db_dir);

    if (new_argc <= 1) {
        cli_print_usage();
        inventory_free(&inv);
        if (new_argv != argv) free(new_argv);
        return 0;
    }
    int rc = cli_dispatch(&inv, new_argc, new_argv, db_dir);
    if (inv.manufacturers_count == 0 && inv.categories_count == 0 && inv.products_count == 0) {
        fprintf(stderr, "Warning: no data loaded from '%s'. Use --db <dir> or set INVENTORY_DB_DIR.\n", db_dir);
    }
    inventory_free(&inv);
    if (new_argv != argv) free(new_argv);
    return rc;
}

