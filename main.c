#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structures.h"
#include "printFunctions.h"
#include "inputHandler.h"
#include "palindromsFinder.h"
#include "replacingSpecSymbols.h"
#include "sorting.h"
#include "deleting.h"


int main() {

    struct Text sentencesArray;
    sentencesArray.len = 0;
    sentencesArray.sentences = malloc(1 * sizeof(struct Sentence*));

    int option = start();

    switch (option)
    {
    case 5:
        return 0;
    case 1:
        wrapper(palindromsInText, &sentencesArray);
        break;
    case 2:
        wrapper(replaceSpecialSymbols, &sentencesArray);
        break;
    case 3:
        wrapper(sortLetters, &sentencesArray);
        break;
    case 4:
        wrapper(deleteDifferentLanguages, &sentencesArray);
        break;
    default:
        printError("ERROR: incorrect input data. Please use numbers from 0 to 5\n");
        printf("Program competed unsuccsessfully\n");
        return 1;
    }

    printArray(&sentencesArray);

    return 0;
}