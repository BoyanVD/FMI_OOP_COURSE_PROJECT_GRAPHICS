#ifndef __SESSION_H
#define __SESSION_H

#include <iostream>
#include <vector>

#include "ImageFile.h"
#include "Command.h"
#include "ImageFileFactory.h"

class Session
{
private:
    struct SessionItem
    {
        // Think of smart pointers
        ImageFile* image;
        std::vector<std::string> imageTransformations;

        SessionItem(const ImageFile* img, const std::vector<std::string>& transformations) :
        image(img->clone()), imageTransformations(transformations) {}

        ~SessionItem()
        {
            delete image;
        }

        void executeAll()
        {
            for (std::string transformation : imageTransformations)
            {
                // std::cout << transformation << std::endl;
                image->executeTransformation(transformation);
            }

            imageTransformations.clear();
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
    std::vector<SessionItem*> sessionItems;
public:
    Session(unsigned _sessionId) : sessionId(_sessionId) {};

    void addItem(ImageFile* item)
    {
        // this->sessionItems.push_back(item);
        // SessionItem sessionItem(item, {});

        this->sessionItems.push_back(new SessionItem(item, {}));
    }

    void addTransformation(const Command& command)
    {
        // this->sessionCommands.push_back(command);
        for (SessionItem* item : sessionItems)
        {
            item->imageTransformations.push_back(command.getCommand());
        }
    }

    unsigned getId()
    {
        return this->sessionId;
    }

    void undo() // 
    {
        for (SessionItem* item : sessionItems)
        {
            item->imageTransformations.pop_back();
        }
    }

    void save()
    {
        for (SessionItem* item : sessionItems)
        {
            item->image->write();
        }
    }

    void saveas(const std::string& newName)
    {
        if (this->sessionItems.size() == 0)
        {
            std::cout << "There are no session items !" << std::endl;
            return;
        }

        std::string oldName = this->sessionItems[0]->image->getFilename();
        this->sessionItems[0]->image->setFilename(newName);

        this->save();

        this->sessionItems[0]->image = ImageFileFactory::generate(oldName);
        this->sessionItems[0]->image->open();
    }

    // void changeFirstItemName(const std::string& newName)
    // {
    //     if (this->sessionItems.size() == 0)
    //     {
    //         std::cout << "There are no session items !" << std::endl;
    //         return;
    //     }
    //     this->sessionItems[0].image->setFilename(newName);
    // }

    void executeAllTransformations()
    {
        for (SessionItem* item : sessionItems)
        {
            item->executeAll();
        }
    }

    bool operator < (Session other) // needed for <algorithm> sort function
    {
        return this->sessionId < other.sessionId;
    }

    void print()
    {
        std::cout << "Session ID : " << sessionId << std::endl;

        for (SessionItem* item : sessionItems)
        {
            item->print();
        }
    }

    bool contains(const std::string filename)
    {
        for (SessionItem* item : sessionItems)
        {
            if (item->image->getFilename() == filename)
                return true;
        }

        return false;
    }

    ~Session()
    {
        for(SessionItem* item : this->sessionItems)
        {
            delete item;
        }
    }
};

#endif