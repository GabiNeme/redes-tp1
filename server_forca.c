#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


struct Forca {
    int sizeWord;
    bool *guessed;

};

void init_forca(struct Forca *forca){
    forca->sizeWord = strlen(word);

    forca->guessed = malloc(sizeof(bool) * strlen(word));
}

bool guessed_all(struct Forca *forca){
    for (int i = 0; i < forca->sizeWord; i++){
        if (!forca->guessed[i])
            return false;
    }
    return true;
}

void check_char_in_word(struct Forca *forca, char c, unsigned int *oc_count, char *buf){

    char placements[BUFSIZ] = "";
    //count ocurrencies
    unsigned int count = 0;
    for (int i = 0; i < forca->sizeWord; i++){
        if (word[i] == c || word[i] == toupper(c)){
            placements[count] = i;
            forca->guessed[i] = true;
            count++;
        }
    }

    memset(buf, 0, BUFSZ);
    buf[0] = 3;
    buf[1] = count;
    strcat(buf, placements);
    *oc_count = count;
}