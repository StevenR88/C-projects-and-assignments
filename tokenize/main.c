#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define MAX_WORD_LENGTH 20
#define MAX_NUMBER_OF_WORDS 100

char *moveToBeginningOfNextToken(char *inputString) {
    while (*inputString == ' ')  {
        inputString++;
    }

    return inputString;

}

int getCurrentTokenSize(char *inputString) {
    int counter = 0;

    while (*inputString != ' ' & *inputString != '\0'
            && *inputString++ && ++counter);

    return counter;
}

int tokenize(char *paragraph, char
        tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH]) {

    int override = 0;
    int wordCounter = 0;

    for (int rowNum = 1; rowNum <= MAX_NUMBER_OF_WORDS
        && override != 2; rowNum++) {
        override = 0;
        for (int columnNum = 1; columnNum <= MAX_WORD_LENGTH
            && override == 0; columnNum++) {
            paragraph = moveToBeginningOfNextToken(paragraph);
            tokens[rowNum - 1][columnNum - 1] = *paragraph++;
            if (*paragraph == ' ' || !*paragraph) {
                tokens[rowNum - 1][columnNum] = '\0';
                paragraph = moveToBeginningOfNextToken(paragraph);
                override = 1;
                wordCounter++;
            }

            if (*paragraph == '\0') {
                override = 2;
            }
        }
    }

    return wordCounter;

}

int getNumberOfWordsForNextLine(char
        tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int
        numberOfWordsProcessedSoFar, int totalNumberOfWords, int lineLength) {

    int override = 0;
    int lineCounter = 0;
    int wordCounter = numberOfWordsProcessedSoFar;
    int remainingSpaces;

    for (int i = 0; i < lineLength & override == 0; i++){
        lineCounter = lineCounter + getCurrentTokenSize(tokens[wordCounter]);
        wordCounter++;

        remainingSpaces = lineLength - lineCounter;
        if (remainingSpaces <= (getCurrentTokenSize(tokens[wordCounter]))
            + (wordCounter - numberOfWordsProcessedSoFar - 1)) {
            override = 1;
        }

        if (wordCounter >= totalNumberOfWords) {
            override = 1;
        }

    }

    return wordCounter - numberOfWordsProcessedSoFar;

}

void formatAndPrintCurrentLine(char
        tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int
        numberOfWordsProcessedSoFar, int numberOfWordsOnNextLine,
        int lineLength) {

    int characterCount = 0;

    for (int i = 0; i < numberOfWordsOnNextLine; i++) {
        characterCount = characterCount
                + getCurrentTokenSize
                    (tokens[numberOfWordsProcessedSoFar + i]);
    }

    int spacesForNextWord;
    char lineString[200] = "";
    int remainingBlankSpacesBetweenWords = numberOfWordsOnNextLine - 1;

    for (int j = 0; j < numberOfWordsOnNextLine; j++) {
        strcat(lineString, tokens[numberOfWordsProcessedSoFar + j]);
        if (remainingBlankSpacesBetweenWords == 0) {
            spacesForNextWord = 0;
        } else {
            spacesForNextWord = ceil((double) (lineLength - characterCount)
                                     / remainingBlankSpacesBetweenWords);
        }
        characterCount = characterCount + spacesForNextWord;
        remainingBlankSpacesBetweenWords--;
        for (int k = 0; k < spacesForNextWord; k++) {
            strcat(lineString, " ");
        }
    }

    printf("%s\n", lineString);

}

void formatAndPrintParagraph(char *paragraph, int lineLength) {
    char tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH] = {0};

    int totalNumberOfWords = tokenize(paragraph, tokens);
    int numberOfWordsProcessedSoFar = 0;

    int totalNumberOfWordsForLineCount = totalNumberOfWords;
    int lineCount = 0;
    int numberOfWordsProcessedForLineCount = 0;

    while (totalNumberOfWordsForLineCount > 0) {
        totalNumberOfWordsForLineCount = totalNumberOfWordsForLineCount
                - getNumberOfWordsForNextLine
                (tokens, numberOfWordsProcessedForLineCount,
                 totalNumberOfWords, lineLength);
        numberOfWordsProcessedForLineCount = numberOfWordsProcessedForLineCount
                + getNumberOfWordsForNextLine
                (tokens, numberOfWordsProcessedForLineCount,
                 totalNumberOfWords, lineLength);
        lineCount++;
    }

    for (int k = 0; k < lineCount; k++) {
        formatAndPrintCurrentLine
        (tokens, numberOfWordsProcessedSoFar,getNumberOfWordsForNextLine
        (tokens,numberOfWordsProcessedSoFar,totalNumberOfWords,lineLength)
        ,lineLength);

        numberOfWordsProcessedSoFar = numberOfWordsProcessedSoFar
                + getNumberOfWordsForNextLine
                (tokens,numberOfWordsProcessedSoFar,totalNumberOfWords,
                 lineLength);
    }

}

int main() {

    char paragraph[] = "         Hi everyone. This is          "
                       " the 2nd assignment. "
                       "Please make sure you start early as this "
                       "is going to take some time!     ";

    char paragraphTest1[] = "This.                  HAS         HUGE       "
                            "SPACES";

    char paragraphTest2[] = "                ";

    char paragraphTest3[] = "Lorem ipsum dolor sit amet, consectetur "
                            "adipiscing elit. Vivamus aliquam leo rutrum, "
                            "imperdiet neque et, pharetra lectus. Vestibulum"
                            " nec euismod arcu. Aliquam ac arcu laoreet, "
                            "semper dolor sed, faucibus tellus. Nunc volutpat"
                            " vulputate libero sit amet efficitur. Maecenas "
                            "est augue, pulvinar ut ornare sed, interdum eu "
                            "arcu. Praesent non risus at arcu tristique "
                            "aliquet. Ut quis sagittis nunc, a scelerisque ante."
                            "Curabitur faucibus nisl dui, quis imperdiet "
                            "nisi sagittis nec. Suspendisse faucibus mauris "
                            "ut semper gravida. Fusce a suscipit dui. Integer "
                            "in commodo eros. Quisque faucibus libero odio, "
                            "eget pulvinar ante rhoncus sit amet. Vestibulum "
                            "ac fermentum sapien, ac interdum purus. Donec "
                            "eget blandit dui, tincidunt pulvinar dolor. "
                            "Integer mauris nisl, dictum nec nunc at, "
                            "sodales aliquet odio. Donec scelerisque.";

    char paragraphTest4[] = "...!!!!??????  hi            ";

    char paragraphTest5[] = "this.has.no.spaces";

    printf("Beginning paragraph tests");
    printf("\n");
    printf("---------------------------------------------");
    printf("\n");

    formatAndPrintParagraph(paragraph, 1);
    printf("\n");
    formatAndPrintParagraph(paragraph, 6);
    printf("\n");
    formatAndPrintParagraph(paragraph, 15);
    printf("\n");
    formatAndPrintParagraph(paragraph, 20);
    printf("\n");
    formatAndPrintParagraph(paragraph, 25);
    printf("\n");
    formatAndPrintParagraph(paragraph, 35);
    printf("\n");
    formatAndPrintParagraph(paragraph, 100);
    printf("\n");
    formatAndPrintParagraph(paragraph, 120);
    printf("\n");

    formatAndPrintParagraph(paragraphTest1, 20);
    printf("\n");

    formatAndPrintParagraph(paragraphTest2, 20);
    printf("\n");

    formatAndPrintParagraph(paragraphTest3, 50);
    printf("\n");

    formatAndPrintParagraph(paragraphTest4, 10);
    printf("\n");

    formatAndPrintParagraph(paragraphTest5, 40);
    printf("\n");

    printf("---------------------------------------------");
    printf("\n");
    printf("Paragraph tests concluded.\n\n");

    printf("Testing creation of testTokens array...\n");
    printf("\n");

    char testTokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH];
    int tokensTest = tokenize(paragraph, testTokens);

    printf("Asserting that number of tokens in test array is "
           "equal to 21...\n");
    printf("\n");
    assert (tokensTest == 21);
    printf("testTokens array created with an expected length of 21.\n");
    printf("\n");

    printf("Printing testTokens array for validation.\n");

    for (int i = 0; i < tokensTest; i++) {
        printf("Token[%d] = %s\n", i, testTokens[i]);
    }
    printf("\n");

    return 0;

}
