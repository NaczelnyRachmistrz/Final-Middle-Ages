#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "parse.h"

static const char * commands[] = {
    "INIT",
    "MOVE",
    "PRODUCE_KNIGHT",
    "PRODUCE_PEASANT",
    "END_TURN",
    "INVALID_INPUT"
};

static const int properCommandArgumentsCount[] = {
    7, // INIT
    4, // MOVE
    4, // PRODUCE_KNIGHT
    4, // PRODUCE_PEASANT
    0  // INVALID_INPUT
};

static bool hasValidArgumentsCount(enum CommandType commandType, int commandArgumentsCount) {
    if (commandType == INVALID_INPUT) {
        return true;
    } else {
        return properCommandArgumentsCount[commandType] == commandArgumentsCount;
    }
}

static void copyArguments(long * toArray, long * fromArray, int count) {
    assert(count >= 0 && count <= MAX_ARGUMENTS_COUNT);
    while (count > 0) {
        count--;
        toArray[count] = fromArray[count];
    }
}

Command * newCommand(enum CommandType type, long * commandArguments, int commandArgumentsCount) {
    Command * command = (Command *) malloc(sizeof(Command));

    if (hasValidArgumentsCount(type, commandArgumentsCount)) {
        command->type = type;
        copyArguments(command->args, commandArguments, commandArgumentsCount);
    } else {
        command->type = INVALID_INPUT;
    }

    return command;
}

static char* readLine() {
    size_t length = 0;
    size_t bufferSize = MAX_COMMAND_LENGTH + 2;
    char * buffer = malloc(sizeof(char) * bufferSize);

    int character;

    while (EOF != (character = fgetc(stdin)) && character != '\n') {
        if (length == bufferSize) {
            continue;
        }
        buffer[length++] = (char)character;
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

static int numberLength(long a) {
    int n = 0;
    while (a > 0) {
        n++;
        a /= 10;
    }
    return n;
}

static int parseCommandArguments(char *text, long * commandArguments, int * commandArgumentsCount) {
    long argument;
    *commandArgumentsCount = 0;

    while (strlen(text) > 0) {
        if (text[0] != ' ') {
            return 1;
        } else if (sscanf(++text, "%ld", &argument) != 1) {
            return 1;
        }
        text += numberLength(argument);
        commandArguments[(*commandArgumentsCount)++] = argument;
    }

    return 0;
}

static Command * parseCommand(char * text) {
    Command * command;

    enum CommandType commandType;
    long commandArguments[MAX_ARGUMENTS_COUNT];
    int commandArgumentsCount = 0;

    char * commandText = (char *) malloc(sizeof(char) * MAX_COMMAND_LENGTH);

    if (sscanf(text, "%s", commandText) != 1
        || parseCommandType(commandText, &commandType)
        || parseCommandArguments(text + strlen(commandText), commandArguments, &commandArgumentsCount)) {
        command = newCommand(INVALID_INPUT, NULL, 0);
    } else {
        command = newCommand(commandType, commandArguments, commandArgumentsCount);
    }

    free(text);
    free(commandText);
    return command;
}

Command * getCommandFromInput() {
    char * commandText = readLine();
    return parseCommand(commandText);
}

void removeCommand(Command * command) {
    free(command);
}