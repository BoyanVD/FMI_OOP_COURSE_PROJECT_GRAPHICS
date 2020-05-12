#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"
#include "Session.h"
#include "Command.h"

/*
* Works with ASCII file format
*/
class Application
{
private:
    std::vector<Session*> sessions;
    Session* currentSession; // points to one of sessions items

    unsigned generateUniqueId();

    void load(const Command& command);

    void printSessions();
public:
    Application() : currentSession(nullptr) {}

    void run();
};

#endif