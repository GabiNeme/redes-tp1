#include "common.h"
#include "client_connect.h"
#include "client_forca.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>



int main(int argc, char **argv) {
	if (argc != 3) {
        printf("Para iniciar o cliente digite como argumento o endereço (IPv4 ou IPv6) e porta de conexão: \n");
        printf("Exemplo: %s 51511\n", argv[0]);
		printf("example: %s 127.0.0.1 51511\n", argv[0]);
        exit(EXIT_FAILURE);
	}

	struct sockaddr_storage storage;
	int ssocket = init_client(argv[1], argv[2], &storage);

	char buf[BUFSZ];

	//recebe do servidor o tamanho da palavra
	memset(buf, 0, BUFSZ);
	size_t count = recv(ssocket, buf, BUFSZ, 0);
	unsigned int charCount = (unsigned char) buf[1];
	printf("Tamanho da palavra: %u\n", charCount);
	char cword[charCount];
	init_cword(cword, charCount);

	while(1){

		//pergunta ao usuário o palpite
		char c[BUFSIZ];
		printf("Palpite: ");
		scanf("%s", c);
		if (strlen(c) != 1){
			printf("O palpite deve ter apenas uma letra.\n");
			continue;
		} 

		//envia o palpite do usuário para o servidor
		memset(buf, 0, BUFSZ);
		buf[0] = 2;
		buf[1] = c[0];
		count = send(ssocket, buf, 2, 0);
		if (count != 2) {
			logError("send");
		}
		
		//recebe do servidor a resposta ao palpite
		memset(buf, 0, BUFSZ);
		recv(ssocket, buf, BUFSZ, 0);
			
		int type = buf[0];

		//decodigica mensagem enviada pelo servidor
		if (type == 4){ //caso tenha encerrado o jogo
			end_game(cword, charCount, c[0]);
			break;
		}else{ //caso seja a resposta ao palpite
			read_server_reply(cword, buf, c[0], charCount); 
		}
	}

	close(ssocket);



	return 0;
}