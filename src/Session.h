#ifndef __SESSION_H
#define __SESSION_H

#include <iostream>
#include <vector>

#include "ImageFile.h"
#include "Command.h"

class Session
{
private:
    unsigned sessionId;
    std::vector<ImageFile*> sessionItems;
    std::vector<Command> sessionCommands;
public:
    Session(unsigned _sessionId) : sessionId(_sessionId) {};

    void addItem(ImageFile* item)
    {
        this->sessionItems.push_back(item);
    }

    void addCommand(Command command)
    {
        this->sessionCommands.push_back(command);
    }

    unsigned getId()
    {
        return this->sessionId;
    }

    std::vector<Command> getSessionCommands()
    {
        return this->sessionCommands;
    }

    std::vector<ImageFile*> getSessionItems()
    {
        return this->sessionItems;
    }

    bool operator < (Session other) // needed for <algorithm> sort function
    {
        return this->sessionId < other.sessionId;
    }

    void print()
    {
        std::cout << "Session ID : " << sessionId << std::endl;
        std::cout << "Session commands : " << std::endl;
        for (Command c : sessionCommands)
        {
            c.print();
        }

        std::cout << "Session file items : " << std::endl;
        for (ImageFile* file : sessionItems)
        {
            file->print();
        }
    }
};

#endif