/**
 * \class Session
 *
 * \brief Application session class.
 *
 * Class, used to represent the Application sessions. Stores all the
 * session related functionality.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */

/**
 * \struct SessionItem
 *
 * \brief Nested struct, used to wrap the intems, stored in session.
 *
 * Keeps pair of image and transformations, to be performed on image.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __SESSION_H
#define __SESSION_H

#include <iostream>
#include <vector>

#include "ImageFile.h"
#include "Command.h"
#include "ImageFileFactory.h"

/**
 * @param sessionId session identificator parameter
 * @param sessionItems stores all items, loaded in session.
 */
class Session
{
private:
    struct SessionItem
    {
        ImageFile* image;
        std::vector<std::string> imageTransformations;

        SessionItem(const ImageFile* img, const std::vector<std::string>& transformations) :
        image(img->clone()), imageTransformations(transformations) {}

        ~SessionItem();

        void executeAll();

        void print() const;
    };

    unsigned sessionId;
    std::vector<SessionItem*> sessionItems;
public:
    Session(unsigned _sessionId) : sessionId(_sessionId) {};

    /**
     * Adds new item to session. Note that the Session becomes
     * owner of the pointer through SessionItem constructor.
     * 
     * @param item pointer to image to add
     */
    void addItem(ImageFile* item);

    /**
     * Adds new transformation to all session items loaded.
     * 
     * @param command user input command.
     */
    void addTransformation(const Command& command);

    /**
     * Session id getter
     * 
     * @return session's id
     */
    unsigned getId();

    /**
     * Removes the last transformation from all session items.
     */
    void undo();

    /**
     * Saves all session items to their initial files. Note that it doesn't
     * remove them from session after saving them.
     */
    void save();

    /**
     * Saves the first session item in file given, all other items are
     * saved in their initial files. Please note that after saveas the first item
     * stays the same for the session.
     * 
     * @param newName first item new name.
     */
    void saveas(const std::string& newName);

    /**
     * Performs all transformation to images in session. Please 
     * note thet after executing transformation, the session items are
     * cleared.
     */
    void executeAllTransformations();

    /**
     * Needed for <algorithm> sort function.
     */
    bool operator < (Session other);

    /**
     * Prints info about session
     */
    void print();

    /**
     * Checks if there is session item with name given.
     * 
     * @param filename name of file to look for
     * @return bool
     */
    bool contains(const std::string filename);

    /**
     * Rotates all session items 90 degree in direction given
     * 
     * @param direction
     */
    void rotate(const std::string& direction);

    ~Session();
};

#endif