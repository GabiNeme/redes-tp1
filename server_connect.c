#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

int init_server_sockaddr(int iPversion, const char *portstr, struct sockaddr_storage *storage) {
    uint16_t port = (uint16_t)atoi(portstr); // unsigned short
    if (port == 0) {
        return -1;
    }
    port = htons(port); // host to network short

    memset(storage, 0, sizeof(*storage));
    if (iPversion == 4) {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_addr.s_addr = INADDR_ANY;
        addr4->sin_port = port;
        return 0;
    } else if (iPversion == 6) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_addr = in6addr_any;
        addr6->sin6_port = port;
        return 0;
    } else {
        return -1;
    }
}

int init_server(char *port, struct sockaddr_storage *saddr_storage){
    if (init_server_sockaddr(version, port, saddr_storage) != 0) {
        logError("Failed to init server with port.\n");
    }

    int serverSocket = socket(saddr_storage->ss_family, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        logError("Failed to init server socket.\n");
    }

    //allow address reuse
    int enable = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0) {
        logError("Failed to configure socke.t");
    }

    return serverSocket;
}