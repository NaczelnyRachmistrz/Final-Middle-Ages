 /** @file
    Interface of parser.

 */

#ifndef PARSE_H
#define PARSE_H


/**
 * Data structure with parsed input line.
 **/
typedef struct defCommand {
    char name[16]; /**< Type of command. */
    int data[7]; /**< Points required with a command. */
} Command;


/** 
 * Reads a command.
 **/
void readCommand(char* inputLine);

/**
 * Parses a command and returns
 * a structure with data points.
 **/
Command parseCommand();
 
#endif /* PARSE_H */
