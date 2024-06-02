//
// Created by 86158 on 2024/5/29.
//

#include "prompt.h"

void getPrompt(char* prompt) {
    gethostname(prompt, PROMPT_MAX_SIZE);
}
