#ifndef SPECIAL_CHALLENGES_H
#define SPECIAL_CHALLENGES_H

#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

int add_product_uuid_to_category(Inventory* inv, char* category_uuid, char* product_uuid);
int remove_product_uuid_from_category(Inventory* inv, char* category_uuid, char* product_uuid);
int ensure_accessory_relationship(Inventory* inv, char* product_uuid, char* accessory_uuid);
int remove_accessory_relationship(Inventory* inv, char* product_uuid, char* accessory_uuid);

#endif
