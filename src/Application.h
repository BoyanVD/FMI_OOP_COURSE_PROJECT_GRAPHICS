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
    typedef void (Application::*Function)(const Command&);
    static const std::map<std::string, Function> SUPPORTED_FUNCTIONS;

    std::istream& inputStream;
    std::ostream& logStream;

    std::vector<Session*> sessions;
    Session* currentSession; // points to one of sessions items

    unsigned generateUniqueId();

    Function getFunction(const std::string key);

    void load(const Command& command);
    void addImage(const Command& command);
    void sessionInfo(const Command& command); // Argument used only in order to fit the Application methods format
    void switchSession(const Command& command);

    void collage(const Command& command);// this method is different than other transformation, and it will be performed immediately
    void imageTransformation(const Command& command);

    void save(const Command& command);
    void saveas(const Command& command);
    void undo(const Command& command);

    void printSessions();
public:
    Application(std::istream& _inputStream, std::ostream& _logStream) : 
    inputStream(_inputStream), logStream(_logStream), currentSession(nullptr) {}

    void run();

    ~Application()
    {
        for (Session* session : this->sessions)
        {
            delete session;
        }
    }
};

#endif