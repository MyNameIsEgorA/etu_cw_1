int start();

wchar_t* reading();

int sentenceExists(struct Text *textStructured, wchar_t *sentence);

void addSentencesToText(struct Text *textStructured, wchar_t *text);

void removeExtraSpaces(wchar_t *str);

int wrapper(void (*function)(struct Text *), struct Text *sentencesArray);