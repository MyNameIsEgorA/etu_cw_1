#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#include "structures.h"

void replaceChars(wchar_t *str, const wchar_t *charsToReplace, const wchar_t *substr) {

    wchar_t *token = wcstok(str, charsToReplace, &str);
    while (token != NULL) {
        wchar_t *nextToken = wcstok(NULL, charsToReplace, &str);
        if (nextToken != NULL) {
            wcscat(token, substr);
            wcscat(token, nextToken);
        }
        token = nextToken;
    }

}


void replaceSpecialSymbols(struct Text *textStructured) {

    wchar_t *delims = L".,;!@#$^&*()";
    wchar_t *new_sentence;
    wchar_t *toAdd = L">special symbol<";
    
    for (int i = 0; i < textStructured->len; i++) {
        new_sentence = malloc(wcslen(textStructured->sentences[i]->sentence) + 2);
        new_sentence[0] = L'\0'; 
        for (int j = 0; j < wcslen(textStructured->sentences[i]->sentence); j++) {
            if (wcschr(delims, textStructured->sentences[i]->sentence[j])) {
                new_sentence = realloc(new_sentence, wcslen(new_sentence) + wcslen(toAdd) + 2);
                wcscat(new_sentence, toAdd);
            } else {
                int len = wcslen(new_sentence);
                new_sentence[len] = textStructured->sentences[i]->sentence[j];
                new_sentence[len + 1] = '\0';
            }
        }
        free(textStructured->sentences[i]->sentence); 
        textStructured->sentences[i]->sentence = new_sentence;
    }

}