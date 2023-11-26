#include "structures.h"
#include <stdio.h>
#include <wchar.h>

void printError(wchar_t *text) {
    wprintf(L"\033[0;31m");
    wprintf(L"\n%s\n", text);
    wprintf(L"\033[0m");
}

void printArray(struct Text *textStructured) {
    for (int i = 0; i < textStructured->len; i++) {
        wprintf(L"%s\n", textStructured->sentences[i]->sentence);
    }
}