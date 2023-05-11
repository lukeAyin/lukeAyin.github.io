#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "pointerCheck.h"

#define MAX_CHAR_IN_WORD 255

typedef struct Input_T {
    char word[MAX_CHAR_IN_WORD];
    int count;
} Input;

Input *InputNew(const char *word)
{
    Input *newInput = (Input *)malloc(sizeof(Input));
    CHECK_NULL_RETURN_NULL(newInput);

    memset(newInput, 0, sizeof(Input));
    strncpy(newInput->word, word, MAX_CHAR_IN_WORD);
    newInput->count = 1;

    return newInput;
}

char *InputGetWord(Input *input)
{
    CHECK_NULL_RETURN_NULL(input);
    return input->word;
}

int InputGetWordCount(Input *input)
{
    CHECK_NULL_RETURN_ZERO(input);
    return input->count;
}

void InputSetWordCount(Input *input, int count)
{
    CHECK_NULL_RETURN_VOID(input);
    input->count = count;
}

int InputCountCompare(void *inputA, void *inputB) {
    int result = ((Input *)inputA)->count - ((Input *)inputB)->count;
    return result;
}

bool InputWordEqual(void *inputA, void *inputB) {
    if (0 == strncmp(((Input *)inputA)->word, ((Input *)inputB)->word, MAX_CHAR_IN_WORD)) {
        return true;
    } else {
        return false;
    }
}

void InputFree(Input **input)
{
    CHECK_NULL_RETURN_VOID(input);
    CHECK_NULL_RETURN_VOID(*input);
    free(*input);
    *input = NULL;
}