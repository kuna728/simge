#include "../main.h"


void resize (Image* image, RGB* buffer, uint16_t newWidth, uint16_t newHeight)
{
    float widthRatio = image->width/(float)newWidth, heightRatio = image->height/(float)newHeight;
    int n = 0;
    for(int j=0; j<newHeight; j++)
        for(int i=0; i<newWidth; i++)
            writeToBuffer((int)(i*widthRatio), (int)(j*heightRatio), &n, image, buffer);

    image->height = newHeight;
    image->width = newWidth;
    image->size = image->height*image->width*image->bpp;
    free(image->data);
    image->data = buffer;
}

