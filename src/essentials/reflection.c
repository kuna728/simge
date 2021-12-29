#include "../main.h"


void mirrorY(Image * image, RGB* buffer)
{
    int n = 0;
    for(int j=0; j<image->height; j++)
        for(int i=image->width-1; i>=0; i--)
            writeToBuffer(i, j, &n, image, buffer);
    free(image->data);
    image->data = buffer;
}

void mirrorX(Image * image, RGB* buffer)
{
    int n = 0;
    for(int j=image->height-1; j>=0; j--)
        for(int i=0; i<image->width; i++)
            writeToBuffer(i, j, &n, image, buffer);
    free(image->data);
    image->data = buffer;
}

void symmetricYleft(Image* image, RGB* buffer)
{
    int n=0;
    for(int j=0; j<image->height; j++)
    {
        for(int i=0; i<image->width/2; i++)
            writeToBuffer(i, j, &n, image, buffer);   
        int i= image->width%2 ? image->width/2 : image->width/2 - 1;
        for(i; i>=0; i--)
            writeToBuffer(i, j, &n, image, buffer);   
    }
    free(image->data);
    image->data = buffer;
}

void symmetricYright(Image* image, RGB* buffer)
{
    int n=0;
    for(int j=0; j<image->height; j++)
    {
        for(int i=image->width-1; i>=image->width/2; i--)
            writeToBuffer(i, j, &n, image, buffer);  
        int i= image->width%2 ? (image->width/2+1) : image->width/2; 
        for(i; i<image->width; i++)
            writeToBuffer(i, j, &n, image, buffer);   
    }
    free(image->data);
    image->data = buffer;
}

void symmetricXup(Image* image, RGB* buffer)
{
    int n=0;
    for(int j=0; j<image->height/2; j++)
        for(int i=0; i<image->width; i++)
            writeToBuffer(i, j, &n, image, buffer); 
    for(int j=image->height/2; j>0; j--)
        for(int i=0; i<image->width; i++)
            writeToBuffer(i, j, &n, image, buffer); 
    free(image->data);
    image->data = buffer;
}

void symmetricXdown(Image* image, RGB* buffer)
{
    int n=0;
    for(int j=image->height-1; j>=image->height/2; j--)
        for(int i=0; i<image->width; i++)
            writeToBuffer(i, j, &n, image, buffer); 
    int j= image->height%2 ? (image->height/2+1) : image->height/2; 
    for(j; j<image->height; j++)
        for(int i=0; i<image->width; i++)
            writeToBuffer(i, j, &n, image, buffer); 
    free(image->data);
    image->data = buffer;
}