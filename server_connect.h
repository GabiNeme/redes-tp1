#pragma once


int init_server_sockaddr(int iPversion, const char *portstr, struct sockaddr_storage *storage);

int init_server(char *port, struct sockaddr_storage *saddr_storage);