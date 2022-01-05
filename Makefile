CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

TEST_SRC = test/test.c
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

LIB_STATIC_NAME = libstring_view.a

ifeq ($(OS),Windows_NT)
	LIB_DYNAMIC_NAME = libstring_view.dll
else
	LIB_DYNAMIC_NAME = libstring_view.so
endif

.PHONY: test clean

build-static: $(SRC)
	$(CC) $(CFLAGS) -c $?
	ar r $(LIB_STATIC_NAME) $(OBJ)
	@rm -rf $(OBJ)

build-dynamic: $(SRC)
	$(CC) $(CFLAGS) -c -fPIC $(SRC) 
	$(CC) $(CFLAGS) -shared -o $(LIB_DYNAMIC_NAME) $(OBJ)
	@rm -rf $(OBJ)

test: $(TEST_SRC) $(SRC)
	$(info "Run tests...")
	@$(CC) $(CFLAGS) -o test/$@ $?
	@./test/test
	@rm -rf ./test/test

clean:
	-rm -rf $(LIB_STATIC_NAME) $(LIB_DYNAMIC_NAME)
