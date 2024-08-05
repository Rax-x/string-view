#include <stdio.h>
#include <string.h>
#include <assert.h>

#define STRING_VIEW_IMPLEMENTATION
#include "../string_view.h"

#define PRINT_INFO_MESSAGE(msg) printf("\e[1;32m%s\e[0m\n", msg);

void test_string_view_trim(){
    string_view_t sv = new_string_view("  Hello World!!!\n\n  ", 20);
    
    PRINT_INFO_MESSAGE("Running `string_view_trim` test...");
    
    string_view_trim(&sv);
    assert(strncmp(string_view_data(sv), "Hello World!!!", string_view_size(sv)) == 0);
}

void test_string_view_remove_prefix(){
    string_view_t sv = new_string_view_from_cstr("http://example.com");
    
    PRINT_INFO_MESSAGE("Running `string_view_remove_prefix` tests...");

    string_view_remove_prefix(&sv, 7);
    assert(strncmp(string_view_data(sv), "example.com" , string_view_size(sv)) == 0);

    string_view_remove_prefix(&sv, string_view_size(sv)+1);
    assert(string_view_is_empty(sv) == true);
}

void test_string_view_remove_suffix(){
    string_view_t sv = new_string_view_from_cstr("test-name-file.txt");

    PRINT_INFO_MESSAGE("Running `string_view_remove_suffix` tests...");

    string_view_remove_suffix(&sv, 4);
    assert(strncmp(string_view_data(sv), "test-name-file", string_view_size(sv)) == 0);

    string_view_remove_prefix(&sv, string_view_size(sv)+1);
    assert(string_view_is_empty(sv) == true);
}

void test_string_view_swap(){
    string_view_t sv1 = new_string_view_from_cstr("Hello");
    string_view_t sv2 = new_string_view_from_cstr("Hello1");

    PRINT_INFO_MESSAGE("Running `string_view_swap` test...");

    string_view_swap(&sv1, &sv2);

    assert(
        strncmp(string_view_data(sv1), "Hello1", string_view_size(sv1)) == 0 &&
        strncmp(string_view_data(sv2), "Hello", string_view_size(sv2)) == 0
    );
}

void test_string_view_copy(){

    char buffer[30];
    string_view_t sv = new_string_view_from_cstr("Hello World");

    PRINT_INFO_MESSAGE("Running `string_view_copy` test...");

    string_view_copy(sv, buffer, 5, 6);
    assert(strncmp(buffer, "World", 5) == 0);

    string_view_copy(sv, buffer, 12, 6);
    assert(strncmp(buffer, "World", 5) == 0);
}

void test_string_view_substr(){
    
    string_view_t sv = new_string_view_from_cstr("http://example.com/");
    
    PRINT_INFO_MESSAGE("Running `string_view_substr` tests...");
    
    string_view_t result = string_view_substr(sv, 7, 11);
    assert(strncmp(string_view_data(result), "example.com", string_view_size(result)) == 0);

    result = string_view_substr(sv, 7, 15);
    assert(strncmp(string_view_data(result), "example.com/", string_view_size(result)) == 0);

    result = string_view_substr(sv, string_view_size(sv)+1, 11);
    assert(string_view_is_empty(result) == true);
}

void test_string_view_compare(){

    string_view_t sv1 = new_string_view("Hello", 5);
    string_view_t sv2 = new_string_view("Hello World", 11);

    PRINT_INFO_MESSAGE("Running `string_view_compare` tests...");

    assert(string_view_compare(sv1, sv2) < 0);
    assert(string_view_compare(string_view_substr(sv2, 0, string_view_size(sv1)), sv1) == 0);
    assert(string_view_compare(sv1, string_view_substr(sv2, 0, 3)) > 0);
}

void test_string_view_equal(){
    string_view_t sv1 = new_string_view("Hello", 5);
    string_view_t sv2 = new_string_view("Hello World", 11);

    PRINT_INFO_MESSAGE("Running `string_view_equal` tests...");

    assert(string_view_equal(sv1, sv2) == false);
    assert(string_view_equal(sv1, string_view_substr(sv2, 0, 5)) == true);
}

void test_string_view_starts_with(){

    string_view_t sv = new_string_view_from_cstr("http://google.com");

    PRINT_INFO_MESSAGE("Running `string_view_starts_with` tests..."); 

    assert(string_view_starts_with(sv, "http://", 7) == true);
    assert(string_view_starts_with(sv, "http://google.com/", string_view_size(sv)+1) == false);
    assert(string_view_starts_with(sv, "", 5) == false);
}

void test_string_view_ends_with(){

    string_view_t sv = new_string_view_from_cstr("http://google.com");

    PRINT_INFO_MESSAGE("Running `string_view_ends_with` tests..."); 

    assert(string_view_ends_with(sv, ".com", 4) == true);
    assert(string_view_ends_with(sv, "http://google.com/", string_view_size(sv)+1) == false);
    assert(string_view_ends_with(sv, "", 5) == false);
}

void test_string_view_find_char(){
    string_view_t sv = new_string_view_from_cstr("This is a string");

    PRINT_INFO_MESSAGE("Running `string_view_find_char` tests...");

    assert(string_view_find_char(sv, 'a', 10) == STRING_VIEW_NPOS);
    assert(string_view_find_char(sv, '.', 0) == STRING_VIEW_NPOS);
    assert(string_view_find_char(sv, 'a', 100) == STRING_VIEW_NPOS);
    assert(string_view_find_char(sv, 'a', 7) == 8);

}

void test_string_view_find_str(){
    string_view_t sv = new_string_view_from_cstr("This is a string");

    PRINT_INFO_MESSAGE("Running `string_view_find_str` tests...");

    assert(string_view_find_str(sv, "string", 10) == 10);
    assert(string_view_find_str(sv, "pippo", 0) == STRING_VIEW_NPOS);
    assert(string_view_find_str(sv, "Hello", 100) == STRING_VIEW_NPOS);
    assert(string_view_find_str(sv, "is", 4) == 5);

}

int main(void){

    test_string_view_trim();
    test_string_view_remove_prefix();
    test_string_view_remove_suffix();
    test_string_view_swap();
    test_string_view_copy();
    test_string_view_substr();
    test_string_view_compare();
    test_string_view_equal();
    test_string_view_starts_with();
    test_string_view_ends_with();
    test_string_view_find_char();
    test_string_view_find_str();

    PRINT_INFO_MESSAGE("\nAll Test passed!!! :)");

    return 0;
}
