#include <stdlib.h>

#include "test_utils.h"

#define STRING_VIEW_IMPLEMENTATION
#include "../string_view.h"

TEST_SUITE(string_view_creation) {

    TEST_CASE("Create an empty string view"){

        string_view_t sv1 = new_string_view("", 0);
        string_view_t sv2 = STRING_VIEW_EMPTY;

        TEST_ASSERT(string_view_is_empty(sv1), "Expect an empty string view.");
        TEST_ASSERT(string_view_is_empty(sv2), "Expect an empty string view.");
    }

    TEST_CASE("Create a new string view"){

        string_view_t sv = new_string_view("Hello World", 11);

        TEST_ASSERT(!string_view_is_empty(sv), "Expect a non empty string view.");
        TEST_ASSERT(string_view_size(sv) == 11, "Expect string view size equal to 11.");
    }

    TEST_CASE("Create a new string view from a string literal"){
        string_view_t sv = new_string_view_from_cstr("Hello World");

        TEST_ASSERT(!string_view_is_empty(sv), "Expect a non empty string view.");
        TEST_ASSERT(string_view_size(sv) == 11, "Expect string view size equal to 11.");
    }

}

TEST_SUITE(string_view_operators) {
    TEST_CASE("Retrive the first character of the string view"){
        string_view_t sv = new_string_view_from_cstr("Hello World");
        string_view_t empty_sv = STRING_VIEW_EMPTY;

        TEST_ASSERT(string_view_front(sv) == 'H', "Expect the character 'H'.");
        TEST_ASSERT(string_view_front(empty_sv) == '\0', "Expect the null terminator character.");
    }

    TEST_CASE("Retrive the last character of the string view"){

        string_view_t sv = new_string_view_from_cstr("Hello World");
        string_view_t empty_sv = STRING_VIEW_EMPTY;

        TEST_ASSERT(string_view_back(sv) == 'd', "Expect the character 'd'.");
        TEST_ASSERT(string_view_back(empty_sv) == '\0', "Expect the null terminator character.");
    }

    TEST_CASE("Retrive the character of the string view at the specified index"){

        string_view_t sv = new_string_view_from_cstr("Hello World");
        string_view_t empty_sv = STRING_VIEW_EMPTY;

        TEST_ASSERT(string_view_at(sv, 0) == 'H', "Expect the character 'H'.");
        TEST_ASSERT(string_view_at(sv, string_view_size(sv) - 1) == 'd', "Expect the character 'd'.");
        TEST_ASSERT(string_view_at(sv, 1000) == '\0', "Expect the null terminator character.");        


        TEST_ASSERT(string_view_at(empty_sv, 0) == '\0', "Expect the null terminator character.");        
        TEST_ASSERT(string_view_at(empty_sv, 100) == '\0', "Expect the null terminator character.");        
    }
}


TEST_SUITE(string_view_comparison){

    TEST_CASE("Comparison beetween string views"){

        string_view_t sv1 = new_string_view("Hello", 5);
        string_view_t sv2 = new_string_view("Hello World", 11);

        TEST_ASSERT(string_view_compare(sv1, sv2) < 0, "Expect first string view less then second string view.");
        TEST_ASSERT(string_view_compare(string_view_substr(sv2, 0, string_view_size(sv1)), sv1) == 0,
                    "Expect equal string views.");

        TEST_ASSERT(string_view_compare(sv1, string_view_substr(sv2, 0, 3)) > 0,
                    "Expect first string view greater then second string view.");
    }

    TEST_CASE("Check equality beetween string views"){
        string_view_t sv1 = new_string_view("Hello", 5);
        string_view_t sv2 = new_string_view("Hello World", 11);

        TEST_ASSERT(string_view_equal(sv1, sv2) == false, "Expect non equal string views.");
        TEST_ASSERT(string_view_equal(sv1, string_view_substr(sv2, 0, 5)) == true, "Expect equal string views.");
    }

}

TEST_SUITE(string_view_finding) {

    TEST_CASE("Find characters inside an empty string view"){

        string_view_t sv = STRING_VIEW_EMPTY;

        TEST_ASSERT(string_view_find_char(sv, 'A', 10) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");

        TEST_ASSERT(string_view_find_char(sv, '?', 0) == STRING_VIEW_NPOS,
                    "Expect STIRNG_VIEW_NPOS.");

        TEST_ASSERT(string_view_find_char(sv, ',', 100) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");
    }

    TEST_CASE("Find characters inside a string view"){

        string_view_t sv = new_string_view_from_cstr("This is a string");

        TEST_ASSERT(string_view_find_char(sv, 'a', 10) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");

        TEST_ASSERT(string_view_find_char(sv, '.', 0) == STRING_VIEW_NPOS,
                    "Expect STIRNG_VIEW_NPOS.");
        TEST_ASSERT(string_view_find_char(sv, 'a', 100) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");

        TEST_ASSERT(string_view_find_char(sv, 'a', 7) == 8, "Expect index equal to 8.");
        TEST_ASSERT(string_view_find_char(sv, 'g', 7) == string_view_size(sv) - 1,
                    "Expect index equal to 'string_view_size(sv) - 1'");

        TEST_ASSERT(string_view_find_char(sv, 'T', 1) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");
    }

    TEST_CASE("Find substring inside an empty string view"){
        string_view_t sv = STRING_VIEW_EMPTY;
        string_view_t needle;

        needle = new_string_view_from_cstr("notinstirng");
        TEST_ASSERT(string_view_find_substring(sv, needle, 0) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");

        needle = new_string_view_from_cstr("Hello");
        TEST_ASSERT(string_view_find_substring(sv, needle, 100) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");
    }

    TEST_CASE("Find a substring inside a string view"){
        string_view_t sv = new_string_view_from_cstr("This is a string");
        string_view_t needle;


        needle = new_string_view_from_cstr("string");
        TEST_ASSERT(string_view_find_substring(sv, needle, 10) == 10,
                    "Expect index equal to 10.");

        needle = new_string_view_from_cstr("notinstring");
        TEST_ASSERT(string_view_find_substring(sv, needle, 0) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");

        needle = new_string_view_from_cstr("Hello");
        TEST_ASSERT(string_view_find_substring(sv, needle, 100) == STRING_VIEW_NPOS,
                    "Expect STRING_VIEW_NPOS.");

        needle = new_string_view_from_cstr("is");
        TEST_ASSERT(string_view_find_substring(sv, needle, 4) == 5,
                    "Expect index equal to 5.");
    }
}


TEST_SUITE(string_view_substrings) {

    TEST_CASE("Substring of an empty string view"){
        string_view_t empty_sv = STRING_VIEW_EMPTY;
        
        string_view_t sub_view = string_view_substr(empty_sv, 10, 20);
        TEST_ASSERT(string_view_is_empty(sub_view), "Expect an empty string view.");
    }

    TEST_CASE("Substring of string view"){
        string_view_t floating_number = new_string_view_from_cstr("12.243");
        
        string_view_t integral_part = string_view_substr(floating_number, 0, 2);
        TEST_ASSERT(!string_view_is_empty(integral_part), "Expect a non empty string view.");
        TEST_ASSERT(strncmp(string_view_data(integral_part), "12", string_view_size(integral_part)) == 0, 
                    "Expect the substring equal to '12'.");

        string_view_t decimal_part = string_view_substr(floating_number, 3, 233);
        TEST_ASSERT(!string_view_is_empty(decimal_part), "Expect a non empty string view.");
        TEST_ASSERT(string_view_size(decimal_part) == 3, "Expect the substring size equal to 3.");
        TEST_ASSERT(strncmp(string_view_data(decimal_part), "243", string_view_size(integral_part)) == 0, 
                    "Expect the substring equal to '243'.");
    }

    TEST_CASE("Parsing a simple url (https://example.com/?username=User1)"){

        string_view_t url = new_string_view_from_cstr("https://example.com/?username=User1");
    
        string_view_t protocol = string_view_substr(url, 0, 5);

        size_t domain_position = string_view_find_substring(url, new_string_view_from_cstr("://"), 0) + 3;
        string_view_t domain = string_view_substr(url, domain_position, 11);

        string_view_t query = string_view_substr(url, 21, string_view_size(url) - 21);
        
        TEST_ASSERT(strncmp(string_view_data(protocol), "https", string_view_size(protocol)) == 0,
                    "Expect the substirng equal to 'https'.");

        TEST_ASSERT(strncmp(string_view_data(domain), "example.com", string_view_size(domain)) == 0,
                    "Expect the substirng equal to 'example.com'.");

        TEST_ASSERT(strncmp(string_view_data(query), "username=User1", string_view_size(query)) == 0,
                    "Expect the substirng equal to 'username=User1'.");
    }
}

TEST_SUITE(string_view_utils) {

    TEST_CASE("Trim string views"){
        string_view_t sv = new_string_view("  Hello World!!!\n\n  ", 20);
        string_view_t spaces_sv = new_string_view_from_cstr("      \n      \t\r");

        string_view_trim_left(&sv);
        string_view_trim_right(&sv);
        TEST_ASSERT(strncmp(string_view_data(sv), "Hello World!!!", string_view_size(sv)) == 0,
                    "Expect 'Hello World!!!'.");

        string_view_trim(&spaces_sv);
        TEST_ASSERT(string_view_size(spaces_sv) == 0, "Expect an empty string view.");
    }

    TEST_CASE("Swap beetween string views"){
        string_view_t sv1 = new_string_view_from_cstr("Hello");
        string_view_t sv2 = new_string_view_from_cstr("Hello1");

        string_view_swap(&sv1, &sv2);

        TEST_ASSERT(strncmp(string_view_data(sv1), "Hello1", string_view_size(sv1)) == 0 &&
                    strncmp(string_view_data(sv2), "Hello", string_view_size(sv2)) == 0,
                    "Expect the contents of sv1 in sv2 and viceversa.");
    }

    TEST_CASE("Copy string view content in an exnternal buffer"){

        char buffer1[30] = {0};
        char buffer2[30] = {0};
        string_view_t sv = new_string_view_from_cstr("Hello World");

        string_view_copy(sv, buffer1, 5, 0);
        string_view_copy(sv, &buffer1[5], 5, 6);
        TEST_ASSERT(strncmp(buffer1, "HelloWorld", 10) == 0, "Expect 'HelloWorld' string in the buffer.");

        string_view_copy(sv, buffer2, 10, 100);
        TEST_ASSERT(strlen(buffer2) == 0, "Expect an empty buffer.");

        string_view_copy(sv, buffer2, 13, 3);
        TEST_ASSERT(strncmp(buffer2, "lo World", 9) == 0, "Expect 'lo World'.");
    }

}

TEST_SUITE(string_view_prefix_suffix) {

    TEST_CASE("Remove prefix from a string view") {
        string_view_t sv = new_string_view_from_cstr("http://example.com");
        string_view_t empty_sv = STRING_VIEW_EMPTY;

        string_view_remove_prefix(&sv, 7);
        TEST_ASSERT(strncmp(string_view_data(sv), "example.com" , string_view_size(sv)) == 0,
                    "Expect string view equal to 'example.com'.");

        string_view_remove_prefix(&sv, string_view_size(sv)+1);
        TEST_ASSERT(string_view_is_empty(sv), "Expect an empty string view.");

        string_view_remove_prefix(&empty_sv, string_view_size(sv)+100);
        TEST_ASSERT(string_view_is_empty(sv), "Expect an empty string view.");
    }

    TEST_CASE("Remove suffix from a string view") {
        string_view_t sv = new_string_view_from_cstr("test-name-file.txt");
        string_view_t empty_sv = STRING_VIEW_EMPTY;

        string_view_remove_suffix(&sv, 4);
        TEST_ASSERT(strncmp(string_view_data(sv), "test-name-file", string_view_size(sv)) == 0,
                    "Expect the string view without '.txt' suffix.");

        string_view_remove_suffix(&sv, string_view_size(sv)+1);
        TEST_ASSERT(string_view_is_empty(sv), "Expect an empty string view.");

        string_view_remove_suffix(&empty_sv, 11);
        TEST_ASSERT(string_view_is_empty(sv), "Expect an empty string view.");
    }


    TEST_CASE("Check if a string view starts with a specified prefix"){

        string_view_t sv = new_string_view_from_cstr("http://google.com");
        string_view_t empty_sv = STRING_VIEW_EMPTY;

        TEST_ASSERT(string_view_starts_with(sv, new_string_view_from_cstr("http://")), "Expcet true.");
        TEST_ASSERT(string_view_starts_with(sv, new_string_view("http://google.com/", string_view_size(sv)+1)) == false,
                    "Expect false.");

        TEST_ASSERT(string_view_starts_with(sv, STRING_VIEW_EMPTY), "Expect true.");
        TEST_ASSERT(string_view_starts_with(empty_sv, new_string_view_from_cstr("hello")) == false, "Expect false");
    }

    TEST_CASE("Check if a string view ends with a specified suffix."){

        string_view_t sv = new_string_view_from_cstr("http://google.com");
        string_view_t empty_sv = STRING_VIEW_EMPTY;

        TEST_ASSERT(string_view_starts_with(empty_sv, new_string_view_from_cstr("hello")) == false, "Expect false");
        TEST_ASSERT(string_view_starts_with(empty_sv, new_string_view_from_cstr("")), "Expect true");
        TEST_ASSERT(string_view_ends_with(sv, new_string_view("http://google.com/", string_view_size(sv)+1)) == false,
                    "Expect false.");

        TEST_ASSERT(string_view_ends_with(sv, STRING_VIEW_EMPTY), "Expect true.");
    }
}

int main(void){

    REGISTER_AND_RUN_SUITE(string_view_creation);
    REGISTER_AND_RUN_SUITE(string_view_operators);
    REGISTER_AND_RUN_SUITE(string_view_finding);
    REGISTER_AND_RUN_SUITE(string_view_substrings);
    REGISTER_AND_RUN_SUITE(string_view_comparison);
    REGISTER_AND_RUN_SUITE(string_view_prefix_suffix);
    REGISTER_AND_RUN_SUITE(string_view_utils);

    PRINT_TEST_RESULT();

    return TEST_FAILED_COUNT() != 0
        ? EXIT_FAILURE
        : EXIT_SUCCESS;
}
