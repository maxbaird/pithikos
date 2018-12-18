PROJECT     = test.out
CC          = gcc
CFLAGS      = -c -Wall -Wextra -Werror

.phony : all clean

all : $(PROJECT)

$(PROJECT) : lexer_test.o lexer.o token.o common.o
	$(CC) $^ -o $@

lexer_test.o : lexer_test.c
	$(CC) $(CFLAGS) $< -o $@

lexer.o : ../lexer.c
	$(CC) $(CFLAGS) $< -o $@

token.o : ../../token/token.c
	$(CC) $(CFLAGS) $< -o $@

common.o : ../../common/common.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.out $(PROJECT)
