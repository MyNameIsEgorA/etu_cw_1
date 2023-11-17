int start();

char* reading();

int sentenceExists(struct Text *textStructured, char *sentence);

void addSentencesToText(struct Text *textStructured, char *text);

int wrapper(void (*function)(struct Text *), struct Text *sentencesArray);