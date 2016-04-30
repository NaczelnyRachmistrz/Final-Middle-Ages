#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

static const char *commands[] = {
    "INVALID_INPUT",
    "INIT",
    "MOVE",
    "PRODUCE_KNIGHT",
    "PRODUCE_PEASANT",
    "END_TURN"
};

static void copyArray(int ** toArray, int ** fromArray, int count) {
    while (count > 0) {
        count--;
        *toArray[count] = *fromArray[count];
    }
}

Command * newCommand(enum CommandType type, int * args, int argc) {
    Command * command = (Command *) malloc(sizeof(struct DefCommand));
    command->type = type;
    copyArray(&command->arguments, &args, argc);
    return command;
}

void removeCommand(Command * command) {
    free(command);
}

static char* readLine() {
    size_t length = 0;
    size_t bufferSize = MAX_COMMAND_LENGTH + 2;
    char * buffer = malloc(sizeof(char) * bufferSize);

    int character;

    while (EOF != (character = fgetc(stdin)) && character != '\n') {
        if (length == bufferSize){
            continue;
        }
        buffer[length++] = character;
    }

    buffer[length++] = '\0';
    return (char *) realloc(buffer, sizeof(char) * length);
}

static int parseCommandType(char *text, enum CommandType * commandType) {
    for (int i = 0; i < COMMANDS_COUNT; i++) {
        if (strcmp(commands[i], text) == 0) {
            *commandType = (enum CommandType) i;
            return 0;
        }
    }
    return 1;
}

static int parseCommandArguments(char *text, int ** commandArguments, int * commandArgumentsCount) {
    printf("ARGUMENTS [%s]\n", text);
    return 1;
}

static Command * parseCommand(char * text) {
    enum CommandType commandType;
    int commandArguments[MAX_ARGUMENTS_COUNT];
    int commandArgumentsCount;

    char * commandText = (char *) malloc(sizeof(char) * MAX_COMMAND_LENGTH);
    char * commandArgumentsText = (char *) malloc(sizeof(char) * MAX_COMMAND_LENGTH);

    if (sscanf(text, "%s%[^\n]", commandText, commandArgumentsText) != 2) {
        return newCommand(INVALID, NULL, 0);
    }

    if (parseCommandType(commandText, &commandType)) {
        return newCommand(INVALID, NULL, 0);
    }

    if (parseCommandArguments(commandArgumentsText, &commandArguments, &commandArgumentsCount)) {
        return newCommand(INVALID, NULL, 0);
    }

    Command * command = newCommand(commandType, commandArguments, commandArgumentsCount);

    free(text);
    free(commandText);
    free(commandArgumentsText);

    return command;
}

Command* getCommandFromInput() {
    char * commandText = readLine();
    return parseCommand(commandText);
}
