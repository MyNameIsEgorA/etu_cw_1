#include <string.h>
#include <stdlib.h>

#include "structures.h"

void replaceChars(char *str, const char *charsToReplace, const char *substr) {

    char *token = strtok(str, charsToReplace);
    while (token != NULL) {
        char *nextToken = strtok(NULL, charsToReplace);
        if (nextToken != NULL) {
            strcat(token, substr);
            strcat(token, nextToken);
        }
        token = nextToken;
    }

}


void replaceSpecialSymbols(struct Text *textStructured) {

    char *delims = ".,;!@#$^&*()";
    char *new_sentence;
    char *toAdd = ">special symbol<";
    
    for (int i = 0; i < textStructured->len; i++) {
        new_sentence = malloc(strlen(textStructured->sentences[i]->sentence) + 2);
        new_sentence[0] = '\0'; 
        for (int j = 0; j < strlen(textStructured->sentences[i]->sentence); j++) {
            if (strchr(delims, textStructured->sentences[i]->sentence[j])) {
                new_sentence = realloc(new_sentence, strlen(new_sentence) + strlen(toAdd) + 2);
                strcat(new_sentence, toAdd);
            } else {
                int len = strlen(new_sentence);
                new_sentence[len] = textStructured->sentences[i]->sentence[j];
                new_sentence[len + 1] = '\0';
            }
        }
        free(textStructured->sentences[i]->sentence); 
        textStructured->sentences[i]->sentence = new_sentence;
    }

}