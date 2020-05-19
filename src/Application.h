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
    void addImage(const Command& command);
    void sessionInfo(const Command& command); // Argument used only in order to fit the Application methods format
    void switchSession(const Command& command);

    void collage(const Command& command);// this method is different than other transformation, and it will be performed immediately
    void imageTransformation(const Command& command);

    void save(const Command& command);
    void saveas(const Command& command);

    // void grayscale();
    // void monochrome();
    // void negative();
    // void rotate(const Command& command);




    void printSessions();
public:
    Application() : currentSession(nullptr) {}

    void run();
};

#endif