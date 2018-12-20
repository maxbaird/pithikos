#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void safeFree (void **ptr)
{
  if (ptr != NULL && *ptr != NULL)
  {
    free(*ptr);
    *ptr = NULL;
  }
}

void PITHIKOS_fatal(const char *msg){
  char str[PITHIKOS_BUFFER];
  snprintf(str, PITHIKOS_BUFFER, "FATAL ERROR: %s", msg);
  PITHIKOS_print(str, PITHIKOS_EROR);
  exit(EXIT_FAILURE);
}

void PITHIKOS_print(const char *msg, unsigned short int priority)
{
  if(msg != NULL)
  {
    fflush(stdout); /* In case stdout and stderr are the same */
    fflush(stderr);
    switch(priority)
    {
      case PITHIKOS_INFO:
        fprintf(stdout, "[ " CYN "%s Info" RESET " ] : %s \n", APP_NAME, msg);
        break;
      case PITHIKOS_WARN:
        fprintf(stdout, "[ " YEL "%s Warning" RESET " ] : %s \n", APP_NAME, msg);
        break;
      case PITHIKOS_EROR:
        fprintf(stderr, "[ " RED "%s Error" RESET " ] : %s \n", APP_NAME, msg);
        break;
      case PITHIKOS_DBUG:
#ifdef DEBUG
        fprintf(stdout, "[ " WHT "%s Debug" RESET " ] : %s \n", APP_NAME, msg);
#endif
        break;
    }

    fflush(stdout);
    fflush(stderr);
  }
}
