/**
 * \class Command
 *
 * \brief Class, representing user input.
 *
 * Command class is used to parse and wrap user input in
 * format expected by Application.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __COMMAND_H
#define __COMMAND_H

#include <iostream>
#include <vector>
#include <string>

/**
 * @param command stores the name of the command
 * @param parameters stores parsed parameters.
 */
class Command
{
private:
    std::string command;
    std::vector<std::string> parameters;

    /**
     * Parses string and sets class fields.
     * 
     * @param input user input string.
     */
    void parseInput(std::string input);

public:
    Command(std::string input);
    Command(const Command &other);

    /**
     * Gets command name.
     * 
     * @return command name.
     */
    std::string getCommand() const;

    /**
     * Gets parameter at index given.
     * 
     * @return parameter at index
     */
    std::string getParameter(unsigned index) const;

    /**
     * Gets the number of command parameters.
     * 
     * @return number of command parameters
     */
    size_t getNumberOfParameters() const;

    /**
     * Prints command.
     */
    void print();
};

#endif