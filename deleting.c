#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"

int differentLanguages(char *sentence) {

    int latin = 0;
    int cyrillic = 0;

    for (int i = 0; sentence[i] != '\0'; i++) {
        if (isalpha(sentence[i])) {
            latin++;
        }
        else {
            if ((sentence[i] >= 'А') || sentence[i] >= 'а') {
                cyrillic++;
            }
        }
    }

    if (latin > 0 && cyrillic > 0) {
        return 1;
    }

    return 0;

}

void deletingSentenceFromText(struct Text *textStructured, int index) {

    free(textStructured->sentences[index]);

    for (int i = index; i < textStructured->len-1; i++) {
        textStructured->sentences[i] = textStructured->sentences[i+1];
    }

    textStructured->len--;

}

void deleteDifferentLanguages(struct Text *textStructured) {

    for (int i = 0; i < textStructured->len;) {
        if (differentLanguages(textStructured->sentences[i]->sentence)) {
            deletingSentenceFromText(textStructured, i);
        } else {
            i++;
        }
    }

    if (textStructured->len == 0) {
        printf("\033[1;33mAll sentences contained cyrillic and latin letters so TEXT is empty\033\n");
    }

}