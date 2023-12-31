#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "structures.h"
#include "printFunctions.h"


int countLatinLetters(char *sentence) {

    int count = 0;

    for (int i = 0; i < strlen(sentence); i++) {
        if (isalpha(sentence[i])) {
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
        printError("ERROR: sortLettersComapare arguments aren't Sentence struct");
        return 0;
    }

    return -(countLatinLetters(sentence_one->sentence) - countLatinLetters(sentence_two->sentence));
}

void sortLetters(struct Text *textStructured) {
    qsort(textStructured->sentences, textStructured->len, sizeof(struct Sentence*), sortLettersCompare);
}