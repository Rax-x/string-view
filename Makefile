CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

TEST_SRC = test/test.c
SRC = $(wildcard *.c)

.PHONY: test

test: $(TEST_SRC) $(SRC)
	$(info "Run tests...")
	@$(CC) $(CFLAGS) -o test/$@ $?
	@./test/test
	@rm -rf ./test/test
