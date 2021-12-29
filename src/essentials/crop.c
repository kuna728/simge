#include "../main.h"


void crop (Image* image, RGB* buffer, uint16_t startX, uint16_t startY, uint16_t finalX, uint16_t finalY)
{
    int n = 0;
    for(int j=startY; j<finalY; j++)
        for(int i=startX; i<finalX; i++)
            writeToBuffer(i, j, &n, image, buffer);
    image->height = finalY-startY;
    image->width = finalX-startX;
    image->size = image->height*image->width*image->bpp;
    free(image->data);
    image->data = buffer;
}