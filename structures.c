struct Sentence {
    char *sentence;
    int len;
};

struct Text{
    struct Sentence **sentences;
    int len;
};