/**
 * \class ImageFile
 *
 * \brief ImageFile base abstract class.
 *
 * The class, that all images in application must extend.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */

/**
 * \struct Pixel
 *
 * \brief Class, representing image pixel.
 *
 * Base class for all types of pixels.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __IMAGE_FILE_H
#define __IMAGE_FILE_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

struct Pixel 
{
    virtual ~Pixel() {};
    virtual Pixel* clone() const = 0;
};

/**
 * @param TRANSFORMATIONS map, used as dictionary for image transformations supported.
 * @param filename name of the file, containing image.
 * @param type type of the image format.
 * @param pixels vector, used to store image pixels.
 * @param width image width.
 * @param height image height. 
 */
class ImageFile
{
protected:
    typedef void (ImageFile::*Transformation)();
    static const std::map<std::string, Transformation> TRANSFORMATIONS;

    std::string filename;
    std::string type;
    std::vector<Pixel*> pixels;
    unsigned int width;
    unsigned int height;

    /**
     * Setter for pixels parameters.
     * 
     * @param _pixels pixels to set.
     */
    void setPixels(const std::vector<Pixel*>& _pixels);

public:
    ImageFile(const std::string& _filename, const std::string& _type) : filename(_filename), type(_type), width(0), height(0) {};

    /**
     * Loads image file content.
     */
    virtual void open() = 0;

    /**
     * Writes image file content to file. 
     */
    virtual void write() = 0;

    /**
     * Performs grayscale transformation. 
     */
    virtual void grayscale() = 0;

    /**
     * Performs monochrome transformation. 
     */
    virtual void monochrome() = 0;

    /**
     * Performs negative transformation. 
     */
    virtual void negative() = 0;

    /**
     * Performs redscale transformation. 
     */
    virtual void redscale() = 0;

    /**
     * Performs greenscale transformation. 
     */
    virtual void greenscale() = 0;

    /**
     * Performs bluescale transformation. 
     */
    virtual void bluescale() = 0;

    /**
     * Performs transformation, given as string.
     * 
     * @param transformation transformation name string
     */
    void executeTransformation(const std::string& transformation);

    /**
     * Returns image type string.
     * 
     * @return image type string.
     */
    virtual std::string getType() const = 0;

    /**
     * Clone method, returning pointer to base class throught derived class.
     * 
     * @return pointer to base class throught derived class.
     */
    virtual ImageFile* clone() const = 0;

    /**
     * Makes collage from two images, horizontally or vertically. Both images
     * must be from same dimensions.
     * 
     * @return pointer to new collage image file
     */
    static ImageFile* collage(std::string direction, std::string image1Filename, std::string image2Filename, std::string outimageFilename);

    /**
     * Gets pixel on indexes (i, j)
     * 
     * @return pointer pixel at (i, j)
     */
    Pixel* getPixel(unsigned int i, unsigned int j);

    /**
     * Sets pixel on indexes (i, j)
     * 
     * @param i rows index
     * @param j colm index
     * @param _pixel pixel to set
     */
    void setPixel(unsigned int i, unsigned int j, const Pixel* _pixel);

    /**
     * Image width getter 
     * 
     * @return image width
     */
    unsigned int getWidth();

    /**
     * Image height getter 
     * 
     * @return image height
     */
    unsigned int getHeight();

    /**
     * Image filename setter
     * 
     * @param newFilename new name.
     */
    void setFilename(std::string newFilename);

    /**
     * Image filename getter 
     * 
     * @return image file name
     */
    std::string getFilename();

    /**
     * Prints image info.
     */
    virtual void print();

    /**
     * Rotates image 90 degress in direction given. Throws exception
     * if direction not valid.
     * 
     * @param direction left or right
     */
    void rotate(std::string direction);

    /**
     * Checks if there is such image transformation
     * 
     * @return bool
     */
    static bool isThereSuchTransformation(std::string transformation);

    virtual ~ImageFile();
};


#endif