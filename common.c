#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

void logError(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}




