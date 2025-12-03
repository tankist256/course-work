#include <stdio.h>
#include <stdlib.h>
#include "../headers/data_structures.h"
#include "../headers/technical_requirements.h"
#include "../headers/special_challenges.h"

static int ensure_category_uuid_capacity(Category* c, int min_cap){
    if(c->product_uuids_capacity >= min_cap) return 1;
    int cap = c->product_uuids_capacity==0?4:c->product_uuids_capacity;
    while(cap < min_cap) cap = cap*2;
    char** np = (char**)malloc(cap * sizeof(char*));
    if(!np) return 0;
    { int i; for(i=0;i<c->product_uuids_count;i++) np[i]=c->product_uuids[i]; }
    if(c->product_uuids) free(c->product_uuids);
    c->product_uuids = np;
    c->product_uuids_capacity = cap;
    return 1;
}

int add_product_uuid_to_category(Inventory* inv, char* category_uuid, char* product_uuid){
    int ci = find_category_index(inv, category_uuid);
    if(ci<0) return 0;
    if(find_product_index(inv, product_uuid)<0) return 0;
    Category* c = &inv->categories[ci];
    int i; for(i=0;i<c->product_uuids_count;i++){ if(str_cmp(c->product_uuids[i], product_uuid)==0) { c->total_products_count++; return 1; } }
    if(!ensure_category_uuid_capacity(c, c->product_uuids_count+1)) return 0;
    char* d = str_dup(product_uuid); if(!d) return 0;
    c->product_uuids[c->product_uuids_count++] = d;
    c->total_products_count++;
    return 1;
}

int remove_product_uuid_from_category(Inventory* inv, char* category_uuid, char* product_uuid){
    int ci = find_category_index(inv, category_uuid);
    if(ci<0) return 0;
    Category* c=&inv->categories[ci];
    int i,found=-1;
    for(i=0;i<c->product_uuids_count;i++){ if(str_cmp(c->product_uuids[i], product_uuid)==0){ found=i; break; } }
    if(found<0){ if(c->total_products_count>0) c->total_products_count--; return 1; }
    if(c->product_uuids[found]){ free(c->product_uuids[found]); }
    for(i=found+1;i<c->product_uuids_count;i++) c->product_uuids[i-1]=c->product_uuids[i];
    c->product_uuids_count--;
    if(c->total_products_count>0) c->total_products_count--;
    if(c->product_uuids_capacity>4 && c->product_uuids_count <= c->product_uuids_capacity/4){
        int ncap = c->product_uuids_capacity/2; if(ncap<4) ncap=4;
        char** np = (char**)malloc(ncap*sizeof(char*)); if(np){ int k; for(k=0;k<c->product_uuids_count;k++) np[k]=c->product_uuids[k]; free(c->product_uuids); c->product_uuids=np; c->product_uuids_capacity=ncap; }
    }
    return 1;
}

static int ensure_product_accessory_capacity(Product* p, int min_cap){
    if(p->accessory_capacity >= min_cap) return 1;
    int cap = p->accessory_capacity==0?4:p->accessory_capacity;
    while(cap<min_cap) cap=cap*2;
    char** np = (char**)malloc(cap*sizeof(char*)); if(!np) return 0;
    { int i; for(i=0;i<p->accessory_count;i++) np[i]=p->accessory_uuids[i]; }
    if(p->accessory_uuids) free(p->accessory_uuids);
    p->accessory_uuids=np; p->accessory_capacity=cap; return 1;
}

int ensure_accessory_relationship(Inventory* inv, char* product_uuid, char* accessory_uuid){
    int pi = find_product_index(inv, product_uuid); if(pi<0) return 0;
    int ai = find_product_index(inv, accessory_uuid); if(ai<0) return 0;
    Product* p=&inv->products[pi];
    int i; for(i=0;i<p->accessory_count;i++){ if(str_cmp(p->accessory_uuids[i], accessory_uuid)==0) return 1; }
    if(!ensure_product_accessory_capacity(p, p->accessory_count+1)) return 0;
    char* d = str_dup(accessory_uuid); if(!d) return 0;
    p->accessory_uuids[p->accessory_count++] = d;
    return 1;
}

int remove_accessory_relationship(Inventory* inv, char* product_uuid, char* accessory_uuid){
    int pi = find_product_index(inv, product_uuid); if(pi<0) return 0;
    Product* p=&inv->products[pi];
    int i,found=-1; for(i=0;i<p->accessory_count;i++){ if(str_cmp(p->accessory_uuids[i], accessory_uuid)==0){ found=i; break; } }
    if(found<0) return 1;
    if(p->accessory_uuids[found]) free(p->accessory_uuids[found]);
    for(i=found+1;i<p->accessory_count;i++) p->accessory_uuids[i-1]=p->accessory_uuids[i];
    p->accessory_count--;
    if(p->accessory_capacity>4 && p->accessory_count <= p->accessory_capacity/4){ int ncap=p->accessory_capacity/2; if(ncap<4) ncap=4; char** np=(char**)malloc(ncap*sizeof(char*)); if(np){ int k; for(k=0;k<p->accessory_count;k++) np[k]=p->accessory_uuids[k]; free(p->accessory_uuids); p->accessory_uuids=np; p->accessory_capacity=ncap; } }
    return 1;
}
