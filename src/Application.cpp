#ifndef __APPLICATION_CPP
#define __APPLICATION_CPP

#include "Application.h"
#include "Constants.h"
#include "ImageFileFactory.h"

#include <algorithm>

unsigned Application::generateUniqueId()
{
    sort(this->sessions.begin(), this->sessions.end());
    unsigned id = INITIAL_SESSION_ID;
    for(Session* session : sessions)
    {
        if (session->getId() == id)
            ++id;
    }

    return id;
}

void Application::printSessions()
{
    std::cout << "Current session : " << currentSession->getId() << std::endl;
    std::cout << "Session commands : " << std::endl;
    for (Command command : currentSession->getSessionCommands())
    {
        command.print();
    }

    for (ImageFile* item : currentSession->getSessionItems())
    {
        item->print();
    }
}

void Application::load(const Command& command)
{
    unsigned sessionId = generateUniqueId();
    Session* session = new Session(sessionId);
    session->addCommand(command);

    size_t numberOfParameters = command.getNumberOfParameters();
    for (int index = 0; index < numberOfParameters; ++index)
    {
        ImageFile* item = ImageFileFactory::generate(command.getParameter(index));
        if (item == nullptr)
        {
            std::cout << "Invalid filepath for command : " << command.getCommand() << std::endl;
            std::cout << "For filepath : " << (index + 1) << std::endl;

            continue;
        }

        item->open();
        session->addItem(item);
    }

    this->sessions.push_back(session);
    this->currentSession = session;

    std::cout << "Session with ID: " << session->getId() << " started" << std::endl;
}

void Application::run()
{
    std::string input = "load ./files/6colour_ppma.ppm";
    Command command(input);
    load(input);
    printSessions();
}

#endif