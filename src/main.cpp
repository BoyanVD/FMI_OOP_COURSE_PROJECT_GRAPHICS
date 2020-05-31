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
    //------------------------------------------------------------------------------DEMO_1------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // img->open();
    // img->grayscale();

    // img->setFilename("./files/Aerial_GREYSCALE.ppm");
    // img->write();

    // ImageFile* img1 = ImageFileFactory::generate("./files/Aerial_GREYSCALE.ppm");
    // img1->open();
    // img1->grayscale();
    
    // img1->setFilename("./files/Aerial_GREYSCALE_NEW.ppm");
    // img1->write();
    //------------------------------------------------------------------------------DEMO_1------------------------------------------

    //------------------------------------------------------------------------------DEMO_2------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/marbles.ppm");
    // img->open();
    // img->grayscale();

    // img->setFilename("./files/marbles_GREYSCALE.ppm");
    // img->write();
    //------------------------------------------------------------------------------DEMO_2------------------------------------------

    //------------------------------------------------------------------------------DEMO_3------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/apollonian_gasket.ascii.pgm");
    // img->open();
    // img->grayscale();

    // img->setFilename("./files/apollonian_gasket_COPY.ascii.pgm");
    // img->write();
    //------------------------------------------------------------------------------DEMO_3------------------------------------------

    //------------------------------------------------------------------------------DEMO_4------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/marbles.pbm");
    // img->open();

    // img->setFilename("./files/marbles_COPY.pbm");
    // img->write();
    //------------------------------------------------------------------------------DEMO_4------------------------------------------

    //------------------------------------------------------------------------------DEMO_5------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // img->open();
    // img->grayscale();

    // img->setFilename("./files/Aerial_GREYSCALE.ppm");
    // img->write();

    // ImageFile* img1 = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // img1->open();
    // img1->monochrome();
    
    // img1->setFilename("./files/Aerial_MONOCHROME.ppm");
    // img1->write();
    //------------------------------------------------------------------------------DEMO_5------------------------------------------

    //------------------------------------------------------------------------------DEMO_5------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/apollonian_gasket.ascii.pgm");
    // img->open();
    // img->monochrome();
    
    // img->setFilename("./files/apollonian_gasket_MONO.ascii.pgm");
    // img->write();
    //------------------------------------------------------------------------------DEMO_5------------------------------------------

    //------------------------------------------------------------------------------DEMO_6------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // img->open();
    // img->negative();

    // img->setFilename("./files/Aerial_NEGATIVE.ppm");
    // img->write();
    //------------------------------------------------------------------------------DEMO_6------------------------------------------

    //------------------------------------------------------------------------------DEMO_7------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/apollonian_gasket.ascii.pgm");
    // img->open();
    // img->negative();
    
    // img->setFilename("./files/apollonian_gasket_NEGATIVE.ascii.pgm");
    // img->write();
    //------------------------------------------------------------------------------DEMO_7------------------------------------------

    //------------------------------------------------------------------------------DEMO_8------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/sample.pbm");
    // img->open();
    // img->negative();

    // img->setFilename("./files/sample_NEGATIVE.pbm");
    // img->write();
    //------------------------------------------------------------------------------DEMO_8------------------------------------------

    //------------------------------------------------------------------------------DEMO_8------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/marbles.pbm");
    // img->open();
    // img->negative();

    // img->setFilename("./files/marbles_NEGATIVE.pbm");
    // img->write();
    //------------------------------------------------------------------------------DEMO_8------------------------------------------

    //------------------------------------------------------------------------------DEMO_9------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // img->open();
    // img->rotate("right");

    // img->setFilename("./files/Aerial_ROTATE_RIGTH.ppm");
    // img->write();

    // ImageFile* img1 = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // img1->open();
    // img1->rotate("left");

    // img1->setFilename("./files/Aerial_ROTATE_LEFT.ppm");
    // img1->write();
    //------------------------------------------------------------------------------DEMO_9------------------------------------------

    //------------------------------------------------------------------------------DEMO_10------------------------------------------
    // ImageFile* img = ImageFileFactory::generate("./files/marbles.ppm");
    // img->open();
    // img->rotate("right");

    // img->setFilename("./files/marbles_ROTATE_RIGTH.ppm");
    // img->write();

    // ImageFile* img1 = ImageFileFactory::generate("./files/marbles.ppm");
    // img1->open();
    // img1->rotate("left");

    // img1->setFilename("./files/marbles_ROTATE_LEFT.ppm");
    // img1->write();
    //------------------------------------------------------------------------------DEMO_10------------------------------------------

    //------------------------------------------------------------------------------DEMO_11------------------------------------------
    // ImageFile* image = ImageFile::collage("horizontal", "./files/Aerial.512.ppm", "./files/Aerial.512.ppm", "./files/Aerial_COLLAGE.ppm");
    // image->write();
    //------------------------------------------------------------------------------DEMO_11------------------------------------------

    //------------------------------------------------------------------------------DEMO_12------------------------------------------
    // ImageFile* image = ImageFile::collage("vertical", "./files/Aerial.512.ppm", "./files/Aerial.512.ppm", "./files/Aerial_COLLAGE_VERTICAL.ppm");
    // image->write();
    //------------------------------------------------------------------------------DEMO_12------------------------------------------

    //------------------------------------------------------------------------------DEMO_13------------------------------------------
    // ImageFile* image = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // image->open();
    // image->executeTransformation("shit");

    // // image->setFilename("./files/Aerial_NEGATIVE_WAY_MONOCHROME.ppm");
    // // image->write();
    //------------------------------------------------------------------------------DEMO_13------------------------------------------

    // ImageFile* image = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // image->open();
    // image->redscale();

    // image->setFilename("./files/Aerial_RED.ppm");
    // image->write();

    // ImageFile* image1 = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // image1->open();
    // image1->greenscale();

    // image1->setFilename("./files/Aerial_GREEN.ppm");
    // image1->write();

    // ImageFile* image2 = ImageFileFactory::generate("./files/Aerial.512.ppm");
    // image2->open();
    // image2->bluescale();

    // image2->setFilename("./files/Aerial_BLUE.ppm");
    // image2->write();
    
    Application app(std::cin, std::cout);
    app.run();
}