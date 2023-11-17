#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "structures.h"

int palindrom(char *word) {

    for (int i = 0; i < strlen(word) / 2; i++) {
        if (tolower(word[i]) != tolower(word[strlen(word) - i - 1])) {
            return 0;
        }
    }
    return 1;
    
}

void palindromsInText(struct Text *textStructured) {

    int count;
    int palindromCount;
    char *word;
    char *sentenceCopy = malloc(100);

    for (int i = 0; i < textStructured->len; i++) {
        count = 0;
        palindromCount = 0;
        for (int j = 0; j < textStructured->sentences[i]->len; j++) {
            strcpy(sentenceCopy, textStructured->sentences[i]->sentence);
            word = strtok(sentenceCopy, " ");
            while (word != NULL) {
                count++;
                palindromCount += palindrom(word);
                word = strtok(NULL, " ");
            }
        }
        if (palindromCount == 0) {
            printf("(%s) - Кто-то потерял все палиндромы.\n", textStructured->sentences[i]->sentence);
        } else if (palindromCount == count) {
            printf("(%s) - Палиндромы на месте!\n", textStructured->sentences[i]->sentence);
        } else {
            printf("(%s) - Чего-то не хватает.\n", textStructured->sentences[i]->sentence);
        }
    }

}