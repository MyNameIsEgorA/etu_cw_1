int start();

wchar_t* reading();

int sentenceExists(struct Text *textStructured, wchar_t *sentence);

void addSentencesToText(struct Text *textStructured, wchar_t *text);

int wrapper(void (*function)(struct Text *), struct Text *sentencesArray);