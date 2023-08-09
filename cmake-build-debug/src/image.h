//
// Created by Max Ross on 3/23/22.
//
#include <vector>
#ifndef PROJECT2_IMAGE_H
#define PROJECT2_IMAGE_H
using namespace std;

class pixel {
public:
    unsigned char red, green, blue;
    pixel();
    pixel(unsigned char red, unsigned char green, unsigned char blue);
};

class image {
public:
    vector<pixel> pixels;
};

struct Header
{
    char  idLength;
    char  colorMapType;
    char  dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  bitsPerPixel;
    char  imageDescriptor;
};



#endif //PROJECT2_IMAGE_H
