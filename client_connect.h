
int addr_parse(const char *addrstr, const char *portstr, struct sockaddr_storage *storage);

int init_client(char *addr_str, char *port_str, struct sockaddr_storage *addr_storage);