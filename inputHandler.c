#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "printFunctions.h"
#include <string.h>
#include <ctype.h>

int start() {

    printf("Course work for option 5.10, created by Egor Anakhin.\n");
    printf("Введите номер опции: ");

    int option;

    scanf("%d", &option);

    getchar();
    return option;
}

char* reading() {

    char *text = malloc(1 * sizeof(char));
    
    char character = getchar();
    char prev_character = '\0';
    int leng = 0;
    
    while (1) {
        if (prev_character == '\n' && character == '\n') {
            break;
        }
        if ((prev_character == '.' && character == ' ') || character == '\n') {
            prev_character = character;
            character = getchar();
        } else {
            *(text + leng++) = character;
            prev_character = character;
            character = getchar();
            text = realloc(text, (leng + 2) * sizeof(char));
            if (text == NULL) {
                printError("ERROR: failed to reallocate memory for text");
                return " ";
            }
        }
    }
    *(text + leng) = '\0';
    return text;
}

int sentenceExists(struct Text *textStructured, char *sentence) {
    for (int i = 0; i < textStructured->len; i++) {
        int j;
        for (j = 0; j < textStructured->sentences[i]->len && j < strlen(sentence); j++) {
            if (tolower(textStructured->sentences[i]->sentence[j]) != tolower(sentence[j])) {
                break;
            }
        }
        if (j == textStructured->sentences[i]->len && j == strlen(sentence)) {
            return 1;
        }
    }
    return 0;
}

void addSentencesToText(struct Text *textStructured, char *text) {

    char* token = strtok(text, ".");

    while (token != NULL) {
        struct Sentence *newSentence = malloc(sizeof(struct Sentence));
        newSentence->sentence = malloc((strlen(token) + 1) * sizeof(char));
        if (newSentence->sentence == NULL) {
            printf("\nERROR: failed to allocate memory for struct Sentence *newSentence\n");
            exit(1);
        }
        strcpy(newSentence->sentence, token);
        newSentence->len = strlen(token);
        textStructured->sentences = realloc(textStructured->sentences, (textStructured->len + 1) * sizeof(struct Sentence*));
        if (textStructured->sentences == NULL) {
            printError("ERROR: failed to reallocate memory for textStructed->sentences");
            exit(1);
        }
        if (!sentenceExists(textStructured, newSentence->sentence)) {
            textStructured->sentences[textStructured->len] = newSentence;
            textStructured->len++;
        }
        token = strtok(NULL, ".");
    }

    free(text);
}

int wrapper(void (*function)(struct Text *), struct Text *sentencesArray) {
    char *new_text = reading();
    if (strcmp(new_text, " ") == 0) {
        return 1;
    }
    if (strcmp(new_text, " ") == 0) {
        printf("Program competed unsuccsessfully\n");
        return 1;
    }
    addSentencesToText(sentencesArray, new_text);
    function(sentencesArray);
    return 0;
}