/**
 * \class Application
 *
 * \brief The application driving class
 *
 * This is the class, where most of the application features
 * and functionality is maneged. It contains most of the
 * business logic as well. Please, note that the application works
 * with both binary and ASCII files format, but doesn't support
 * operations with files, that contain comment line.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"
#include "Session.h"
#include "Command.h"

/**
 * @param SUPPORTED_FUNCTIONS map, used like dictionary for supported functions by app.
 * @param inputStream the stream, used for user input.
 * @param logStream the stream, used for Application loggs. 
 * @param sessions stores all loaded sessions by user.
 * @param currentSession stores pointer to the current session.
 */
class Application
{
private:
    typedef void (Application::*Function)(const Command&);
    static const std::map<std::string, Function> SUPPORTED_FUNCTIONS;

    std::istream& inputStream;
    std::ostream& logStream;

    std::vector<Session*> sessions;
    Session* currentSession;

    /**
     * Used to generate new unique session id.
     */
    unsigned generateUniqueId();

    /**
     * Function, used to wrap the work with SUPPORTED_FUNCTIONS map.
     * 
     * @param key the key, used to get function by. 
     */
    Function getFunction(const std::string key);

    /**
     * Loads image from filepath, extracted from user input. Automatically
     * starts new session as well.
     * 
     * @param command parsed user input.
     */
    void load(const Command& command);

    /**
     * Adds new image to current session.
     * 
     * @param command parsed user input.
     */
    void addImage(const Command& command);

    /**
     * Shows brief information about current session.
     * 
     * @param command parsed user input.
     */
    void sessionInfo(const Command& command);

    /**
     * Switches the current session.
     * 
     * @param command parsed user input.
     */
    void switchSession(const Command& command);

    /**
     * Makes collage from two images. They should be from the same dimensions.
     * There are two options for collage - horizontal and vertical.
     * 
     * @param command parsed user input.
     */
    void collage(const Command& command);

    /**
     * Rotates all images in current session. Please note that 
     * rotate just like collage is performed immediately.
     * 
     * @param command parsed user input.
     */
    void rotate(const Command& command);

    /**
     * Adds new transformation to all images in current session. Supported
     * transformations are grayscale, monochrome, negative, redscale, greenscale and bluescale.
     * 
     * @param command parsed user input.
     */
    void imageTransformation(const Command& command);

    /**
     * Saves all images to initial files.
     * 
     * @param command parsed user input.
     */
    void save(const Command& command);

    /**
     * Saves the first image, loaded in session, in new file given.
     * All the other files are saved in their initial files.
     * 
     * @param command parsed user input.
     */
    void saveas(const Command& command);

    /**
     * Removes the last image transformation made.
     * 
     * @param command parsed user input.
     */
    void undo(const Command& command);

    /**
     * Prints all sessions, mostly used for demonstration purposes. 
     */
    void printSessions();
public:
    Application(std::istream& _inputStream, std::ostream& _logStream) : 
    inputStream(_inputStream), logStream(_logStream), currentSession(nullptr) {}

    /**
     * The application management method.
     */
    void run();

    ~Application();
};

#endif