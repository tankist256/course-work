#ifndef TECHNICAL_REQUIREMENTS_H
#define TECHNICAL_REQUIREMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

int str_len(char* s);
int str_cmp(char* a, char* b);
int str_icmp(char* a, char* b);
char* str_dup(char* s);
int str_contains(char* haystack, char* needle);
int str_icontains(char* haystack, char* needle);

int parse_int_str(char* s, int* out);
int parse_float_str(char* s, float* out);

int uuid_validate(char* s);
void uuid_generate(char out[UUID_STR_LEN]);

char* escape_field(char* s);
char* unescape_field(char* s);

int save_all(Inventory* inv, char* dir);
int load_all(Inventory* inv, char* dir);

void sort_products_by_price(Product* arr, int count, int ascending);
void sort_products_by_score(Product* arr, int count, int ascending);
void sort_products_by_power(Product* arr, int count, int ascending);
void sort_products_by_stock(Product* arr, int count, int ascending);
void sort_products_by_model(Product* arr, int count, int ascending);

Product* filter_products_by_category(Inventory* inv, char* category_uuid, int* out_count);
Product* filter_products_by_manufacturer(Inventory* inv, char* manufacturer_uuid, int* out_count);
Product* filter_products_by_price_range(Inventory* inv, float min_price, float max_price, int* out_count);
Product* filter_products_by_score_range(Inventory* inv, int min_score, int max_score, int* out_count);
Product* filter_products_by_max_power(Inventory* inv, int max_power, int* out_count);
Product* filter_products_by_interface(Inventory* inv, char* interface_type, int* out_count);
void free_product_array(Product* arr, int count);

#endif
