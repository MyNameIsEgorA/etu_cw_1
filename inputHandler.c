#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>


#include "structures.h"
#include "printFunctions.h"


int start() {

    wprintf(L"Course work for option 5.10, created by Egor Anakhin.\n");
    wprintf(L"Введите номер опции: ");

    int option;

    wscanf(L"%d", &option);

    // getwchar();
    return option;
}

wchar_t* reading() {
    setlocale(LC_CTYPE, "");
    wchar_t *text = malloc(10 * sizeof(wchar_t));
    if (text == NULL) {
        printError(L"ERROR: failed to allocate memory for text");
        free(text);
        return L" ";
    }

    wchar_t character = getwchar();
    int break_count = 0;
    int leng = 0;

    while (1) {

        if (character == L'\n') {
            break_count++;
        } else {
            break_count = 0;
        }

        if (break_count == 2) {
            break;
        }

        *(text + leng++) = character;
        text = realloc(text, (10 + wcslen(text)) * sizeof(wchar_t));
        if (text == NULL) {
            free(text);
            printError(L"ERROR: failed to reallocate memory for text");
            return L" ";
        }

        character = getwchar();
    }

    *(text + leng) = L'\0';
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
        newSentence->sentence = malloc((wcslen(token) + 20) * sizeof(wchar_t));
        if (newSentence->sentence == NULL) {
            printError(L"\nERROR: failed to allocate memory for struct Sentence *newSentence\n");
            exit(1);
        }
        wcscpy(newSentence->sentence, token);
        newSentence->len = wcslen(token);
        textStructured->sentences = realloc(textStructured->sentences, (textStructured->len + 30) * sizeof(struct Sentence*));
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

    setlocale(LC_CTYPE, "");

    wchar_t *new_text = reading();
    if (wcscmp(new_text, L" ") == 0) {
        printError(L"error at wrapper");
        return 1;
    }
    addSentencesToText(sentencesArray, new_text);
    function(sentencesArray);
    return 0;
}