#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

#define MAX_COMMAND_LENGTH 101

static const char *commands[] = {
        "INIT",
        "MOVE",
        "PRODUCE_KNIGHT",
        "PRODUCE_PEASANT",
        "END_TURN"
};

command* parse_command() {
    char* command_name = read_input();
}

char* read_input() {
    size_t buffer_size = MAX_COMMAND_LENGTH;
    size_t length = 0;

    char *buffer;
    int input;

    buffer = realloc(NULL, sizeof(char) * buffer_size);
    if (!buffer) {
        return buffer;
    }

    while ((input = fgetc(stdin)) != EOF && input != '\n') {
        buffer[length++] = input;
        if (length == buffer_size){
            buffer = realloc(buffer, sizeof(char) * (buffer_size += 16));
            if (!buffer) {
                return buffer;
            }
        }
    }
    buffer[length++] = '\0';
    return realloc(buffer, sizeof(char) * length);
}
