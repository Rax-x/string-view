#include <ctype.h>
#include "string_view.h"

// To avoid string.h...
static uint32_t xstrlen(char* str){
    uint32_t length = 0;
    while (*str++) length++;
    return length;
}

static bool compare_str(char* str1, char* str2, uint32_t len){
    while(len--){
        if(*str1++ != *str2++) return false;
    }
    return true;
}


bool sv_is_null(string_view sv){
    return sv.data == NULL;
}

string_view sv_from_parts(char* data, uint32_t size){
    return (string_view) {
        .data = data,
        .size = size
    };
}

string_view sv_from_str(char* data){
    return sv_from_parts(data, xstrlen(data));
}

char sv_at(string_view sv, uint32_t index){
    return (index > sv.size) ? 0 : *(sv.data+index);
}

char sv_front(string_view sv){    
    return *sv.data;
}

char sv_back(string_view sv){
    return *(sv.data+sv.size);
}

char* sv_data(string_view sv){
    return sv.data;
}

uint32_t sv_size(string_view sv){
    return sv.size;
}

bool sv_is_empty(string_view sv){
    return (sv.data == NULL || sv.size == 0) ? true : false;
}

void sv_trim(string_view *sv){
    for(; isspace(*sv->data); sv->data++, sv->size--);
    for(; isspace(*(sv->data+sv->size-1)); sv->size--);
}

void sv_remove_prefix(string_view *sv, uint32_t pos){
    if(pos > sv->size){
        *sv = SV_NULL;
    }else{
        sv->data += pos;
        sv->size -= pos;
    }
}

void sv_remove_suffix(string_view *sv, uint32_t pos){
    if(pos > sv->size){
        *sv = SV_NULL;
    }else{
        sv->size -= pos;  
    }
}

void sv_swap(string_view* sv1, string_view* sv2){
    string_view tmp = *sv1;
    *sv1 = *sv2;
    *sv2 = tmp;
}

void sv_copy(string_view sv, char *dest, uint32_t size, uint32_t pos){
    uint32_t i;

    if(dest == NULL || pos > sv.size) return;
    if(size > sv.size) size = sv.size-pos;

    for(i=0; i<size; i++){
        *(dest+i) = *((sv.data+pos)+i);
    }
}

string_view sv_substr(string_view sv, uint32_t pos, uint32_t count){  
    if(count > (sv.size - pos)) count = sv.size - pos;
    return (pos > sv.size) ? SV_NULL : sv_from_parts(sv.data+pos, count);
}

int8_t sv_compare(const string_view sv1, const string_view sv2){
    
    if(sv1.size > sv2.size) return 1;
    if(sv1.size < sv2.size) return -1;
    
    if(sv1.size == sv2.size){
        for(uint32_t i=0; i<sv1.size; i++){
            if(*(sv1.data+i) < *(sv2.data+i)) return -1;
            if(*(sv1.data+i) > *(sv2.data+i)) return 1;
        }   
    }

    return 0;
}

bool sv_equal(string_view sv1, string_view sv2){
    if(sv1.size != sv2.size) return false;

    for(uint32_t i=0; i<sv1.size; i++){
        if(*(sv1.data+i) != *(sv2.data+i)) return false;
    }

    return true;
}

bool sv_starts_with(string_view sv, const char* prefix, uint32_t len){

    if(len > sv.size) return false;

    for (uint32_t i = 0; i < len; i++){
        if(*(sv.data+i) != *(prefix+i)) return false; 
    }
    
    return true;
}


bool sv_ends_with(string_view sv, const char* suffix, uint32_t len){
    
    uint32_t pos;
    
    if(len > sv.size) return false;

    pos = sv.size - len;
    for (uint32_t i = 0; i < len; i++){
        if(*((sv.data+pos)+i) != *(suffix+i)) return false; 
    }

    return true;
}

int32_t sv_find_char(string_view sv, char c, uint32_t pos){

    for(uint32_t i=pos; i<sv.size; i++){
        if(*(sv.data+i) == c) return i;
    }

    return -1;
}

int32_t sv_find_str(string_view sv, char* str, uint32_t pos){
    uint32_t length = xstrlen(str);

    for(uint32_t i=pos; i<sv.size; i++){
        if(compare_str(sv.data+i, str, length)) return i;
    }

    return -1;
}