# String view for C language

This is a simple porting of C++ `std::string_view` for the C programming language. 
This library is header-only and follows the [stb-style](https://github.com/nothings/stb).
For more information about this style read [this](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt).

> [!IMPORTANT]  
> This library uses **C99** features ([Inline functions](https://en.wikipedia.org/wiki/Inline_function)). 

```c

#include <stdio.h>

#define STRING_VIEW_IMPLEMENTATION
#include "string_view.h"

int main(int argc, char** argv) {

    string_view_t hello = new_string_view_from_cstr("Hello string views");
    printf(STRING_VIEW_FORMAT "\n", STRING_VIEW_ARG(hello));

    return 0;
}

// Output: Hello string views

```

## 🌱 How to use this library?

Simple just include it and before the include directive add `#define STRING_VIEW_IMPLEMENTATION`.
No linking or stuff like that is needed.

> [!TIP]
> If in your project string views are shared among multiple files
> you need to create another file and put there the implmentation of the library.
> See the above example:
> ```c 
> // string_view_impl.c
> 
> #define STRING_VIEW_IMPLEMENTATION
> #include "string_view.h"
>
> ```
>
> ```c 
> // my_project_file.c
> 
> #include <stdio.h>
> #include "string_view.h"
> 
> void print_view(string_view_t sv) {
>   printf(STRING_VIEW_FORMAT "\n", STRING_VIEW_ARG(sv));
> }
> ```

## 📔 API

The full documentation is situated inside the [string_view.h](./string_view.h) file.

## Functions

| Function                     | Brief                                                                  |
|------------------------------|------------------------------------------------------------------------|
| `new_string_view`            | Creates a new string view from a character array and length            |
| `new_string_view_from_cstr`  | Creates a new string view from a null-terminated character string      |
| `string_view_data`           | Returns a pointer to the underlying character data of the string view  |
| `string_view_size`           | Returns the length of the string view                                  |
| `string_view_at`             | Returns the character at the specified index in the string view        |
| `string_view_front`          | Returns the first character of the string view                         |
| `string_view_back`           | Returns the last character of the string view                          |
| `string_view_is_empty`       | Checks if the string view is empty                                     |
| `string_view_trim_left`      | Trims whitespace characters from the beginning of a string view        |
| `string_view_trim_right`     | Trims whitespace characters from the end of a string view              |
| `string_view_trim`           | Trims whitespace characters from both ends of a string view            |
| `string_view_remove_prefix`  | Removes a prefix of specified length from a string view                |
| `string_view_remove_suffix`  | Removes a suffix of specified length from a string view                |
| `string_view_swap`           | Swaps the contents of two string views                                 |
| `string_view_copy`           | Copies a portion of a string view into a character array               |
| `string_view_substr`         | Creates a new string view that is a substring of the given string view |
| `string_view_compare`        | Compares two string views lexicographically                            |
| `string_view_equal`          | Checks if two string views are equal                                   |
| `string_view_starts_with`    | Checks if a string view starts with a given prefix                     |
| `string_view_ends_with`      | Checks if a string view ends with a given suffix                       |
| `string_view_find_char`      | Finds the first occurrence of a character in a string view             |
| `string_view_find_substring` | Finds the first occurrence of a substring within a string view         |

> [!NOTE]
> **string_view_contains** is dependent on the C standard version.
>
> In **C11** is defined as a macro that uses `_Generic` to dispatch the correct implementation.
> 
> | Macro                            | Brief                                                |
> |----------------------------------|------------------------------------------------------|
> | `string_view_contains`           | Checks if a string view contains a specified element |
>
> In **C99**, two separate macros are defined for character and substring checks:
>
> | Macro                            | Brief                                                 |
> |----------------------------------|-------------------------------------------------------|
> | `string_view_contains_char`      | Checks if a string view contains a specific character |
> | `string_view_contains_substring` | Checks if a string view contains a specific substring |

## 🔭 Resources

- [C++ std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view)
- [Tsoding String_View](https://github.com/tsoding/sv)

