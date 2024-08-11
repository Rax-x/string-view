# String view implementation for C language

This is a simple porting of C++ `std::string_view` for the C programming language. 
This library is header-only and follows the [stb-style](https://github.com/nothings/stb).
For more information about this style read [this](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt).

> [!NOTE]  
> This library uses C99 features (inline functions). 

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

## How use this library?

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
