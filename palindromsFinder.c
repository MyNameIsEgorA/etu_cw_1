#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"

int palindrom(wchar_t *word) {

    for (int i = 0; i < wcslen(word) / 2; i++) {
        if (towlower(word[i]) != towlower(word[wcslen(word) - i - 1])) {
            return 0;
        }
    }
    return 1;
    
}

void palindromsInText(struct Text *textStructured) {

    int count;
    int palindromCount;
    wchar_t *word;
    wchar_t *sentenceCopy = malloc(100);

    for (int i = 0; i < textStructured->len; i++) {
        count = 0;
        palindromCount = 0;
        for (int j = 0; j < textStructured->sentences[i]->len; j++) {
            wcscpy(sentenceCopy, textStructured->sentences[i]->sentence);
            word = wcstok(sentenceCopy, L" ", &sentenceCopy);
            while (word != NULL) {
                count++;
                palindromCount += palindrom(word);
                word = wcstok(NULL, L" ", &sentenceCopy);
            }
        }
        if (palindromCount == 0) {
            wprintf(L"(%ls) - Кто-то потерял все палиндромы.\n", textStructured->sentences[i]->sentence);
        } else if (palindromCount == count) {
            wprintf(L"(%ls) - Палиндромы на месте!\n", textStructured->sentences[i]->sentence);
        } else {
            wprintf(L"(%ls) - Чего-то не хватает.\n", textStructured->sentences[i]->sentence);
        }
    }

}