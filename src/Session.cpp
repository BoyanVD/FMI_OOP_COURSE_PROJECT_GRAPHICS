#ifndef __SESSION_CPP
#define __SESSION_CPP

#include "Session.h"

void Session::addItem(ImageFile* item)
{
    this->sessionItems.push_back(new SessionItem(item, {}));
}

void Session::addTransformation(const Command& command)
{
    std::string cmd = command.getCommand();
    for (SessionItem* item : sessionItems)
    {
        item->imageTransformations.push_back(cmd);
    }
}

unsigned Session::getId()
{
    return this->sessionId;
}

void Session::undo()
{
    for (SessionItem* item : sessionItems)
    {
        item->imageTransformations.pop_back();
    }
}

void Session::save()
{
    for (SessionItem* item : sessionItems)
    {
        item->image->write();
    }
}

void Session::saveas(const std::string& newName)
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

void Session::executeAllTransformations()
{
    for (SessionItem* item : sessionItems)
    {
        item->executeAll();
    }
}

bool Session::operator < (Session other) // needed for <algorithm> sort function
{
    return this->sessionId < other.sessionId;
}

void Session::print()
{
    std::cout << "Session ID : " << sessionId << std::endl;

    for (SessionItem* item : sessionItems)
    {
        item->print();
    }
}

bool Session::contains(const std::string filename)
{
    for (SessionItem* item : sessionItems)
    {
        if (item->image->getFilename() == filename)
            return true;
    }

    return false;
}

Session::~Session()
{
    for(SessionItem* item : this->sessionItems)
    {
        delete item;
    }
}

Session::SessionItem::~SessionItem()
{
        delete image;
}

void Session::SessionItem::executeAll()
{
    for (std::string transformation : imageTransformations)
    {
        image->executeTransformation(transformation);
    }

    imageTransformations.clear();
}

void Session::SessionItem::print() const
{
    std::cout << "Image : " << image->getFilename() << std::endl;
    std::cout << "Transformations to be done on image : " << std::endl;
    for (std::string transformation : imageTransformations)
    {
        std::cout << transformation << std::endl;
    }
}

void Session::rotate(const std::string& direction)
{
    for (SessionItem* item : this->sessionItems)
    {
        try
        {
            item->image->rotate(direction);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            continue;
        }
    }
}

#endif