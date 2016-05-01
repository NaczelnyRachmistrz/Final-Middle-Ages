#ifndef PARSE_H
#define PARSE_H

#define COMMANDS_COUNT 5
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS_COUNT 7

enum CommandType {
    INIT,
    MOVE,
    PRODUCE_KNIGHT,
    PRODUCE_PEASANT,
    END_TURN,
    INVALID
};

typedef struct {
    enum CommandType type;
    int arguments[MAX_ARGUMENTS_COUNT];
} Command;

Command * newCommand(enum CommandType type, int * commandArguments, int commandArgumentsCount);
void removeCommand(Command * command);

Command * getCommandFromInput();

#endif
