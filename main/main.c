#include <stdio.h>
#include <stdlib.h>
#include "../repl/repl.h"

int main(){
  fprintf(stdout, "Hello! This is the Pithikos programming language!\n");
  fprintf(stdout, "Feel free to type in commands\n\n");
  StartRepl();
  return EXIT_SUCCESS;
}
