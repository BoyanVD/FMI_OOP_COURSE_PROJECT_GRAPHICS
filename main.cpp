#include <iostream>

#include "Application.h"
#include "PPM.h"

int main()
{
    PPM img;
    img.open("./files/6colour_ppma.ppm");
    img.print();
}