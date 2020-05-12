#ifndef __COMMAND_CPP
#define __COMMAND_CPP

#include "Command.h"
#include "Constants.h"

Command::Command(const Command &other)
{
    this->command = other.command;
    this->parameters.clear();
    for (int index = 0; index < other.getNumberOfParameters(); ++index)
    {
        this->parameters.push_back(other.getParameter(index));
    }
}

void Command::parseInput(std::string input)
{
    // size_t position = 0;
    // std::string current;
    // unsigned currentStringNumber = 0;

    // while ((position = input.find(INPUT_COMMAND_DELIMETER)) != std::string::npos) {
    //     current = input.substr(0, position);
    //     input.erase(0, position + INPUT_COMMAND_DELIMETER.length());
        
    //     if (currentStringNumber == 0)
    //         this->command = current;
    //     else 
    //         this->parameters.push_back(current);
        
    //     ++currentStringNumber;
    // }



    size_t current, previous = 0;
    current = input.find(INPUT_COMMAND_DELIMETER);
    unsigned numberOfParsedStrings = 0;

    while (current != std::string::npos) 
    {
        std::string currentStr = input.substr(previous, current - previous);
        if (numberOfParsedStrings == 0)
            this->command = currentStr;
        else 
            this->parameters.push_back(currentStr);

        previous = current + 1;
        current = input.find(INPUT_COMMAND_DELIMETER, previous);

        ++numberOfParsedStrings;
    }

    if (numberOfParsedStrings == 0)
            this->command = input.substr(previous, current - previous);
        else 
            this->parameters.push_back(input.substr(previous, current - previous));
}

#endif