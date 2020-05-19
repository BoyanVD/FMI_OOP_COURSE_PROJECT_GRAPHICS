#ifndef __SESSION_H
#define __SESSION_H

#include <iostream>
#include <vector>

#include "ImageFile.h"
#include "Command.h"

class Session
{
private:
    struct SessionItem
    {
        ImageFile* image;
        std::vector<std::string> imageTransformations;

        SessionItem(const ImageFile* img, const std::vector<std::string>& transformations) :
        image(img->clone()), imageTransformations(transformations) {}

        void executeAll()
        {
            for (std::string transformation : imageTransformations)
            {
                image->executeTransformation(transformation);
            }
        }

        void print() const
        {
            std::cout << "Image : " << image->getFilename() << std::endl;
            std::cout << "Transformations to be done on image : " << std::endl;
            for (std::string transformation : imageTransformations)
            {
                std::cout << transformation << std::endl;
            }
        }
    };

    unsigned sessionId;
    // std::vector<ImageFile*> sessionItems;
    // std::vector<Command> sessionCommands;
    std::vector<SessionItem> sessionItems;
public:
    Session(unsigned _sessionId) : sessionId(_sessionId) {};

    void addItem(ImageFile* item)
    {
        // this->sessionItems.push_back(item);
        SessionItem sessionItem(item, {});
        this->sessionItems.push_back(sessionItem);
    }

    void addTransformation(Command command)
    {
        // this->sessionCommands.push_back(command);
        for (SessionItem item : sessionItems)
        {
            item.imageTransformations.push_back(command.getCommand());
        }
    }

    unsigned getId()
    {
        return this->sessionId;
    }

    void undo() // 
    {
        // this->sessionCommands.pop_back();
        for (SessionItem item : sessionItems)
        {
            item.imageTransformations.pop_back();
        }
    }

    void save()
    {
        for (SessionItem item : sessionItems)
        {
            item.image->write();
        }
    }

    void changeFirstItemName(const std::string& newName)
    {
        if (this->sessionItems.size() == 0)
        {
            std::cout << "There are no session items !" << std::endl;
            return;
        }
        this->sessionItems[0].image->setFilename(newName);
    }

    void executeAllTransformations()
    {
        for (SessionItem item : this->sessionItems)
        {
            item.executeAll();
        }
    }

    bool operator < (Session other) // needed for <algorithm> sort function
    {
        return this->sessionId < other.sessionId;
    }

    void print()
    {
        std::cout << "Session ID : " << sessionId << std::endl;

        for (SessionItem item : sessionItems)
        {
            item.print();
        }
    }
};

#endif