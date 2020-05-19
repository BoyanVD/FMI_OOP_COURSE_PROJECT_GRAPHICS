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
    // for (Command command : currentSession->getSessionCommands())
    // {
    //     command.print();
    // }

    // for (ImageFile* item : currentSession->getSessionItems())
    // {
    //     item->print();
    // }
}

void Application::load(const Command& command)
{
    if (currentSession != nullptr)
    {
        std::cout << "You already have session loaded ! If you want to start new one, please use 'switch' command." << std::endl;
        return;
    }

    unsigned sessionId = generateUniqueId();
    Session* session = new Session(sessionId);

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
    // session->addCommand(command);

    this->sessions.push_back(session);
    this->currentSession = session;

    std::cout << "Session with ID: " << session->getId() << " started" << std::endl;
}

void Application::addImage(const Command& command)
{
    size_t numberOfParameters = command.getNumberOfParameters();
    if (numberOfParameters > 1)
    {
        std::cout << "Add image command accepts only one parameter !" << std::endl;
        return;
    }

    if (currentSession == nullptr)
    {
        std::cout << "There is currently no active session !" << std::endl;
        return;
    }

    ImageFile* item = ImageFileFactory::generate(command.getParameter(0));
    currentSession->addItem(item);
    std::cout << "Image '" << item->getFilename() << "' added" << std::endl;
}

void Application::imageTransformation(const Command& command)
{
    size_t numberOfParameters = command.getNumberOfParameters();
    if (numberOfParameters > 0)
    {
        std::cout << "Transformation commands doesn not take arguments !" << std::endl;
        return;
    }

    if (currentSession == nullptr)
    {
        std::cout << "There is currently no active session !" << std::endl;
        return;
    }

    currentSession->addTransformation(command);
}

void Application::sessionInfo(const Command& command)
{
    if (this->currentSession == nullptr)
    {
        std::cout << "There is currently no active session !" << std::endl;
        return;
    }

    this->currentSession->print();

}

void Application::switchSession(const Command& command)
{
    size_t numberOfParameters = command.getNumberOfParameters();
    if (numberOfParameters > 1)
    {
        std::cout << "Add image command accepts only one parameter !" << std::endl;
        return;
    }

    if (this->currentSession == nullptr)
    {
        std::cout << "There is currently no active session !" << std::endl;
        return;
    }

    int id = 0;
    try
    {
        id = std::stoi(command.getParameter(0));
    }
    catch(const std::invalid_argument& ia)
    {
        std::cout << "Invalid argument !" << std::endl;
        return;
    }

    if (id == 0)
        return;

    for (Session* session : this->sessions)
    {
        if (session->getId() == id)
        {
            this->currentSession = session;
            return;
        }
    }

    std::cout << "No session with ID : " << id << std::endl;
}

void Application::collage(const Command& command)
{
    if (this->currentSession == nullptr)
    {
        std::cout << "There is currently no active session !" << std::endl;
        return;
    }

    size_t numberOfParameters = command.getNumberOfParameters();
    if (numberOfParameters != 4)
    {
        std::cout << "Collage command expects exactly 4 parameters !" << std::endl;
        return;
    }

    ImageFile* image = ImageFile::collage(command.getParameter(0), command.getParameter(1), command.getParameter(2), command.getParameter(3));
    image->write();
}

void Application::save(const Command& command)
{
    if (this->currentSession == nullptr)
    {
        std::cout << "There is currently no active session !" << std::endl;
        return;
    }

    size_t numberOfParameters = command.getNumberOfParameters();
    if (numberOfParameters != 0)
    {
        std::cout << "Save command doesnt require parameters !" << std::endl;
        return;
    }

    this->currentSession->save();
}

void Application::saveas(const Command& command)
{
    if (this->currentSession == nullptr)
    {
        std::cout << "There is currently no active session !" << std::endl;
        return;
    }

    size_t numberOfParameters = command.getNumberOfParameters();
    if (numberOfParameters != 1)
    {
        std::cout << "Saveas command requires exactly 1 parameter !" << std::endl;
        return;
    }

    this->currentSession->changeFirstItemName(command.getParameter(0));
    this->currentSession->save();
}

void Application::run()
{
    std::string input = "load ./files/apollonian_gasket.ascii.pgm";
    Command command(input);
    load(input);
    printSessions();
}

#endif