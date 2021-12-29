#include "../main.h"


void rotate90R(Image * image, RGB* buffer)
{
    int n = 0;
    for(int i=0; i<image->width; i++)
        for(int j=image->height-1; j>=0; j--)
            writeToBuffer(i, j, &n, image, buffer);
    free(image->data);
    image->data = buffer;
    uint16_t w = image->width;
    image->width = image->height;
    image->height = w;
}

void rotate180(Image * image, RGB* buffer)
{
    int n = 0;
    for(int j=image->height-1; j>=0; j--)
        for(int i=image->width-1; i>=0; i--)
            writeToBuffer(i, j, &n, image, buffer);
    free(image->data);
    image->data = buffer;
}

void rotate90L(Image * image, RGB* buffer)
{
    int n = 0;
    for(int i=image->width-1; i>=0; i--)
        for(int j=0; j<image->height; j++)
            writeToBuffer(i, j, &n, image, buffer);
    free(image->data);
    image->data = buffer;
    uint16_t w = image->width;
    image->width = image->height;
    image->height = w;
}
