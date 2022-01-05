#ifndef _STRING_VIEW_H_
    #define _STRING_VIEW_H_

    #include <stdint.h>
    #include <stdbool.h>

    #ifndef NULL
        #ifndef _cplusplus
            #define NULL ((void *)0)
        #else
            #define NULL 0
        #endif
    #endif

    #if defined _WIN32 || defined _WIN64 
        #define SV_API __declspec(dllexport)
    #else 
        #define SV_API extern
    #endif
    

    #define SV_FORMAT "%.*s"
    #define SV_ARG(sv) (sv).size, (sv).data

    #define SV_NULL (string_view) {.data = NULL, .size = 0}

    typedef struct _string_view{
        char* data;
        uint32_t size;
    }string_view;

    SV_API string_view sv_from_parts(char* data, uint32_t size);
    SV_API string_view sv_from_str(char* data);
    
    SV_API char* sv_data(string_view sv);
    SV_API uint32_t sv_size(string_view sv);

    SV_API char sv_at(string_view sv, uint32_t index);
    SV_API char sv_front(string_view sv);
    SV_API char sv_back(string_view sv);
    
    SV_API bool sv_is_empty(string_view sv);
    SV_API bool sv_is_null(string_view sv);

    SV_API void sv_trim(string_view *sv);
    SV_API void sv_remove_prefix(string_view *sv, uint32_t pos);
    SV_API void sv_remove_suffix(string_view *sv, uint32_t pos);  
    
    SV_API void sv_swap(string_view* sv1, string_view* sv2); 
    SV_API void sv_copy(string_view sv, char *dest, uint32_t size, uint32_t pos);
    SV_API string_view sv_substr(string_view sv, uint32_t pos, uint32_t count);
    SV_API int8_t sv_compare(string_view sv1, string_view sv2);
    SV_API bool sv_equal(string_view sv1, string_view sv2);
    SV_API bool sv_starts_with(string_view sv, const char* prefix, uint32_t len);
    SV_API bool sv_ends_with(string_view sv, const char* suffix, uint32_t len);
    SV_API int32_t sv_find_char(string_view sv, char c, uint32_t pos);
    SV_API int32_t sv_find_str(string_view sv, char* str, uint32_t pos);

#endif