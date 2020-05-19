#ifndef __APPLICATION_CPP
#define __APPLICATION_CPP

#include "Application.h"
#include "Constants.h"
#include "ImageFileFactory.h"

#include <algorithm>

const std::map<std::string, Application::Function> Application::SUPPORTED_FUNCTIONS = {
    {"load", &Application::load},
    {"add", &Application::addImage},
    {"session_info", &Application::sessionInfo},
    {"switch", &Application::switchSession},
    {"collage", &Application::collage},
    {"image_transformation", &Application::imageTransformation},
    {"save", &Application::save},
    {"saveas", &Application::saveas},
    {"undo", &Application::undo}
};

Application::Function Application::getFunction(const std::string key)
{
    std::map<std::string, Application::Function>::const_iterator it = SUPPORTED_FUNCTIONS.find(key);
    if (it == SUPPORTED_FUNCTIONS.end())
    {
        return SUPPORTED_FUNCTIONS.find("image_transformation")->second; // image transformations validation is in ImageFile
    }

    return it->second;
}

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

    // std::cout << command.getCommand() << std::endl;
    currentSession->addTransformation(command);
}

void Application::undo(const Command& command)
{
    if (this->currentSession == nullptr)
    {
        std::cout << "There is currently no active session !" << std::endl;
        return;
    }

    size_t numberOfParameters = command.getNumberOfParameters();
    if (numberOfParameters != 0)
    {
        std::cout << "Undo command doesnt require parameters !" << std::endl;
        return;
    }

    this->currentSession->undo();
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

// @TODO Session must contain the images to collage
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

    std::string image1 = command.getParameter(1);
    std::string image2 = command.getParameter(2);
    if (!(this->currentSession->contains(image1) && this->currentSession->contains(image2)))
    {
        std::cout << "Images not loaded in current session !" << std::endl;
        return;
    }

    ImageFile* image = ImageFile::collage(command.getParameter(0), image1, image2, command.getParameter(3));
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

    this->currentSession->executeAllTransformations();
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

    // this->currentSession->changeFirstItemName(command.getParameter(0));
    this->currentSession->executeAllTransformations();
    this->currentSession->saveas(command.getParameter(0));
}

void Application::run()
{
    std::string input;
    do
    {
        std::cout << ">";
        getline(std::cin, input);
        
        Command command(input);
        Application::Function function = this->getFunction(command.getCommand());

        (this->*function)(command);

    } while (input != "exit");
    
    std::cout << "Thank you for using the system !" << std::endl;
}

#endif