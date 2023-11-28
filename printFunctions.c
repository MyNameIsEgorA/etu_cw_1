#include "structures.h"
#include <stdio.h>
#include <wchar.h>

void printError(wchar_t *text) {
    wprintf(L"\033[0;31m");
    wprintf(L"\n%ls\n", text);
    wprintf(L"\033[0m");
}

void printArray(struct Text *textStructured) {
    for (int i = 0; i < textStructured->len; i++) {
        wprintf(L"%ls\n", textStructured->sentences[i]->sentence);
    }
}