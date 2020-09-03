all:
	gcc -Wall -c common.c
	gcc -Wall -c server_forca.c
	gcc -Wall -c server_connect.c
	gcc -Wall -c client_forca.c
	gcc -Wall -c client_connect.c
	gcc -Wall client.c common.o client_connect.o client_forca.o -o cliente
	gcc -Wall server.c common.o server_connect.o server_forca.o -o servidor

clean:
	rm common.o client_connect.o client_forca.o server_connect.o server_forca.o cliente servidor
