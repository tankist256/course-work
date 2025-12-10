#include <stdio.h>
#include <stdlib.h>
#include "../headers/data_structures.h"
#include "../headers/technical_requirements.h"
#include "../headers/special_challenges.h"

static int ensure_manufacturers_capacity(Inventory* inv, int min_cap) {
    if (inv->manufacturers_capacity >= min_cap) return 1;
    int new_cap = inv->manufacturers_capacity == 0 ? 4 : inv->manufacturers_capacity;
    while (new_cap < min_cap) new_cap = new_cap * 2;
    Manufacturer* np = (Manufacturer*)malloc(new_cap * sizeof(Manufacturer));
    if (!np) return 0;
    { int i; for(i=0;i<inv->manufacturers_count;i++) np[i]=inv->manufacturers[i]; }
    if (inv->manufacturers) free(inv->manufacturers);
    inv->manufacturers = np;
    inv->manufacturers_capacity = new_cap;
    return 1;
}

static int ensure_categories_capacity(Inventory* inv, int min_cap) {
    if (inv->categories_capacity >= min_cap) return 1;
    int new_cap = inv->categories_capacity == 0 ? 4 : inv->categories_capacity;
    while (new_cap < min_cap) new_cap = new_cap * 2;
    Category* np = (Category*)malloc(new_cap * sizeof(Category));
    if (!np) return 0;
    { int i; for(i=0;i<inv->categories_count;i++) np[i]=inv->categories[i]; }
    if (inv->categories) free(inv->categories);
    inv->categories = np;
    inv->categories_capacity = new_cap;
    return 1;
}

static int ensure_products_capacity(Inventory* inv, int min_cap) {
    if (inv->products_capacity >= min_cap) return 1;
    int new_cap = inv->products_capacity == 0 ? 4 : inv->products_capacity;
    while (new_cap < min_cap) new_cap = new_cap * 2;
    Product* np = (Product*)malloc(new_cap * sizeof(Product));
    if (!np) return 0;
    { int i; for(i=0;i<inv->products_count;i++) np[i]=inv->products[i]; }
    if (inv->products) free(inv->products);
    inv->products = np;
    inv->products_capacity = new_cap;
    return 1;
}

void inventory_init(Inventory* inv) {
    inv->manufacturers = NULL;
    inv->manufacturers_count = 0;
    inv->manufacturers_capacity = 0;
    inv->categories = NULL;
    inv->categories_count = 0;
    inv->categories_capacity = 0;
    inv->products = NULL;
    inv->products_count = 0;
    inv->products_capacity = 0;
}

static void free_manufacturer(Manufacturer* m) {
    if (m->uuid) free(m->uuid);
    if (m->name) free(m->name);
    if (m->country) free(m->country);
    if (m->website) free(m->website);
    m->uuid = NULL;
    m->name = NULL;
    m->country = NULL;
    m->website = NULL;
}

static void free_category(Category* c) {
    int i;
    if (c->uuid) free(c->uuid);
    if (c->name) free(c->name);
    if (c->description) free(c->description);
    for (i = 0; i < c->product_uuids_count; ++i) {
        if (c->product_uuids && c->product_uuids[i]) free(c->product_uuids[i]);
    }
    if (c->product_uuids) free(c->product_uuids);
    c->uuid = NULL;
    c->name = NULL;
    c->description = NULL;
    c->product_uuids = NULL;
    c->product_uuids_count = 0;
    c->product_uuids_capacity = 0;
    c->total_products_count = 0;
}

static void free_product(Product* p) {
    int i;
    if (p->uuid) free(p->uuid);
    if (p->model_name) free(p->model_name);
    if (p->manufacturer_uuid) free(p->manufacturer_uuid);
    if (p->category_uuid) free(p->category_uuid);
    if (p->sku) free(p->sku);
    if (p->specs.interface_type) free(p->specs.interface_type);
    for (i = 0; i < p->accessory_count; ++i) {
        if (p->accessory_uuids && p->accessory_uuids[i]) free(p->accessory_uuids[i]);
    }
    if (p->accessory_uuids) free(p->accessory_uuids);
    p->uuid = NULL;
    p->model_name = NULL;
    p->manufacturer_uuid = NULL;
    p->category_uuid = NULL;
    p->sku = NULL;
    p->specs.interface_type = NULL;
    p->accessory_uuids = NULL;
    p->accessory_count = 0;
    p->accessory_capacity = 0;
}

void inventory_free(Inventory* inv) {
    int i;
    for (i = 0; i < inv->manufacturers_count; ++i) free_manufacturer(&inv->manufacturers[i]);
    if (inv->manufacturers) free(inv->manufacturers);
    inv->manufacturers = NULL;
    inv->manufacturers_count = 0;
    inv->manufacturers_capacity = 0;

    for (i = 0; i < inv->categories_count; ++i) free_category(&inv->categories[i]);
    if (inv->categories) free(inv->categories);
    inv->categories = NULL;
    inv->categories_count = 0;
    inv->categories_capacity = 0;

    for (i = 0; i < inv->products_count; ++i) free_product(&inv->products[i]);
    if (inv->products) free(inv->products);
    inv->products = NULL;
    inv->products_count = 0;
    inv->products_capacity = 0;
}

int find_manufacturer_index(Inventory* inv, char* uuid) {
    int i;
    for (i = 0; i < inv->manufacturers_count; ++i) {
        if (inv->manufacturers[i].uuid && uuid && str_cmp(inv->manufacturers[i].uuid, uuid) == 0) return i;
    }
    return -1;
}

int find_category_index(Inventory* inv, char* uuid) {
    int i;
    for (i = 0; i < inv->categories_count; ++i) {
        if (inv->categories[i].uuid && uuid && str_cmp(inv->categories[i].uuid, uuid) == 0) return i;
    }
    return -1;
}

int find_product_index(Inventory* inv, char* uuid) {
    int i;
    for (i = 0; i < inv->products_count; ++i) {
        if (inv->products[i].uuid && uuid && str_cmp(inv->products[i].uuid, uuid) == 0) return i;
    }
    return -1;
}

static char* dup_uuid_buf(char* s){ if(!s) return NULL; return str_dup(s); }

static int sku_exists(Inventory* inv, char* sku){
    int i; for(i=0;i<inv->products_count;i++){ if(inv->products[i].sku && sku && str_cmp(inv->products[i].sku, sku)==0) return 1; } return 0;
}

int inventory_add_manufacturer(
    Inventory* inv,
    char* name,
    char* country,
    int month,
    int year,
    char* website,
    int warranty_months,
    char out_uuid[UUID_STR_LEN]
){
    char tmp[UUID_STR_LEN]; uuid_generate(tmp);
    while(find_product_index(inv, tmp) >= 0) uuid_generate(tmp);
    while(find_manufacturer_index(inv, tmp) >= 0) uuid_generate(tmp);
    if(!ensure_manufacturers_capacity(inv, inv->manufacturers_count+1)) return 0;
    Manufacturer m; m.uuid=NULL; m.name=NULL; m.country=NULL; m.website=NULL; m.warranty_months=warranty_months; m.established.month=month; m.established.year=year;
    m.uuid = dup_uuid_buf(tmp);
    m.name = str_dup(name);
    m.country = str_dup(country);
    m.website = str_dup(website);
    if(!m.uuid || !m.name || !m.country || !m.website){ free_manufacturer(&m); return 0; }
    inv->manufacturers[inv->manufacturers_count++] = m;
    if(out_uuid){ int i; for(i=0;i<UUID_STR_LEN;i++){ out_uuid[i] = i<36? tmp[i] : '\0'; } }
    return 1;
}

int inventory_add_category(
    Inventory* inv,
    char* name,
    char* description,
    char out_uuid[UUID_STR_LEN]
){
    char tmp[UUID_STR_LEN]; uuid_generate(tmp);
    while(find_category_index(inv, tmp) >= 0) uuid_generate(tmp);
    if(!ensure_categories_capacity(inv, inv->categories_count+1)) return 0;
    Category c; c.uuid=NULL; c.name=NULL; c.description=NULL; c.total_products_count=0; c.product_uuids=NULL; c.product_uuids_count=0; c.product_uuids_capacity=0;
    c.uuid = dup_uuid_buf(tmp);
    c.name = str_dup(name);
    c.description = str_dup(description);
    if(!c.uuid || !c.name || !c.description){ free_category(&c); return 0; }
    inv->categories[inv->categories_count++] = c;
    if(out_uuid){ int i; for(i=0;i<UUID_STR_LEN;i++){ out_uuid[i] = i<36? tmp[i] : '\0'; } }
    return 1;
}

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
){
    if(find_manufacturer_index(inv, manufacturer_uuid) < 0) return 0;
    if(find_category_index(inv, category_uuid) < 0) return 0;
    if(sku_exists(inv, sku)) return 0;
    if(!ensure_products_capacity(inv, inv->products_count+1)) return 0;

    char tmp[UUID_STR_LEN]; uuid_generate(tmp);

    Product p; p.uuid=NULL; p.model_name=NULL; p.manufacturer_uuid=NULL; p.category_uuid=NULL; p.sku=NULL; p.specs.interface_type=NULL; p.accessory_uuids=NULL; p.accessory_count=0; p.accessory_capacity=0;
    p.uuid = dup_uuid_buf(tmp);
    p.model_name = str_dup(model_name);
    p.manufacturer_uuid = str_dup(manufacturer_uuid);
    p.category_uuid = str_dup(category_uuid);
    p.sku = str_dup(sku);
    p.price = price;
    p.stock_qty = stock_qty;
    p.release_date.month = release_month;
    p.release_date.year = release_year;
    p.specs.performance_score = performance_score;
    p.specs.power_watts = power_watts;
    p.specs.interface_type = str_dup(interface_type);
    p.warranty_months = warranty_months;
    if(!p.uuid || !p.model_name || !p.manufacturer_uuid || !p.category_uuid || !p.sku || !p.specs.interface_type){ free_product(&p); return 0; }

    inv->products[inv->products_count++] = p;

    if(add_product_uuid_to_category(inv, category_uuid, tmp)==0){
        int idx = find_product_index(inv, tmp);
        if(idx>=0){ free_product(&inv->products[idx]);
            int i; for(i=idx+1;i<inv->products_count;i++) inv->products[i-1]=inv->products[i];
            inv->products_count--; }
        return 0;
    }

    if(out_uuid){ int i; for(i=0;i<UUID_STR_LEN;i++){ out_uuid[i] = i<36? tmp[i] : '\0'; } }
    return 1;
}

int inventory_delete_product(Inventory* inv, char* uuid){
    int idx = find_product_index(inv, uuid);
    if(idx<0) return 0;
    Product* p = &inv->products[idx];
    if(p->category_uuid) remove_product_uuid_from_category(inv, p->category_uuid, uuid);
    free_product(p);
    {
        int i; for(i=idx+1;i<inv->products_count;i++) inv->products[i-1]=inv->products[i];
        inv->products_count--;
    }
    return 1;
}

int inventory_delete_manufacturer(Inventory* inv, char* uuid){
    int i;
    for(i=0;i<inv->products_count;i++){
        if(inv->products[i].manufacturer_uuid && str_cmp(inv->products[i].manufacturer_uuid, uuid)==0){
            return 0;
        }
    }
    i = find_manufacturer_index(inv, uuid);
    if(i<0) return 0;
    free_manufacturer(&inv->manufacturers[i]);
    for(; i+1<inv->manufacturers_count; i++) inv->manufacturers[i]=inv->manufacturers[i+1];
    inv->manufacturers_count--;
    return 1;
}

int inventory_delete_category(Inventory* inv, char* uuid){
    int i;
    for(i=0;i<inv->products_count;i++){
        if(inv->products[i].category_uuid && str_cmp(inv->products[i].category_uuid, uuid)==0){
            return 0;
        }
    }
    i = find_category_index(inv, uuid);
    if(i<0) return 0;
    free_category(&inv->categories[i]);
    for(; i+1<inv->categories_count; i++) inv->categories[i]=inv->categories[i+1];
    inv->categories_count--;
    return 1;
}

int inventory_update_product_stock(Inventory* inv, char* uuid, int stock_qty){
    int i = find_product_index(inv, uuid); if(i<0) return 0; inv->products[i].stock_qty = stock_qty; return 1;
}

int inventory_update_product_price(Inventory* inv, char* uuid, float price){
    int i = find_product_index(inv, uuid); if(i<0) return 0; inv->products[i].price = price; return 1;
}

int inventory_update_manufacturer(Inventory* inv, char* uuid, char* name, char* country, int month, int year, char* website, int warranty_months){
    int i = find_manufacturer_index(inv, uuid); if(i<0) return 0;
    Manufacturer* m = &inv->manufacturers[i];
    char* n = NULL; char* c = NULL; char* w = NULL;
    if(name){ n = str_dup(name); if(!n) return 0; }
    if(country){ c = str_dup(country); if(!c){ if(n) free(n); return 0; } }
    if(website){ w = str_dup(website); if(!w){ if(n) free(n); if(c) free(c); return 0; } }
    if(name){ if(m->name) free(m->name); m->name = n; }
    if(country){ if(m->country) free(m->country); m->country = c; }
    if(website){ if(m->website) free(m->website); m->website = w; }
    if(month>0) m->established.month = month;
    if(year>0) m->established.year = year;
    if(warranty_months>0) m->warranty_months = warranty_months;
    return 1;
}

int inventory_add_accessory(Inventory* inv, char* product_uuid, char* accessory_uuid){
    return ensure_accessory_relationship(inv, product_uuid, accessory_uuid);
}

int inventory_remove_accessory(Inventory* inv, char* product_uuid, char* accessory_uuid){
    return remove_accessory_relationship(inv, product_uuid, accessory_uuid);
}

static int uuid_duplicate_exists_manufacturer(Inventory* inv, char* uuid){ int i; for(i=0;i<inv->manufacturers_count;i++){ if(inv->manufacturers[i].uuid && str_cmp(inv->manufacturers[i].uuid, uuid)==0) return 1; } return 0; }
static int uuid_duplicate_exists_category(Inventory* inv, char* uuid){ int i; for(i=0;i<inv->categories_count;i++){ if(inv->categories[i].uuid && str_cmp(inv->categories[i].uuid, uuid)==0) return 1; } return 0; }
static int uuid_duplicate_exists_product(Inventory* inv, char* uuid){ int i; for(i=0;i<inv->products_count;i++){ if(inv->products[i].uuid && str_cmp(inv->products[i].uuid, uuid)==0) return 1; } return 0; }

int inventory_add_manufacturer_with_uuid(
    Inventory* inv,
    char* uuid,
    char* name,
    char* country,
    int month,
    int year,
    char* website,
    int warranty_months
){
    if(!uuid_validate(uuid)) return 0;
    if(uuid_duplicate_exists_manufacturer(inv, uuid)) return 0;
    if(!ensure_manufacturers_capacity(inv, inv->manufacturers_count+1)) return 0;
    Manufacturer m; m.uuid=NULL; m.name=NULL; m.country=NULL; m.website=NULL; m.warranty_months=warranty_months; m.established.month=month; m.established.year=year;
    m.uuid = str_dup(uuid);
    m.name = str_dup(name);
    m.country = str_dup(country);
    m.website = str_dup(website);
    if(!m.uuid || !m.name || !m.country || !m.website){ free_manufacturer(&m); return 0; }
    inv->manufacturers[inv->manufacturers_count++] = m;
    return 1;
}

int inventory_add_category_with_uuid(
    Inventory* inv,
    char* uuid,
    char* name,
    char* description,
    int product_uuid_count,
    char** product_uuid_list
){
    if(!uuid_validate(uuid)) return 0;
    if(uuid_duplicate_exists_category(inv, uuid)) return 0;
    if(!ensure_categories_capacity(inv, inv->categories_count+1)) return 0;
    Category c; c.uuid=NULL; c.name=NULL; c.description=NULL; c.total_products_count=0; c.product_uuids=NULL; c.product_uuids_count=0; c.product_uuids_capacity=0;
    c.uuid = str_dup(uuid);
    c.name = str_dup(name);
    c.description = str_dup(description);
    if(!c.uuid || !c.name || !c.description){ free_category(&c); return 0; }
    if(product_uuid_count>0){
        int cap = product_uuid_count<4?4:product_uuid_count;
        c.product_uuids = (char**)malloc(cap * sizeof(char*));
        if(!c.product_uuids){ free_category(&c); return 0; }
        c.product_uuids_capacity = cap; c.product_uuids_count=0;
        int i; for(i=0;i<product_uuid_count;i++){
            char* d = str_dup(product_uuid_list[i]); if(!d){ free_category(&c); return 0; }
            c.product_uuids[c.product_uuids_count++] = d;
        }
    }
    inv->categories[inv->categories_count++] = c;
    return 1;
}

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
){
    if(!uuid_validate(uuid)) return 0;
    if(uuid_duplicate_exists_product(inv, uuid)) return 0;
    if(find_manufacturer_index(inv, manufacturer_uuid) < 0) return 0;
    if(find_category_index(inv, category_uuid) < 0) return 0;
    if(sku_exists(inv, sku)) return 0;
    if(!ensure_products_capacity(inv, inv->products_count+1)) return 0;

    Product p; p.uuid=NULL; p.model_name=NULL; p.manufacturer_uuid=NULL; p.category_uuid=NULL; p.sku=NULL; p.specs.interface_type=NULL; p.accessory_uuids=NULL; p.accessory_count=0; p.accessory_capacity=0;
    p.uuid = str_dup(uuid);
    p.model_name = str_dup(model_name);
    p.manufacturer_uuid = str_dup(manufacturer_uuid);
    p.category_uuid = str_dup(category_uuid);
    p.sku = str_dup(sku);
    p.price = price;
    p.stock_qty = stock_qty;
    p.release_date.month = release_month;
    p.release_date.year = release_year;
    p.specs.performance_score = performance_score;
    p.specs.power_watts = power_watts;
    p.specs.interface_type = str_dup(interface_type);
    p.warranty_months = warranty_months;
    if(!p.uuid || !p.model_name || !p.manufacturer_uuid || !p.category_uuid || !p.sku || !p.specs.interface_type){ free_product(&p); return 0; }
    if(accessory_count>0){ int cap = accessory_count<4?4:accessory_count; p.accessory_uuids=(char**)malloc(cap*sizeof(char*)); if(!p.accessory_uuids){ free_product(&p); return 0; } p.accessory_capacity=cap; p.accessory_count=0; int i; for(i=0;i<accessory_count;i++){ char* d=str_dup(accessory_uuid_list[i]); if(!d){ free_product(&p); return 0; } p.accessory_uuids[p.accessory_count++]=d; } }
    inv->products[inv->products_count++] = p;
    return 1;
}

void inventory_list_products(Inventory* inv){
    int i,j; for(i=0;i<inv->products_count;i++){
        Product* p=&inv->products[i];
        printf("%s | %s | man:%s | cat:%s | sku:%s | $%.2f | stock:%d | rel:%02d/%04d | score:%d | watts:%d | iface:%s | warr:%d | accessories:%d\n",
            p->uuid?p->uuid:"", p->model_name?p->model_name:"", p->manufacturer_uuid?p->manufacturer_uuid:"", p->category_uuid?p->category_uuid:"", p->sku?p->sku:"", p->price, p->stock_qty,
            p->release_date.month, p->release_date.year, p->specs.performance_score, p->specs.power_watts, p->specs.interface_type?p->specs.interface_type:"", p->warranty_months, p->accessory_count);
        if(p->accessory_count>0){ printf("  accessories:"); for(j=0;j<p->accessory_count;j++){ printf(" %s", p->accessory_uuids[j]?p->accessory_uuids[j]:"" ); } printf("\n"); }
    }
}

void inventory_list_manufacturers(Inventory* inv){
    int i; for(i=0;i<inv->manufacturers_count;i++){
        Manufacturer* m=&inv->manufacturers[i];
        printf("%s | %s | %s | est:%02d/%04d | %s | warr:%d\n", m->uuid?m->uuid:"", m->name?m->name:"", m->country?m->country:"", m->established.month, m->established.year, m->website?m->website:"", m->warranty_months);
    }
}

void inventory_list_categories(Inventory* inv){
    int i; for(i=0;i<inv->categories_count;i++){
        Category* c=&inv->categories[i];
        printf("%s | %s | %s | total:%d | listed:%d\n", c->uuid?c->uuid:"", c->name?c->name:"", c->description?c->description:"", c->total_products_count, c->product_uuids_count);
    }
}

void inventory_list_below_stock(Inventory* inv, int threshold){
    int i; for(i=0;i<inv->products_count;i++){ if(inv->products[i].stock_qty < threshold){ Product* p=&inv->products[i]; printf("LOW STOCK: %s | %s | stock:%d\n", p->uuid?p->uuid:"", p->model_name?p->model_name:"", p->stock_qty); } }
}

void inventory_list_accessories(Inventory* inv, char* product_uuid){
    int i=find_product_index(inv, product_uuid); if(i<0){ printf("Product not found\n"); return; }
    Product* p=&inv->products[i]; int j; printf("Accessories for %s (%s):", p->uuid?p->uuid:"", p->model_name?p->model_name:""); for(j=0;j<p->accessory_count;j++){ printf(" %s", p->accessory_uuids[j]?p->accessory_uuids[j]:"" ); } printf("\n");
}
