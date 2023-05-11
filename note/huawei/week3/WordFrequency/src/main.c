#include <stdio.h>
#include <stdlib.h>
#include "WordFrequency.h"
#include "input.h"
#include "pointerCheck.h"

int main()
{
    char* wordString = WordFrequencyFunc("the the is");
    if(NULL != wordString){
        printf("%s\n", wordString);
        free(wordString);
    }
    return EXIT_SUCCESS;
}
