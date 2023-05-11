#include "WordFrequency.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "pointerCheck.h"
#include "list.h"

#define BUF_SIZE 16

void WordFrequencyFuncSplitWordByDelim(char *newInputString, struct List_T **head)
{
   char *delim = " ";
    char *word = strtok(newInputString, delim);

    while (NULL != word) {
        struct Input_T *newWord = InputNew(word);
        if (NULL != newWord) {
            struct List_T *tail = ListNew(newWord);
            *head = ListAppend(*head, tail);
        }
        word = strtok(NULL, delim);
    }


    free(newInputString);
    newInputString = NULL;    
}

char *WordFrequencyFunc(const char *input)
{
    CHECK_NULL_RETURN_NULL(input);
    char *newInputString = (char *)malloc(strlen(input) + 1);
    CHECK_NULL_RETURN_NULL(newInputString);
    strcpy(newInputString, input);

    struct List_T *head = NULL;
    WordFrequencyFuncSplitWordByDelim(newInputString, &head);

    struct List_T *countedList = NULL;
    List *current = head;
    do {
        struct Input_T *newWord = (struct Input_T *)ListGet(current);
        if (NULL != newWord) {
            struct List_T *exist = ListFind(countedList, newWord, InputWordEqual);
            if (NULL != exist) {
                struct Input_T *oldWord = (struct Input_T *)ListGet(exist);
                int currentCount = InputGetWordCount(oldWord) + 1;
                InputSetWordCount(oldWord, currentCount);
                InputFree(&newWord);
            } else {
                struct List_T *tail = ListNew(newWord);
                countedList = ListAppend(countedList, tail);
            }
        }
        current = ListNext(current);
    } while (NULL != current);
    ListFree(&head);

    if (NULL != countedList) {
        countedList = ListSort(countedList, InputCountCompare);
    }

    char *resultString = (char *)malloc(BUF_SIZE);
    if (NULL != resultString) {
        memset(resultString, 0, BUF_SIZE);
        char *lineString = (char *)malloc(BUF_SIZE);
        if (NULL != lineString) {
            current = countedList;
            while (NULL != current) {
                Input *input_T = (Input *)ListGet(current);
                snprintf(lineString, BUF_SIZE, "%s %d", InputGetWord(input_T), InputGetWordCount(input_T));
                if (strlen(resultString) + strlen(lineString) + 1 >= BUF_SIZE) {
                    free(lineString);
                    lineString = NULL;
                    free(resultString);
                    resultString = NULL;
                    return "";
                }
                strncat(resultString, lineString, BUF_SIZE);

                current = ListNext(current);
                if (NULL != current) {
                    strncat(resultString, "\n", BUF_SIZE);
                }
            }
        }
        free(lineString);
        lineString = NULL;
    }
    ListFree(&countedList);
    return resultString;
}