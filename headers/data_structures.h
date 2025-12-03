#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>

#define UUID_STR_LEN 37

typedef struct Date {
    int month;
    int year;
} Date;

typedef struct Manufacturer {
    char* uuid;
    char* name;
    char* country;
    Date established;
    char* website;
    int warranty_months;
} Manufacturer;

typedef struct Category {
    char* uuid;
    char* name;
    char* description;
    int total_products_count;
    char** product_uuids;
    int product_uuids_count;
    int product_uuids_capacity;
} Category;

typedef struct Specs {
    int performance_score;
    int power_watts;
    char* interface_type;
} Specs;

typedef struct Product {
    char* uuid;
    char* model_name;
    char* manufacturer_uuid;
    char* category_uuid;
    char* sku;
    float price;
    int stock_qty;
    Date release_date;
    Specs specs;
    int warranty_months;
    char** accessory_uuids;
    int accessory_count;
    int accessory_capacity;
} Product;

typedef struct Inventory {
    Manufacturer* manufacturers;
    int manufacturers_count;
    int manufacturers_capacity;

    Category* categories;
    int categories_count;
    int categories_capacity;

    Product* products;
    int products_count;
    int products_capacity;
} Inventory;

void inventory_init(Inventory* inv);
void inventory_free(Inventory* inv);

int find_manufacturer_index(Inventory* inv, char* uuid);
int find_category_index(Inventory* inv, char* uuid);
int find_product_index(Inventory* inv, char* uuid);

int inventory_add_manufacturer(
    Inventory* inv,
    char* name,
    char* country,
    int month,
    int year,
    char* website,
    int warranty_months,
    char out_uuid[UUID_STR_LEN]
);

int inventory_add_category(
    Inventory* inv,
    char* name,
    char* description,
    char out_uuid[UUID_STR_LEN]
);

int inventory_add_product(
    Inventory* inv,
    char* model_name,
    char* manufacturer_uuid,
    char* category_uuid,
    char* sku,
    float price,
    int stock_qty,
    int release_month,
    int release_year,
    int performance_score,
    int power_watts,
    char* interface_type,
    int warranty_months,
    char out_uuid[UUID_STR_LEN]
);

int inventory_delete_product(Inventory* inv, char* uuid);
int inventory_delete_manufacturer(Inventory* inv, char* uuid);
int inventory_delete_category(Inventory* inv, char* uuid);

int inventory_update_product_stock(Inventory* inv, char* uuid, int stock_qty);
int inventory_update_product_price(Inventory* inv, char* uuid, float price);
int inventory_update_manufacturer(Inventory* inv, char* uuid, char* name, char* country, int month, int year, char* website, int warranty_months);

int inventory_add_accessory(Inventory* inv, char* product_uuid, char* accessory_uuid);
int inventory_remove_accessory(Inventory* inv, char* product_uuid, char* accessory_uuid);

int inventory_add_manufacturer_with_uuid(
    Inventory* inv,
    char* uuid,
    char* name,
    char* country,
    int month,
    int year,
    char* website,
    int warranty_months
);

int inventory_add_category_with_uuid(
    Inventory* inv,
    char* uuid,
    char* name,
    char* description,
    int product_uuid_count,
    char** product_uuid_list
);

int inventory_add_product_with_uuid(
    Inventory* inv,
    char* uuid,
    char* model_name,
    char* manufacturer_uuid,
    char* category_uuid,
    char* sku,
    float price,
    int stock_qty,
    int release_month,
    int release_year,
    int performance_score,
    int power_watts,
    char* interface_type,
    int warranty_months,
    int accessory_count,
    char** accessory_uuid_list
);

void inventory_list_products(Inventory* inv);
void inventory_list_manufacturers(Inventory* inv);
void inventory_list_categories(Inventory* inv);
void inventory_list_below_stock(Inventory* inv, int threshold);
void inventory_list_accessories(Inventory* inv, char* product_uuid);

#endif
