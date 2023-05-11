#ifndef INPUT_H__
#define INPUT_H__

#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct Input_T Input;

Input *InputNew(const char *word);
char *InputGetWord(Input *input);
int InputGetWordCount(Input *input);
void InputSetWordCount(Input *input, int count);
int InputCountCompare(void *inputA, void *inputB);
bool InputWordEqual(void *inputA, void *inputB);
void InputFree(Input **input);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* INPUT_H__ */