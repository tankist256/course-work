#include <stdio.h>
#include <stdlib.h>
#include "../headers/data_structures.h"
#include "../headers/technical_requirements.h"

static int to_lower_char(int c){
    if(c>='A'&&c<='Z') return c+32;
    return c;
}

int str_len(char* s){
    int n = 0;
    if(!s) return 0;
    while(s[n]){
        n++;
    }
    return n;
}

int str_cmp(char* a, char* b){
    int i = 0;
    if(a==b) return 0;
    if(!a) return -1;
    if(!b) return 1;
    while(a[i] && b[i]){
        if(a[i]!=b[i]) return (a[i]<b[i])?-1:1;
        i++;
    }
    if(a[i]==b[i]) return 0;
    return a[i]?1:-1;
}

int str_icmp(char* a, char* b){
    int i = 0;
    if(a==b) return 0;
    if(!a) return -1;
    if(!b) return 1;
    while(a[i] && b[i]){
        int ca = to_lower_char(a[i]);
        int cb = to_lower_char(b[i]);
        if(ca!=cb) return (ca<cb)?-1:1;
        i++;
    }
    if(a[i]==b[i]) return 0;
    return a[i]?1:-1;
}

char* str_dup(char* s){
    if(!s) return NULL;
    int n = str_len(s);
    char* p = (char*)malloc(n + 1);
    if(!p) return NULL;
    int i;
    for(i=0;i<n;i++) p[i]=s[i];
    p[n]='\0';
    return p;
}

int str_contains(char* haystack, char* needle){
    if(!haystack||!needle) return 0;
    int n = str_len(needle);
    if(n==0) return 1;
    int h = str_len(haystack);
    if(n>h) return 0;
    int i,j;
    for(i=0;i<=h-n;i++){
        for(j=0;j<n;j++){
            if(haystack[i+j]!=needle[j]) break;
        }
        if(j==n) return 1;
    }
    return 0;
}

int str_icontains(char* haystack, char* needle){
    if(!haystack||!needle) return 0;
    int n = str_len(needle);
    if(n==0) return 1;
    int h = str_len(haystack);
    if(n>h) return 0;
    int i,j;
    for(i=0;i<=h-n;i++){
        for(j=0;j<n;j++){
            int ca = to_lower_char(haystack[i+j]);
            int cb = to_lower_char(needle[j]);
            if(ca!=cb) break;
        }
        if(j==n) return 1;
    }
    return 0;
}

int parse_int_str(char* s, int* out){
    if(!s||!out) return 0;
    int i = 0;
    int sign = 1;
    long v = 0;
    if(s[i]=='+'){
        i++;
    } else if(s[i]=='-'){
        sign = -1;
        i++;
    }
    int digits = 0;
    while(s[i]){
        char c = s[i];
        if(c<'0'||c>'9') return 0;
        v = v*10 + (c-'0');
        digits++;
        i++;
    }
    if(digits==0) return 0;
    v *= sign;
    if(v>2147483647L||v<(-2147483648L)) return 0;
    *out = (int)v;
    return 1;
}

int parse_float_str(char* s, float* out){
    if(!s||!out) return 0;
    int i = 0;
    int sign = 1;
    long ip = 0;
    long fp = 0;
    int fcnt = 0;
    int has_dot = 0;
    if(s[i]=='+'){
        i++;
    } else if(s[i]=='-'){
        sign = -1;
        i++;
    }
    int any = 0;
    for(; s[i]; i++){
        char c = s[i];
        if(c=='.'){
            if(has_dot) return 0;
            has_dot = 1;
            continue;
        }
        if(c<'0'||c>'9') return 0;
        any = 1;
        if(!has_dot){
            ip = ip*10 + (c-'0');
        } else {
            fp = fp*10 + (c-'0');
            fcnt++;
        }
    }
    if(!any) return 0;
    float val = (float)ip;
    float denom = 1.0f;
    int k;
    for(k=0;k<fcnt;k++) denom *= 10.0f;
    val += (fcnt ? ((float)fp)/denom : 0.0f);
    val = (sign<0) ? -val : val;
    *out = val;
    return 1;
}

static int is_hex_char(int c){ if((c>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F')) return 1; return 0; }

int uuid_validate(char* s){
    if(!s) return 0;
    if(str_len(s)!=36) return 0;
    int i;
    for(i=0;i<36;i++){
        if(i==8||i==13||i==18||i==23){
            if(s[i]!='-') return 0;
        } else {
            if(!is_hex_char(s[i])) return 0;
        }
    }
    return 1;
}

static char hex_digit(int v){ return (char)(v<10? ('0'+v): ('a'+(v-10))); }

void uuid_generate(char out[UUID_STR_LEN]){
    int i; for(i=0;i<36;i++) out[i]='0'; out[36]='\0';
    for(i=0;i<36;i++){
        if(i==8||i==13||i==18||i==23){ out[i]='-'; continue; }
        int r=rand() & 0xF; out[i]=hex_digit(r);
    }
    out[14]='4';
    {
        int variants[4]={'8','9','a','b'}; out[19]=(char)variants[rand()%4];
    }
}

char* escape_field(char* s){
    if(!s) return str_dup("");
    int n = str_len(s);
    int i;
    int extra = 0;
    for(i=0;i<n;i++){
        char c = s[i];
        if(c=='|'||c=='\\'||c=='\n') extra++;
    }
    char* out = (char*)malloc(n+extra+1);
    if(!out) return NULL;
    int j = 0;
    for(i=0;i<n;i++){
        char c = s[i];
        if(c=='|'||c=='\\'){
            out[j++]='\\';
            out[j++]=c;
        } else if(c=='\n'){
            out[j++]='\\';
            out[j++]='n';
        } else {
            out[j++]=c;
        }
    }
    out[j]='\0';
    return out;
}

char* unescape_field(char* s){
    if(!s) return NULL;
    int n = str_len(s);
    char* out = (char*)malloc(n+1);
    if(!out) return NULL;
    int i = 0, j = 0;
    while(i<n){
        char c = s[i++];
        if(c=='\\' && i<n){
            char d = s[i++];
            if(d=='n') out[j++]='\n';
            else out[j++]=d;
        } else {
            out[j++]=c;
        }
    }
    out[j]='\0';
    return out;
}

static int write_line(FILE* f, char* s){
    if(fputs(s,f)==EOF) return 0;
    if(fputc('\n',f)==EOF) return 0;
    return 1;
}

static char* read_line_dyn(FILE* f){
    int cap=128; int len=0; char* buf=(char*)malloc(cap); if(!buf) return NULL; int c; while((c=fgetc(f))!=EOF){ if(c=='\r') continue; if(c=='\n') break; if(len+1>=cap){ int ncap=cap*2; char* nb=(char*)malloc(ncap); if(!nb){ free(buf); return NULL; } { int i; for(i=0;i<len;i++) nb[i]=buf[i]; } free(buf); buf=nb; cap=ncap; } buf[len++]=(char)c; }
    if(len==0 && c==EOF){ free(buf); return NULL; }
    buf[len]='\0'; return buf;
}

static char** split_escaped_fields(char* line, int* out_count){
    int n=str_len(line); int cap=8; int cnt=0; char** arr=(char**)malloc(cap*sizeof(char*)); if(!arr) return NULL;
    char* field=(char*)malloc(n+1); if(!field){ free(arr); return NULL; } int flen=0; int i=0;
    while(1){ if(i>=n){ field[flen]='\0'; char* un=unescape_field(field); if(!un){ free(field); free(arr); return NULL; } if(cnt>=cap){ int ncap=cap*2; char** na=(char**)malloc(ncap*sizeof(char*)); if(!na){ free(un); free(field); free(arr); return NULL; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; } arr[cnt++]=un; break; }
        char c=line[i++]; if(c=='|'){ field[flen]='\0'; char* un=unescape_field(field); if(!un){ free(field); for(i=0;i<cnt;i++) free(arr[i]); free(arr); return NULL; } if(cnt>=cap){ int ncap=cap*2; char** na=(char**)malloc(ncap*sizeof(char*)); if(!na){ free(un); free(field); for(i=0;i<cnt;i++) free(arr[i]); free(arr); return NULL; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; } arr[cnt++]=un; flen=0; }
        else if(c=='\\'){ if(i<n){ char d=line[i++]; if(d=='n') field[flen++]='\n'; else field[flen++]=d; } else { field[flen++]='\\'; } }
        else { field[flen++]=c; }
    }
    free(field); *out_count=cnt; return arr;
}

static void free_fields(char** fields, int count){ int i; for(i=0;i<count;i++) free(fields[i]); free(fields); }

int save_all(Inventory* inv, char* dir){
    char path[512]; FILE* f;
    int i,j;
    int n1 = snprintf(path, sizeof(path), "%s/manufacturers.txt", dir);
    if(n1<0 || n1>=(int)sizeof(path)) return 0;
    f=fopen(path,"w"); if(!f) return 0;
    for(i=0;i<inv->manufacturers_count;i++){
        Manufacturer* m=&inv->manufacturers[i];
        char* n=escape_field(m->name?m->name:"");
        char* c=escape_field(m->country?m->country:"");
        char* w=escape_field(m->website?m->website:"");
        if(!n||!c||!w){ if(n)free(n); if(c)free(c); if(w)free(w); fclose(f); return 0; }
        char line[2048];
        snprintf(line,sizeof(line),"%s|%s|%s|%d|%d|%s|%d", m->uuid?m->uuid:"", n, c, m->established.month, m->established.year, w, m->warranty_months);
        if(!write_line(f,line)){ fclose(f); free(n); free(c); free(w); return 0; }
        free(n); free(c); free(w);
    }
    fclose(f);

    n1 = snprintf(path, sizeof(path), "%s/categories.txt", dir);
    if(n1<0 || n1>=(int)sizeof(path)) return 0;
    f=fopen(path,"w"); if(!f) return 0;
    for(i=0;i<inv->categories_count;i++){
        Category* c=&inv->categories[i];
        char* n=escape_field(c->name?c->name:"");
        char* d=escape_field(c->description?c->description:"");
        if(!n||!d){ if(n)free(n); if(d)free(d); fclose(f); return 0; }
        char header[2048];
        int off=snprintf(header,sizeof(header),"%s|%s|%s|%d|%d", c->uuid?c->uuid:"", n, d, c->total_products_count, c->product_uuids_count);
        if(off<0){ free(n); free(d); fclose(f); return 0; }
        if(fputs(header,f)==EOF){ free(n); free(d); fclose(f); return 0; }
        for(j=0;j<c->product_uuids_count;j++){
            if(fputc('|',f)==EOF){ free(n); free(d); fclose(f); return 0; }
            if(fputs(c->product_uuids[j]?c->product_uuids[j]:"",f)==EOF){ free(n); free(d); fclose(f); return 0; }
        }
        if(fputc('\n',f)==EOF){ free(n); free(d); fclose(f); return 0; }
        free(n); free(d);
    }
    fclose(f);

    n1 = snprintf(path, sizeof(path), "%s/products.txt", dir);
    if(n1<0 || n1>=(int)sizeof(path)) return 0;
    f=fopen(path,"w"); if(!f) return 0;
    for(i=0;i<inv->products_count;i++){
        Product* p=&inv->products[i];
        char* mn=escape_field(p->model_name?p->model_name:"");
        char* sku=escape_field(p->sku?p->sku:"");
        char* iface=escape_field(p->specs.interface_type?p->specs.interface_type:"");
        if(!mn||!sku||!iface){ if(mn)free(mn); if(sku)free(sku); if(iface)free(iface); fclose(f); return 0; }
        char header[4096];
        int off=snprintf(header,sizeof(header),"%s|%s|%s|%s|%s|%f|%d|%d|%d|%d|%d|%s|%d|%d",
            p->uuid?p->uuid:"", mn, p->manufacturer_uuid?p->manufacturer_uuid:"", p->category_uuid?p->category_uuid:"", sku,
            p->price, p->stock_qty, p->release_date.month, p->release_date.year,
            p->specs.performance_score, p->specs.power_watts, iface, p->warranty_months, p->accessory_count);
        if(off<0){ free(mn); free(sku); free(iface); fclose(f); return 0; }
        if(fputs(header,f)==EOF){ free(mn); free(sku); free(iface); fclose(f); return 0; }
        for(j=0;j<p->accessory_count;j++){
            if(fputc('|',f)==EOF){ free(mn); free(sku); free(iface); fclose(f); return 0; }
            if(fputs(p->accessory_uuids[j]?p->accessory_uuids[j]:"",f)==EOF){ free(mn); free(sku); free(iface); fclose(f); return 0; }
        }
        if(fputc('\n',f)==EOF){ free(mn); free(sku); free(iface); fclose(f); return 0; }
        free(mn); free(sku); free(iface);
    }
    fclose(f);

    return 1;
}

int load_all(Inventory* inv, char* dir){
    char path[512]; FILE* f; int n1;
    n1=snprintf(path,sizeof(path),"%s/manufacturers.txt",dir); if(n1<0||n1>=(int)sizeof(path)) return 0; f=fopen(path,"r"); if(f){
        char* line; while((line=read_line_dyn(f))!=NULL){ int cnt=0; char** fields=split_escaped_fields(line,&cnt); free(line); if(!fields) { fclose(f); return 0; }
            if(cnt>=7){ int month=0,year=0,warr=0; parse_int_str(fields[3],&month); parse_int_str(fields[4],&year); parse_int_str(fields[6],&warr);
                inventory_add_manufacturer_with_uuid(inv, fields[0], fields[1], fields[2], month, year, fields[5], warr);
            }
            free_fields(fields,cnt);
        } fclose(f);
    }
    n1=snprintf(path,sizeof(path),"%s/categories.txt",dir); if(n1<0||n1>=(int)sizeof(path)) return 0; f=fopen(path,"r"); if(f){
        char* line; while((line=read_line_dyn(f))!=NULL){ int cnt=0; char** fields=split_escaped_fields(line,&cnt); free(line); if(!fields){ fclose(f); return 0; }
            if(cnt>=5){ int total=0; int pcount=0; parse_int_str(fields[3],&total); parse_int_str(fields[4],&pcount);
                char** plist=NULL; if(pcount>0 && cnt>=5+pcount){ plist=(char**)&fields[5]; }
                inventory_add_category_with_uuid(inv, fields[0], fields[1], fields[2], pcount, plist);
                if(inv->categories_count>0){ Category* c=&inv->categories[inv->categories_count-1]; c->total_products_count=total; }
            }
            free_fields(fields,cnt);
        } fclose(f);
    }
    n1=snprintf(path,sizeof(path),"%s/products.txt",dir); if(n1<0||n1>=(int)sizeof(path)) return 0; f=fopen(path,"r"); if(f){
        char* line; while((line=read_line_dyn(f))!=NULL){ int cnt=0; char** fields=split_escaped_fields(line,&cnt); free(line); if(!fields){ fclose(f); return 0; }
            if(cnt>=14){ float price=0.0f; int stock=0,rm=0,ry=0,score=0,power=0,warr=0,ac=0; parse_float_str(fields[5],&price); parse_int_str(fields[6],&stock); parse_int_str(fields[7],&rm); parse_int_str(fields[8],&ry);
                parse_int_str(fields[9],&score); parse_int_str(fields[10],&power); parse_int_str(fields[12],&warr); parse_int_str(fields[13],&ac);
                char** alist=NULL; if(ac>0 && cnt>=14+ac){ alist=(char**)&fields[14]; }
                inventory_add_product_with_uuid(inv, fields[0], fields[1], fields[2], fields[3], fields[4], price, stock, rm, ry, score, power, fields[11], warr, ac, alist);
            }
            free_fields(fields,cnt);
        } fclose(f);
    }
    return 1;
}

 

void sort_products_by_price(Product* arr, int count, int ascending){ 
    if(!arr||count<=1) return; 
    int i,j; 
    for(i=0;i<count-1;i++){ 
        for(j=0;j<count-1-i;j++){ 
            float a=arr[j].price, b=arr[j+1].price; 
            int swap = ascending ? (a>b) : (a<b); 
            if(swap){ 
                Product t=arr[j]; 
                arr[j]=arr[j+1]; 
                arr[j+1]=t; 
            } 
        } 
    } 
}
void sort_products_by_score(Product* arr, int count, int ascending){ 
    if(!arr||count<=1) return; 
    int i,j; 
    for(i=0;i<count-1;i++){ 
        for(j=0;j<count-1-i;j++){ 
            int a=arr[j].specs.performance_score, b=arr[j+1].specs.performance_score; 
            int swap = ascending ? (a>b) : (a<b); 
            if(swap){ 
                Product t=arr[j]; 
                arr[j]=arr[j+1]; 
                arr[j+1]=t; 
            } 
        } 
    } 
}
void sort_products_by_power(Product* arr, int count, int ascending){ 
    if(!arr||count<=1) return; 
    int i,j; 
    for(i=0;i<count-1;i++){ 
        for(j=0;j<count-1-i;j++){ 
            int a=arr[j].specs.power_watts, b=arr[j+1].specs.power_watts; 
            int swap = ascending ? (a>b) : (a<b); 
            if(swap){ 
                Product t=arr[j]; 
                arr[j]=arr[j+1]; 
                arr[j+1]=t; 
            } 
        } 
    } 
}
void sort_products_by_stock(Product* arr, int count, int ascending){ 
    if(!arr||count<=1) return; 
    int i,j; 
    for(i=0;i<count-1;i++){ 
        for(j=0;j<count-1-i;j++){ 
            int a=arr[j].stock_qty, b=arr[j+1].stock_qty; 
            int swap = ascending ? (a>b) : (a<b); 
            if(swap){ 
                Product t=arr[j]; 
                arr[j]=arr[j+1]; 
                arr[j+1]=t; 
            } 
        } 
    } 
}
void sort_products_by_model(Product* arr, int count, int ascending){ 
    if(!arr||count<=1) return; 
    int i,j; 
    for(i=0;i<count-1;i++){ 
        for(j=0;j<count-1-i;j++){ 
            char* s1=arr[j].model_name?arr[j].model_name:""; 
            char* s2=arr[j+1].model_name?arr[j+1].model_name:""; 
            int cmp=str_cmp(s1,s2); 
            int swap = ascending ? (cmp>0) : (cmp<0); 
            if(swap){ 
                Product t=arr[j]; 
                arr[j]=arr[j+1]; 
                arr[j+1]=t; 
            } 
        } 
    } 
}

static Product* filter_alloc(int cap){ return (Product*)malloc(cap * sizeof(Product)); }

Product* filter_products_by_category(Inventory* inv, char* category_uuid, int* out_count){ int i,cnt=0,cap=8; Product* arr=filter_alloc(cap); if(!arr){ *out_count=0; return NULL; } for(i=0;i<inv->products_count;i++){ if(str_cmp(inv->products[i].category_uuid, category_uuid)==0){ if(cnt>=cap){ int ncap=cap*2; Product* na=(Product*)malloc(ncap*sizeof(Product)); if(!na){ free(arr); *out_count=0; return NULL; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; } arr[cnt++]=inv->products[i]; } } *out_count=cnt; return arr; }

Product* filter_products_by_manufacturer(Inventory* inv, char* manufacturer_uuid, int* out_count){ int i,cnt=0,cap=8; Product* arr=filter_alloc(cap); if(!arr){ *out_count=0; return NULL; } for(i=0;i<inv->products_count;i++){ if(str_cmp(inv->products[i].manufacturer_uuid, manufacturer_uuid)==0){ if(cnt>=cap){ int ncap=cap*2; Product* na=(Product*)malloc(ncap*sizeof(Product)); if(!na){ free(arr); *out_count=0; return NULL; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; } arr[cnt++]=inv->products[i]; } } *out_count=cnt; return arr; }

Product* filter_products_by_price_range(Inventory* inv, float min_price, float max_price, int* out_count){ int i,cnt=0,cap=8; Product* arr=filter_alloc(cap); if(!arr){ *out_count=0; return NULL; } for(i=0;i<inv->products_count;i++){ float p=inv->products[i].price; if(p>=min_price && p<=max_price){ if(cnt>=cap){ int ncap=cap*2; Product* na=(Product*)malloc(ncap*sizeof(Product)); if(!na){ free(arr); *out_count=0; return NULL; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; } arr[cnt++]=inv->products[i]; } } *out_count=cnt; return arr; }

Product* filter_products_by_score_range(Inventory* inv, int min_score, int max_score, int* out_count){ int i,cnt=0,cap=8; Product* arr=filter_alloc(cap); if(!arr){ *out_count=0; return NULL; } for(i=0;i<inv->products_count;i++){ int s=inv->products[i].specs.performance_score; if(s>=min_score && s<=max_score){ if(cnt>=cap){ int ncap=cap*2; Product* na=(Product*)malloc(ncap*sizeof(Product)); if(!na){ free(arr); *out_count=0; return NULL; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; } arr[cnt++]=inv->products[i]; } } *out_count=cnt; return arr; }

Product* filter_products_by_max_power(Inventory* inv, int max_power, int* out_count){ int i,cnt=0,cap=8; Product* arr=filter_alloc(cap); if(!arr){ *out_count=0; return NULL; } for(i=0;i<inv->products_count;i++){ int w=inv->products[i].specs.power_watts; if(w<=max_power){ if(cnt>=cap){ int ncap=cap*2; Product* na=(Product*)malloc(ncap*sizeof(Product)); if(!na){ free(arr); *out_count=0; return NULL; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; } arr[cnt++]=inv->products[i]; } } *out_count=cnt; return arr; }

Product* filter_products_by_interface(Inventory* inv, char* interface_type, int* out_count){ int i,cnt=0,cap=8; Product* arr=filter_alloc(cap); if(!arr){ *out_count=0; return NULL; } for(i=0;i<inv->products_count;i++){ char* it=inv->products[i].specs.interface_type?inv->products[i].specs.interface_type:""; if(str_cmp(it, interface_type)==0){ if(cnt>=cap){ int ncap=cap*2; Product* na=(Product*)malloc(ncap*sizeof(Product)); if(!na){ free(arr); *out_count=0; return NULL; } { int k; for(k=0;k<cnt;k++) na[k]=arr[k]; } free(arr); arr=na; cap=ncap; } arr[cnt++]=inv->products[i]; } } *out_count=cnt; return arr; }

void free_product_array(Product* arr, int count){ (void)count; if(arr) free(arr); }
