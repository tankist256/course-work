#include <stdio.h>
#include <stdlib.h>
#include "../headers/data_structures.h"
#include "../headers/technical_requirements.h"
#include "../headers/cli.h"

static char* next_val(int argc, char** argv, int i){
    if(i+1<argc){
        return argv[i+1];
    }
    return NULL;
}

void cli_print_usage(void){
    printf("Usage: inventory <command> [options]\n");
    printf("Try 'inventory help' for full help.\n");
}

void cli_print_help(void){
    printf("Commands:\n");
    printf("  help\n");
    printf("  add-manufacturer --name N --country C --est-month M --est-year Y --website W --warranty MM\n");
    printf("  add-category --name N --desc D\n");
    printf("  add-product --model M --man MAN_UUID --cat CAT_UUID --sku S --price P --stock Q --rel-month M --rel-year Y --score S --power W --iface I --warranty MM\n");
    printf("  del-product --uuid U\n");
    printf("  del-manufacturer --uuid U\n");
    printf("  del-category --uuid U\n");
    printf("  upd-stock --uuid U --stock Q\n");
    printf("  upd-price --uuid U --price P\n");
    printf("  upd-manufacturer --uuid U --name N --country C --est-month M --est-year Y --website W --warranty MM\n");
    printf("  add-accessory --uuid U --acc A\n");
    printf("  rm-accessory --uuid U --acc A\n");
    printf("  list-products\n");
    printf("  list-manufacturers\n");
    printf("  list-categories\n");
    printf("  list-below --threshold T\n");
    printf("  list-accessories --uuid U\n");
    printf("  list-products-in-category --uuid U\n");
    printf("  search-model --substr S\n");
    printf("  sort-products --by price|score|power|stock|model [--desc]\n");
    printf("  query [--cat U] [--man U] [--min-price P] [--max-price P] [--min-score S] [--max-score S] [--max-power W] [--iface I] [--sort F] [--desc]\n");
}

static int save(Inventory* inv, char* db_dir){
    if(!save_all(inv, db_dir)){
        fprintf(stderr, "Save failed.\n");
        return 0;
    }
    return 1;
}

static void print_product_line(Product* p){
    printf("%s | %s | man:%s | cat:%s | sku:%s | $%.2f | stock:%d | rel:%02d/%04d | score:%d | watts:%d | iface:%s | warr:%d | accessories:%d\n",
        p->uuid?p->uuid:"", p->model_name?p->model_name:"", p->manufacturer_uuid?p->manufacturer_uuid:"", p->category_uuid?p->category_uuid:"", p->sku?p->sku:"", p->price, p->stock_qty,
        p->release_date.month, p->release_date.year, p->specs.performance_score, p->specs.power_watts, p->specs.interface_type?p->specs.interface_type:"", p->warranty_months, p->accessory_count);
}

int cli_dispatch(Inventory* inv, int argc, char** argv, char* db_dir){
    if(argc<=1){
        cli_print_usage();
        return 0;
    }
    char* cmd = argv[1];

    if(str_cmp(cmd, "help") == 0 || str_cmp(cmd, "--help")==0){
        cli_print_help();
        return 0;
    }

    if(str_cmp(cmd, "add-manufacturer")==0){
        char *name=NULL,*country=NULL,*website=NULL; int month=0,year=0,warr=0; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i], "--name")==0) name=next_val(argc,argv,i++);
            else if(str_cmp(argv[i], "--country")==0) country=next_val(argc,argv,i++);
            else if(str_cmp(argv[i], "--est-month")==0){ char* v=next_val(argc,argv,i++); if(!parse_int_str(v,&month)) month=0; }
            else if(str_cmp(argv[i], "--est-year")==0){ char* v=next_val(argc,argv,i++); if(!parse_int_str(v,&year)) year=0; }
            else if(str_cmp(argv[i], "--website")==0) website=next_val(argc,argv,i++);
            else if(str_cmp(argv[i], "--warranty")==0){ char* v=next_val(argc,argv,i++); if(!parse_int_str(v,&warr)) warr=0; }
        }
        char uuid[UUID_STR_LEN];
        if(!inventory_add_manufacturer(inv,name,country,month,year,website,warr,uuid)){
            fprintf(stderr,"Failed to add manufacturer.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        printf("%s\n", uuid);
        return 0;
    }

    if(str_cmp(cmd, "add-category")==0){
        char *name=NULL,*desc=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--name")==0) name=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--desc")==0) desc=next_val(argc,argv,i++);
        }
        char uuid[UUID_STR_LEN];
        if(!inventory_add_category(inv,name,desc,uuid)){
            fprintf(stderr,"Failed to add category.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        printf("%s\n", uuid);
        return 0;
    }

    if(str_cmp(cmd, "add-product")==0){
        char *model=NULL,*man=NULL,*cat=NULL,*sku=NULL,*iface=NULL; float price=0.0f; int stock=0,rm=0,ry=0,score=0,power=0,warr=0; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--model")==0) model=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--man")==0) man=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--cat")==0) cat=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--sku")==0) sku=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--price")==0){ char* v=next_val(argc,argv,i++); parse_float_str(v,&price); }
            else if(str_cmp(argv[i],"--stock")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&stock); }
            else if(str_cmp(argv[i],"--rel-month")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&rm); }
            else if(str_cmp(argv[i],"--rel-year")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&ry); }
            else if(str_cmp(argv[i],"--score")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&score); }
            else if(str_cmp(argv[i],"--power")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&power); }
            else if(str_cmp(argv[i],"--iface")==0) iface=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--warranty")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&warr); }
        }
        char uuid[UUID_STR_LEN];
        if(!inventory_add_product(inv,model,man,cat,sku,price,stock,rm,ry,score,power,iface,warr,uuid)){
            fprintf(stderr,"Failed to add product.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        printf("%s\n", uuid);
        return 0;
    }

    if(str_cmp(cmd, "del-product")==0){
        char* uuid=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) uuid=next_val(argc,argv,i++);
        }
        if(!inventory_delete_product(inv, uuid)){
            fprintf(stderr,"Delete failed.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        return 0;
    }

    if(str_cmp(cmd, "del-manufacturer")==0){
        char* uuid=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) uuid=next_val(argc,argv,i++);
        }
        if(!inventory_delete_manufacturer(inv, uuid)){
            fprintf(stderr,"Delete failed (maybe has products).\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        return 0;
    }

    if(str_cmp(cmd, "del-category")==0){
        char* uuid=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) uuid=next_val(argc,argv,i++);
        }
        if(!inventory_delete_category(inv, uuid)){
            fprintf(stderr,"Delete failed (maybe has products).\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        return 0;
    }

    if(str_cmp(cmd, "upd-stock")==0){
        char* uuid=NULL; int stock=0; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) uuid=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--stock")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&stock); }
        }
        if(!inventory_update_product_stock(inv, uuid, stock)){
            fprintf(stderr,"Update failed.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        return 0;
    }

    if(str_cmp(cmd, "upd-price")==0){
        char* uuid=NULL; float price=0.0f; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) uuid=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--price")==0){ char* v=next_val(argc,argv,i++); parse_float_str(v,&price); }
        }
        if(!inventory_update_product_price(inv, uuid, price)){
            fprintf(stderr,"Update failed.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        return 0;
    }

    if(str_cmp(cmd, "upd-manufacturer")==0){
        char *uuid=NULL,*name=NULL,*country=NULL,*website=NULL; int month=0,year=0,warr=0; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) uuid=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--name")==0) name=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--country")==0) country=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--est-month")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&month);} 
            else if(str_cmp(argv[i],"--est-year")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&year);} 
            else if(str_cmp(argv[i],"--website")==0) website=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--warranty")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&warr);} 
        }
        if(!inventory_update_manufacturer(inv, uuid, name, country, month, year, website, warr)){
            fprintf(stderr,"Update failed.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        return 0;
    }

    if(str_cmp(cmd, "add-accessory")==0){
        char* u=NULL; char* a=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) u=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--acc")==0) a=next_val(argc,argv,i++);
        }
        if(!inventory_add_accessory(inv,u,a)){
            fprintf(stderr,"Add accessory failed.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        return 0;
    }

    if(str_cmp(cmd, "rm-accessory")==0){
        char* u=NULL; char* a=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) u=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--acc")==0) a=next_val(argc,argv,i++);
        }
        if(!inventory_remove_accessory(inv,u,a)){
            fprintf(stderr,"Remove accessory failed.\n");
            return 1;
        }
        if(!save(inv,db_dir)) return 1;
        return 0;
    }

    if(str_cmp(cmd, "list-products")==0){
        inventory_list_products(inv);
        return 0;
    }
    if(str_cmp(cmd, "list-manufacturers")==0){
        inventory_list_manufacturers(inv);
        return 0;
    }
    if(str_cmp(cmd, "list-categories")==0){
        inventory_list_categories(inv);
        return 0;
    }
    if(str_cmp(cmd, "list-below")==0){
        int t=0; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--threshold")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&t);} 
        }
        inventory_list_below_stock(inv,t);
        return 0;
    }
    if(str_cmp(cmd, "list-accessories")==0){
        char* u=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) u=next_val(argc,argv,i++);
        }
        inventory_list_accessories(inv,u);
        return 0;
    }

    if(str_cmp(cmd, "list-products-in-category")==0){
        char* u=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--uuid")==0) u=next_val(argc,argv,i++);
        }
        int ci = find_category_index(inv,u);
        if(ci<0){
            fprintf(stderr,"Category not found.\n");
            return 1;
        }
        Category* c=&inv->categories[ci];
        for(i=0;i<c->product_uuids_count;i++){
            int pi=find_product_index(inv,c->product_uuids[i]);
            if(pi>=0) print_product_line(&inv->products[pi]);
        }
        return 0;
    }

    if(str_cmp(cmd, "search-model")==0){
        char* s=NULL; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--substr")==0) s=next_val(argc,argv,i++);
        }
        if(!s){
            fprintf(stderr,"Missing --substr.\n");
            return 1;
        }
        for(i=0;i<inv->products_count;i++){
            if(inv->products[i].model_name && str_icontains(inv->products[i].model_name,s)){
                print_product_line(&inv->products[i]);
            }
        }
        return 0;
    }

    if(str_cmp(cmd, "sort-products")==0){
        char* by=NULL; int desc=0; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--by")==0) by=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--desc")==0) desc=1;
        }
        if(!by){ fprintf(stderr,"Missing --by.\n"); return 1; }
        if(inv->products_count==0) return 0;
        Product* arr=(Product*)malloc(inv->products_count*sizeof(Product)); if(!arr) return 1;
        for(i=0;i<inv->products_count;i++) arr[i]=inv->products[i];
        if(str_cmp(by,"price")==0) sort_products_by_price(arr, inv->products_count, desc?0:1);
        else if(str_cmp(by,"score")==0) sort_products_by_score(arr, inv->products_count, desc?0:1);
        else if(str_cmp(by,"power")==0) sort_products_by_power(arr, inv->products_count, desc?0:1);
        else if(str_cmp(by,"stock")==0) sort_products_by_stock(arr, inv->products_count, desc?0:1);
        else if(str_cmp(by,"model")==0) sort_products_by_model(arr, inv->products_count, desc?0:1);
        else { fprintf(stderr,"Unknown field.\n"); free(arr); return 1; }
        for(i=0;i<inv->products_count;i++){
            print_product_line(&arr[i]);
        }
        free(arr);
        return 0;
    }

    if(str_cmp(cmd, "query")==0){
        char *cat=NULL,*man=NULL,*iface=NULL; float minp=-1e30f,maxp=1e30f; int minsc=-2147483647, maxsc=2147483647, maxpw=2147483647; char* sort=NULL; int desc=0; int i;
        for(i=2;i<argc;i++){
            if(str_cmp(argv[i],"--cat")==0) cat=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--man")==0) man=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--min-price")==0){ char* v=next_val(argc,argv,i++); parse_float_str(v,&minp);} 
            else if(str_cmp(argv[i],"--max-price")==0){ char* v=next_val(argc,argv,i++); parse_float_str(v,&maxp);} 
            else if(str_cmp(argv[i],"--min-score")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&minsc);} 
            else if(str_cmp(argv[i],"--max-score")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&maxsc);} 
            else if(str_cmp(argv[i],"--max-power")==0){ char* v=next_val(argc,argv,i++); parse_int_str(v,&maxpw);} 
            else if(str_cmp(argv[i],"--iface")==0) iface=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--sort")==0) sort=next_val(argc,argv,i++);
            else if(str_cmp(argv[i],"--desc")==0) desc=1;
        }
        int cnt=0; int cap=8; Product* arr=(Product*)malloc(cap*sizeof(Product)); if(!arr) return 1;
        for(i=0;i<inv->products_count;i++){
            Product* p=&inv->products[i];
            if(cat && (!p->category_uuid || str_cmp(p->category_uuid,cat)!=0)) continue;
            if(man && (!p->manufacturer_uuid || str_cmp(p->manufacturer_uuid,man)!=0)) continue;
            if(p->price<minp || p->price>maxp) continue;
            if(p->specs.performance_score<minsc || p->specs.performance_score>maxsc) continue;
            if(p->specs.power_watts>maxpw) continue;
            if(iface && (!p->specs.interface_type || str_cmp(p->specs.interface_type,iface)!=0)) continue;
            if(cnt>=cap){ int ncap=cap*2; Product* na=(Product*)malloc(ncap*sizeof(Product)); if(!na){ free(arr); return 1; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; }
            arr[cnt++]=*p;
        }
        if(sort && cnt>1){
            if(str_cmp(sort,"price")==0) sort_products_by_price(arr,cnt,desc?0:1);
            else if(str_cmp(sort,"score")==0) sort_products_by_score(arr,cnt,desc?0:1);
            else if(str_cmp(sort,"power")==0) sort_products_by_power(arr,cnt,desc?0:1);
            else if(str_cmp(sort,"stock")==0) sort_products_by_stock(arr,cnt,desc?0:1);
            else if(str_cmp(sort,"model")==0) sort_products_by_model(arr,cnt,desc?0:1);
        }
        for(i=0;i<cnt;i++){
            print_product_line(&arr[i]);
        }
        free(arr);
        return 0; 
    }

    fprintf(stderr, "Unknown command. Try 'inventory help'.\n");
    return 1;
}
