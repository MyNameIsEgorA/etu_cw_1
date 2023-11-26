#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "printFunctions.h"
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>

int start() {

    printf("Course work for option 5.10, created by Egor Anakhin.\n");
    printf("Введите номер опции: ");

    int option;

    scanf("%d", &option);

    getwchar();
    return option;
}

wchar_t* reading() {
    wprintf(L"12312312313");

    wchar_t *text = malloc(1 * sizeof(wchar_t));
    
    wchar_t character = getwchar();
    wchar_t prev_character = L'\0';
    int leng = 0;
    
    while (1) {
        if (prev_character == L'\n' || character == L'\n') {
            break;
        }
        if ((prev_character == L'.' && character == L' ') || character == L'\n') {
            prev_character = character;
            character = getwchar();
        } else {
            *(text + leng++) = character;
            prev_character = character;
            character = getwchar();
            text = realloc(text, (leng + 2) * sizeof(wchar_t));
            if (text == NULL) {
                printError(L"ERROR: failed to reallocate memory for text");
                return L" ";
            }
        }
    }
    *(text + leng) = '\0';
    return text;
}

int sentenceExists(struct Text *textStructured, wchar_t *sentence) {
    for (int i = 0; i < textStructured->len; i++) {
        int j;
        for (j = 0; j < textStructured->sentences[i]->len && j < wcslen(sentence); j++) {
            if (towlower(textStructured->sentences[i]->sentence[j]) != towlower(sentence[j])) {
                break;
            }
        }
        if (j == textStructured->sentences[i]->len && j == wcslen(sentence)) {
            return 1;
        }
    }
    return 0;
}

void addSentencesToText(struct Text *textStructured, wchar_t *text) {

    wchar_t* token = wcstok(text, L".", &text);

    while (token != NULL) {
        struct Sentence *newSentence = malloc(sizeof(struct Sentence));
        newSentence->sentence = malloc((wcslen(token) + 1) * sizeof(wchar_t));
        if (newSentence->sentence == NULL) {
            printf("\nERROR: failed to allocate memory for struct Sentence *newSentence\n");
            exit(1);
        }
        wcscpy(newSentence->sentence, token);
        newSentence->len = wcslen(token);
        textStructured->sentences = realloc(textStructured->sentences, (textStructured->len + 1) * sizeof(struct Sentence*));
        if (textStructured->sentences == NULL) {
            printError(L"ERROR: failed to reallocate memory for textStructed->sentences");
            exit(1);
        }
        if (!sentenceExists(textStructured, newSentence->sentence)) {
            textStructured->sentences[textStructured->len] = newSentence;
            textStructured->len++;
        }
        token = wcstok(NULL, L".", &text);
    }

    free(text);
}

int wrapper(void (*function)(struct Text *), struct Text *sentencesArray) {
    wchar_t *new_text = reading();
    if (wcscmp(new_text, L" ") == 0) {
        printf("Program competed unsuccsessfully\n");
        return 1;
    }
    addSentencesToText(sentencesArray, new_text);
    function(sentencesArray);
    return 0;
}