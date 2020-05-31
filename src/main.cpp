#include <iostream>
#include <stdexcept>

#include "Application.h"
#include "PPM.h"
#include "Command.h"
#include "ImageFileFactory.h"
#include "ImageFile.h"

/**
 * \mainpage Project Description
 * 
 * \section Idea
 *  This is a project, that implements readactor for Netpbm image files management. There are some transformations,
 * that can be applied to the images in that format like grayscale, monochrome, negative, bluescale, greenscale, redscale
 * and rotate. You can also make collage from two images. When you load one or more images, a new session automatically starts.
 * Of course you can switch sessions and perform every functionality no matter in which session you are currently in.
 * 
 * \section Github
 * https://github.com/BoyanVD/FMI_OOP_COURSE_PROJECT_GRAPHICS
 */
int main()
{
    /**
     * Command to compile:
     * g++ main.cpp Application.cpp PPM.cpp PGM.cpp PBM.cpp Session.cpp Command.cpp ImageFileFactory.cpp ImageFile.cpp
     * 
     * Example 1 of using the system:
     * >load ./files/Aerial.512.ppm ./files/marbles.ppm
     * >negative
     * >grayscale
     * >undo
     * >save
     * >exit
     * 
     * Example 2 of using the system:
     * >load ./files/Aerial.512.ppm
     * >negative
     * >saveas ./files/Aerial_NEGATIVE.ppm
     * >add ./files/Aerial_NEGATIVE.ppm
     * >collage horizontal ./files/Aerial.512.ppm ./files/Aerial_NEGATIVE.ppm ./files/Aerial_COLLAGE.ppm
     * >exit
     * 
     * Example 3 of using the system:
     * >load ./files/Aerial.512.ppm ./files/marbles.ppm
     * >load ./files/Aerial.512.ppm
     * >switch 1
     * >negative
     * >grayscale
     * >undo
     * >undo
     * >saveas ./files/Aerial_DOUBLE_UNDO.ppm
     * >exit
     * 
     */   
    Application app(std::cin, std::cout);
    app.run();
}