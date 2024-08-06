#ifndef _STRING_VIEW_H_
#define _STRING_VIEW_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
    
#define STRING_VIEW_FORMAT "%.*s"
#define STRING_VIEW_ARG(sv) (sv).count, (sv).data

#define STRING_VIEW_EMPTY (new_string_view("", 0))

#define STRING_VIEW_NPOS ((size_t)-1)

typedef struct _string_view {
    const char* data;
    size_t count;
} string_view_t;

string_view_t new_string_view(const char* data, size_t count);
string_view_t new_string_view_from_cstr(const char* data);
    
const char* string_view_data(string_view_t sv);
size_t string_view_size(string_view_t sv);

char string_view_at(string_view_t sv, size_t index);
char string_view_front(string_view_t sv);
char string_view_back(string_view_t sv);
    
bool string_view_is_empty(string_view_t sv);

void string_view_trim_left(string_view_t *sv);
void string_view_trim_right(string_view_t *sv);
void string_view_trim(string_view_t *sv);

void string_view_remove_prefix(string_view_t *sv, size_t pos);
void string_view_remove_suffix(string_view_t *sv, size_t pos);  
    
void string_view_swap(string_view_t* sv1, string_view_t* sv2); 
void string_view_copy(string_view_t sv, char *dest, size_t size, size_t pos);

string_view_t string_view_substr(string_view_t sv, size_t pos, size_t count);

int string_view_compare(string_view_t sv1, string_view_t sv2);
bool string_view_equal(string_view_t sv1, string_view_t sv2);

bool string_view_starts_with(string_view_t sv, const char* prefix, size_t len);
bool string_view_ends_with(string_view_t sv, const char* suffix, size_t len);

size_t string_view_find_char(string_view_t sv, char c, size_t pos);
size_t string_view_find_str(string_view_t sv, char* str, size_t pos);

#if defined(__STDC__) && defined(__STDC_VERSION___) && __STDC_VERSION__ >= 201112L

#define string_view_contains(sv, needle) \
    _Generic(needle,                                                    \
             char : (string_view_find_char(sv, needle, 0) != STRINGSTRING_VIEW_NPOS), \
             const char* : (string_view_find_str(sv, needle, 0) != STRINGSTRING_VIEW_NPOS), \
             char* : (string_view_find_str(sv, needle, 0) != STRINGSTRING_VIEW_NPOS))

#else

#define string_view_contains_char(sv, c) (string_view_find_char(sv, needle, 0) != STRINGSTRING_VIEW_NPOS)
#define string_view_contains_str(sv, c) (string_view_find_str(sv, needle, 0) != STRINGSTRING_VIEW_NPOS)

#endif

#endif

#ifdef STRING_VIEW_IMPLEMENTATION

#include <ctype.h>
#include <string.h>

inline string_view_t new_string_view(const char* data, size_t size){
    return (string_view_t) {
        .data = data,
        .count = size
    };
}

inline string_view_t new_string_view_from_cstr(const char* data){
    return new_string_view(data, strlen(data));
}

inline char string_view_at(string_view_t sv, size_t index){
    return index < sv.count
        ? sv.data[index]
        : '\0';
}

inline char string_view_front(string_view_t sv){    
    return string_view_at(sv, 0);
}

inline char string_view_back(string_view_t sv){
    return string_view_at(sv, string_view_size(sv) - 1);
}

inline const char* string_view_data(string_view_t sv){
    return sv.data;
}

inline size_t string_view_size(string_view_t sv){
    return sv.count;
}

inline bool string_view_is_empty(string_view_t sv){
    return sv.count == 0;
}

void string_view_trim_left(string_view_t *sv) {
    while(isspace(sv->data[0]) && sv->count > 0){
        sv->data++;
        sv->count--;
    }
}

void string_view_trim_right(string_view_t *sv) {
    while(isspace(string_view_back(*sv)) && sv->count > 0){
        sv->count--;
    }
}

inline void string_view_trim(string_view_t *sv){
    string_view_trim_left(sv);
    string_view_trim_right(sv);
}

void string_view_remove_prefix(string_view_t *sv, size_t pos){
    if(pos > sv->count){
        *sv = STRING_VIEW_EMPTY;
    }else{
        sv->data += pos;
        sv->count -= pos;
    }
}

inline void string_view_remove_suffix(string_view_t *sv, size_t pos){
    sv->count -= (pos > sv->count)
        ? sv->count
        : pos;
}

void string_view_swap(string_view_t* sv1, string_view_t* sv2){
    string_view_t tmp = *sv1;
    *sv1 = *sv2;
    *sv2 = tmp;
}

void string_view_copy(string_view_t sv, char *dest, size_t size, size_t pos){

    if(dest == NULL || pos > sv.count) return;
    if(size > sv.count) size = sv.count - pos;

    memcpy(dest, &sv.data[pos], size);
}

string_view_t string_view_substr(string_view_t sv, size_t pos, size_t count){  
    if(count > (sv.count - pos)) {
        count = sv.count - pos;
    }

    return (pos < sv.count) 
        ? new_string_view(&sv.data[pos], count)
        : STRING_VIEW_EMPTY;
}

int string_view_compare(const string_view_t sv1, const string_view_t sv2){
    
    if(sv1.count > sv2.count) return 1;
    if(sv1.count < sv2.count) return -1;
    
    return strncmp(sv1.data, sv2.data, sv1.count);
}

inline bool string_view_equal(string_view_t sv1, string_view_t sv2){
    return string_view_compare(sv1, sv2) == 0;
}

inline bool string_view_starts_with(string_view_t sv, const char* prefix, size_t len){
    if(len > sv.count) return false;
    return strncmp(sv.data, prefix, len) == 0;
}


bool string_view_ends_with(string_view_t sv, const char* suffix, size_t len){
    
    if(len > sv.count) return false;

    const size_t pos = sv.count - len;
    return strncmp(&sv.data[pos], suffix, len) == 0;
}

size_t string_view_find_char(string_view_t sv, char c, size_t pos){

    for(size_t i = pos; i < sv.count; i++){
        if(sv.data[i] == c) return i;
    }

    return STRING_VIEW_NPOS;
}

size_t string_view_find_str(string_view_t sv, char* str, size_t pos){
    const size_t length = strlen(str);

    if(length > sv.count) return STRING_VIEW_NPOS;

    for(size_t i = pos; i <= sv.count - length; i++){
        if(strncmp(&sv.data[i], str, length) == 0) return i;
    }

    return STRING_VIEW_NPOS;
}


#endif
