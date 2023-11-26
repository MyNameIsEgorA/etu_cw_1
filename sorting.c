#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"
#include "printFunctions.h"


int countLatinLetters(wchar_t *sentence) {

    int count = 0;

    for (int i = 0; i < wcslen(sentence); i++) {
        if (isalpha((char)sentence[i])) {
            count++;
        }
    }

    return count;

}

int sortLettersCompare(const void* sentenceA, const void* sentenceB) {

    // используется void, так как функция не знает, что мы будем возвращать.
    // Const используется, чтобы случайно не поменять значения аргументов при сравнении.

    const struct Sentence* sentence_one = *(const struct Sentence**)sentenceA;
    const struct Sentence* sentence_two = *(const struct Sentence**)sentenceB;

    if (sentence_one == NULL || sentence_two == NULL) {
        printError(L"ERROR: sortLettersComapare arguments aren't Sentence struct");
        return 0;
    }

    return -(countLatinLetters(sentence_one->sentence) - countLatinLetters(sentence_two->sentence));
}

void sortLetters(struct Text *textStructured) {
    qsort(textStructured->sentences, textStructured->len, sizeof(struct Sentence*), sortLettersCompare);
}