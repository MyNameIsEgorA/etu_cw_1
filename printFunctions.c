#include "structures.h"
#include <wchar.h>

void printError(wchar_t *text) {

    // Выводит текст-ошибку красным цветом. На вход получает текст, который нужно вывести

    wprintf(L"\033[0;31m");
    wprintf(L"\n%ls\n", text);
    wprintf(L"\033[0m");

}

void printArray(struct Text *textStructured) {

    // Выводит все предложения структуры Text. На вход получает стурктуру Text

    for (int i = 0; i < textStructured->len; i++) {
        wprintf(L"%ls\n", textStructured->sentences[i]->sentence);
    }

}

void printOptions() {
    wprintf(L",...");
}