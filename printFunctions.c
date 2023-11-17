#include "structures.h"
#include <stdio.h>

void printError(char *text) {
    printf("\033[0;31m");
    printf("\n%s\n", text);
    printf("\033[0m");
}

void printArray(struct Text *textStructured) {
    for (int i = 0; i < textStructured->len; i++) {
        printf("%s\n", textStructured->sentences[i]->sentence);
    }
}