#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void print_cword(char *cword, int charCount){
	for(int i = 0; i < charCount; i++){
		if (cword[i] == ' '){
			printf("_ ");
		}else{
			printf("%c ", cword[i]);
		}
	}
	printf("\n");
}


void init_cword(char *cword, int charCount){
	for(int i = 0; i < charCount; i++){
		cword[i] = ' ';
	}
	print_cword(cword, charCount);
}

void read_server_reply(char *cword, char *buf, char c, int charCount){

	unsigned int count = (unsigned char) buf[1];
	printf("Resposta: %u ", count);

	for(int i = 0; i < count; i++){
		unsigned int pos = (unsigned char) buf[i+2];
		cword[pos] = c;
		printf("%u ", pos);
	}

	printf("\n");
	print_cword(cword, charCount);
}

void end_game(char *cword, int charCount, char lastC){
	for(int i = 0; i < charCount; i++){
		if (cword[i] == ' ')
			cword[i] = lastC;
	}
	print_cword(cword, charCount);
}
