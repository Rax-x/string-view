#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../string_view.h"

#define PRINT_INFO_MESSAGE(msg) printf("\e[1;32m%s\e[0m\n", msg);

void test_sv_trim(){
    string_view sv = sv_from_parts("  Hello World!!!\n\n  ", 20);
    
    PRINT_INFO_MESSAGE("Running `sv_trim` test...");
    
    sv_trim(&sv);
    assert(strncmp(sv_data(sv), "Hello World!!!", sv_size(sv)) == 0);
}

void test_sv_remove_prefix(){
    string_view sv = sv_from_str("http://example.com");
    
    PRINT_INFO_MESSAGE("Running `sv_remove_prefix` tests...");

    sv_remove_prefix(&sv, 7);
    assert(strncmp(sv_data(sv), "example.com" , sv_size(sv)) == 0);

    sv_remove_prefix(&sv, sv_size(sv)+1);
    assert(sv_is_null(sv) == true);
}

void test_sv_remove_suffix(){
    string_view sv = sv_from_str("test-name-file.txt");

    PRINT_INFO_MESSAGE("Running `sv_remove_suffix` tests...");

    sv_remove_suffix(&sv, 4);
    assert(strncmp(sv_data(sv), "test-name-file", sv_size(sv)) == 0);

    sv_remove_prefix(&sv, sv_size(sv)+1);
    assert(sv_is_null(sv) == true);
}

void test_sv_swap(){
    string_view sv1 = sv_from_str("Hello");
    string_view sv2 = sv_from_str("Hello1");

    PRINT_INFO_MESSAGE("Running `sv_swap` test...");

    sv_swap(&sv1, &sv2);

    assert(
        strncmp(sv_data(sv1), "Hello1", sv_size(sv1)) == 0 &&
        strncmp(sv_data(sv2), "Hello", sv_size(sv2)) == 0
    );
}

void test_sv_copy(){

    char buffer[30];
    string_view sv = sv_from_str("Hello World");

    PRINT_INFO_MESSAGE("Running `sv_copy` test...");

    sv_copy(sv, buffer, 5, 6);
    assert(strncmp(buffer, "World", 5) == 0);

    sv_copy(sv, buffer, 12, 6);
    assert(strncmp(buffer, "World", 5) == 0);
}

void test_sv_substr(){
    
    string_view sv = sv_from_str("http://example.com/");
    
    PRINT_INFO_MESSAGE("Running `sv_substr` tests...");
    
    string_view result = sv_substr(sv, 7, 11);
    assert(strncmp(sv_data(result), "example.com", sv_size(result)) == 0);

    result = sv_substr(sv, 7, 15);
    assert(strncmp(sv_data(result), "example.com/", sv_size(result)) == 0);

    result = sv_substr(sv, sv_size(sv)+1, 11);
    assert(sv_is_null(result) == true);
}

void test_sv_compare(){

    string_view sv1 = sv_from_parts("Hello", 5);
    string_view sv2 = sv_from_parts("Hello World", 11);

    PRINT_INFO_MESSAGE("Running `sv_compare` tests...");

    assert(sv_compare(sv1, sv2) < 0);
    assert(sv_compare(sv_substr(sv2, 0, sv_size(sv1)), sv1) == 0);
    assert(sv_compare(sv1, sv_substr(sv2, 0, 3)) > 0);
}

void test_sv_equal(){
    string_view sv1 = sv_from_parts("Hello", 5);
    string_view sv2 = sv_from_parts("Hello World", 11);

    PRINT_INFO_MESSAGE("Running `sv_equal` tests...");

    assert(sv_equal(sv1, sv2) == false);
    assert(sv_equal(sv1, sv_substr(sv2, 0, 5)) == true);
}

void test_sv_starts_with(){

    string_view sv = sv_from_str("http://google.com");

    PRINT_INFO_MESSAGE("Running `sv_starts_with` tests..."); 

    assert(sv_starts_with(sv, "http://", 7) == true);
    assert(sv_starts_with(sv, "http://google.com/", sv_size(sv)+1) == false);
    assert(sv_starts_with(sv, "", 5) == false);
}

void test_sv_ends_with(){

    string_view sv = sv_from_str("http://google.com");

    PRINT_INFO_MESSAGE("Running `sv_ends_with` tests..."); 

    assert(sv_ends_with(sv, ".com", 4) == true);
    assert(sv_ends_with(sv, "http://google.com/", sv_size(sv)+1) == false);
    assert(sv_ends_with(sv, "", 5) == false);
}

void test_sv_find_char(){
    string_view sv = sv_from_str("This is a string");

    PRINT_INFO_MESSAGE("Running `sv_find_char` tests...");

    assert(sv_find_char(sv, 'a', 10) == -1);
    assert(sv_find_char(sv, '.', 0) == -1);
    assert(sv_find_char(sv, 'a', -1) == -1);
    assert(sv_find_char(sv, 'a', 7) == 8);

}

void test_sv_find_str(){
    string_view sv = sv_from_str("This is a string");

    PRINT_INFO_MESSAGE("Running `sv_find_str` tests...");

    assert(sv_find_str(sv, "string", 10) == 10);
    assert(sv_find_str(sv, "pippo", 0) == -1);
    assert(sv_find_str(sv, "Hello", -1) == -1);
    assert(sv_find_str(sv, "is", 4) == 5);

}

int main(void){

    test_sv_trim();
    test_sv_remove_prefix();
    test_sv_remove_suffix();
    test_sv_swap();
    test_sv_copy();
    test_sv_substr();
    test_sv_compare();
    test_sv_equal();
    test_sv_starts_with();
    test_sv_ends_with();
    test_sv_find_char();
    test_sv_find_str();

    PRINT_INFO_MESSAGE("\nAll Test passed!!! :)");

    return 0;
}
