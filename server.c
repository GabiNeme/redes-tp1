#include "common.h"
#include "server_forca.h"
#include "server_connect.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>


int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Para iniciar o servidor digite como argumento a porta de conexão: \n");
        printf("Exemplo: %s 51511\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //cria socket
    struct sockaddr_storage addr_storage;
    int serverSocket = init_server(argv[1], &addr_storage);
    struct sockaddr *addr = (struct sockaddr *)(&addr_storage);

    //adiciona ao socket o endereço local
    if (bind(serverSocket, addr, sizeof(addr_storage)) != 0) {
        logError("Failed to bind.");
    }

    //prepara para receber conexões
    if (listen(serverSocket, 10) != 0) {
        logError("Failed to listen.");
    }

    while (1) {

        //recebe conexão do cliente
        struct sockaddr_storage client_storage;
        struct sockaddr *client_addr = (struct sockaddr *)(&client_storage);
        socklen_t client_addrlen = sizeof(client_storage);

        int client_socket = accept(serverSocket, client_addr, &client_addrlen);
        if (client_socket == -1) {
            logError("Failed to accept new client connection");
        }

        //envia ao cliente o tamanho da palavra
        char buf[BUFSZ];
        memset(buf, 0, BUFSZ);
        buf[0] = 1;
        buf[1] = strlen(word);
        size_t count = send(client_socket, buf, 2 , 0);
        if (count != 2) {
            logError("send size of word");
        }

        //estrutura de dados para armazenar as letras adivinhadas
        struct Forca Forca;
        init_forca(&Forca);
        
        while(1){
            // recebe palpite do cliente
            memset(buf, 0, 2);
            recv(client_socket, buf, 2, 0);
            char c = buf[1];
            unsigned int oc_count;
            
            //verifica se a letra está na palavra
            check_char_in_word(&Forca, c, &oc_count, buf);
            
            //idetifica se cliente já adivinhou a palavra
            //e envia mensagem 4 se sim
            if (guessed_all(&Forca)){
                buf[0] = 4;
                count = send(client_socket, buf, 1, 0);
                if (count != 1) {
                    logError("send end of game");
                }
                break;
            }

            //envia a resposta ao palpite ao cliente
            count = send(client_socket, buf, oc_count+2, 0);
            if (count != oc_count+2) {
                logError("send size of word");
            }

        }


        free(Forca.guessed);
        close(client_socket);
    }

    return 0;
}