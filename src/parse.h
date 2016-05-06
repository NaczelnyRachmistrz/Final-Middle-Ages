/**
 * @file parse.h
 * Reading input from stdin and parsing it into a Command
 */
#ifndef MIDDLE_AGES_PARSE_H
#define MIDDLE_AGES_PARSE_H

/**
 * @brief Number of available commands
 * @see CommandType
 */
#define COMMANDS_COUNT 5

/**
 * Maximum length of correct command with parameters
 */
#define MAX_COMMAND_LENGTH 100

/**
 * Maximum arguments in correct command
 * @see Command
 */
#define MAX_ARGUMENTS_COUNT 7

/**
 * Available command types
 * @see Command
 */
enum CommandType {
    INIT,
    MOVE,
    PRODUCE_KNIGHT,
    PRODUCE_PEASANT,
    END_TURN,
    INVALID_INPUT
};

/**
 * Structure containing type and arguments
 * @see getCommandFromInput
 * @see removeCommand
 */
typedef struct {
    enum CommandType type; /**< type of the command */
    long args[MAX_ARGUMENTS_COUNT];/**< additional parameters */
} Command;

/**
 * @brief Reads and parses line from stdin
 *
 * Reads characters from stdin up to '\n'
 * lines longer than MAX_COMMAND_LENGTH are truncated and INVALID_COMMAND is returned
 * @return Pointer to parsed command
 */
Command * getCommandFromInput();

/**
 * Destructor for command
 * @param command command to be removed
 */
void removeCommand(Command * command);

#endif
