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

void init_forca(struct Forca *forca);

bool guessed_all(struct Forca *forca);

void check_char_in_word(struct Forca *forca, char c, unsigned int *oc_count, char *buf);