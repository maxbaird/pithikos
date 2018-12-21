PROJECT     = pithikos.out
CC          = gcc
CFLAGS      = -c -Wall -Wextra -Werror

.phony : all clean

all : $(PROJECT)

$(PROJECT) : main.o repl.o lexer.o token.o common.o
	$(CC) $^ -o $@

main.o : main/main.c
	$(CC) $(CFLAGS) $< -o $@

repl.o : repl/repl.c
	$(CC) $(CFLAGS) $< -o $@

lexer.o : lexer/lexer.c
	$(CC) $(CFLAGS) $< -o $@

token.o : token/token.c
	$(CC) $(CFLAGS) $< -o $@

common.o : common/common.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.out $(PROJECT)
