#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

static const char *commands[] = {
    "INIT",
    "MOVE",
    "PRODUCE_KNIGHT",
    "PRODUCE_PEASANT",
    "END_TURN",
    "INVALID_INPUT"
};

static void copyArguments(int * toArray, int * fromArray, int count) {
    for (int i = MAX_ARGUMENTS_COUNT - 1; i >= count; i--) {
        toArray[i] = -1;
    }
    while (count > 0) {
        toArray[--count] = fromArray[count];
    }
}

Command * newCommand(enum CommandType type, int * commandArguments, int commandArgumentsCount) {
    Command * command = (Command *) malloc(sizeof(Command));
    command->type = type;
    copyArguments(command->arguments, commandArguments, commandArgumentsCount);
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

static int intLength(int a) {
    int n = 0;
    while (a > 0) {
        n++;
        a /= 10;
    }
    return n;
}

static int parseCommandArguments(char *text, int * commandArguments, int * commandArgumentsCount) {
    int argument, argumentLength;
    *commandArgumentsCount = 0;

    while (strlen(text) > 0) {
        if (text[0] != ' ') {
            return 1;
        }
        text++;

        if (sscanf(text, "%d", &argument) != 1) {
            return 1;
        }
        argumentLength = intLength(argument);
        text += argumentLength;

        commandArguments[(*commandArgumentsCount)++] = argument;
    }
    return 0;
}

static Command * parseCommand(char * text) {
    Command * command;

    enum CommandType commandType;
    int commandArguments[MAX_ARGUMENTS_COUNT];
    int commandArgumentsCount;

    char * commandText = (char *) malloc(sizeof(char) * MAX_COMMAND_LENGTH);
    char * commandArgumentsText = (char *) malloc(sizeof(char) * MAX_COMMAND_LENGTH);

    int sscanfResult = sscanf(text, "%s%[^\n]", commandText, commandArgumentsText);

    if (sscanfResult == 1) {
        if (parseCommandType(commandText, &commandType)) {
            command = newCommand(INVALID_INPUT, NULL, 0);
        } else {
            command = newCommand(commandType, commandArguments, 0);
        }
    } else if (sscanfResult == 2) {
        if (parseCommandType(commandText, &commandType)
        || parseCommandArguments(commandArgumentsText, commandArguments, &commandArgumentsCount)) {
            command = newCommand(INVALID_INPUT, NULL, 0);
        } else {
            command = newCommand(commandType, commandArguments, commandArgumentsCount);
        }
    } else {
        command = newCommand(INVALID_INPUT, NULL, 0);
    }

    free(text);
    free(commandText);
    free(commandArgumentsText);
    return command;
}

Command* getCommandFromInput() {
    char * commandText = readLine();
    return parseCommand(commandText);
}
