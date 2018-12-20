#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APP_NAME "PITHIKOS"

#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define PITHIKOS_BUFFER 256
#define PITHIKOS_MAX_INT_LEN     5 /* No more than 5 digits needed for an unsigned int */

#define PITHIKOS_INFO 1
#define PITHIKOS_WARN 2
#define PITHIKOS_EROR 3
#define PITHIKOS_DBUG 4

void safeFree (void **ptr);
void PITHIKOS_print(const char *msg, unsigned short int priority);
void PITHIKOS_fatal(const char *msg);

#endif /* __COMMON_H__ */
