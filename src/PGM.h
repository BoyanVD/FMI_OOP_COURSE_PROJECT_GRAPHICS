#ifndef __PGM_H
#define __PGM_H

#include <iostream>
#include <vector>
#include <string>

#include "ImageFile.h"

struct PixelPGM : public Pixel
{
    unsigned char greyscale;

    PixelPGM() : greyscale(0) {};

    virtual Pixel* clone() const
    {
        return new PixelPGM(*this);
    }

    bool isMonochrome(unsigned int colorRange)
    {
        return ((greyscale == 0) || (greyscale == colorRange));
    }
};

class PGM : public ImageFile
{
private:
    unsigned int colorRange;

    bool openTextType();
    bool openBinaryType();

    bool writeBinary();
    bool writeText();

    bool isMonochrome() const;
public:
    PGM() : ImageFile("", ""), colorRange(255) {};
    PGM(const std::string& _filepath, const std::string& _type) : ImageFile(_filepath, _type), colorRange(255) {};

    void open() override;
    void write() override;
    void grayscale() override {}
    void print() override;
    void monochrome() override;
    void negative() override;
    std::string getType() const override;

    virtual ImageFile* clone() const
    {
        return new PGM(*this);
    }
};

#endif