#ifndef img_h
#define img_h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <getopt.h>
#include <python3.8/Python.h>

// #define LOGGING 
#ifdef LOGGING
#define PYERR_PRINT() PyErr_Print()
#define LOG(...) fprintf(__VA_ARGS__)
#else
#define PYERR_PRINT()
#define LOG(...)
#endif

typedef struct RGB
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB;

typedef struct Image {
    char* path;
    uint16_t width;
    uint16_t height;
    size_t size;
    uint8_t bpp;
    RGB * data;
} Image;

int loadImage(Image*);
int saveImage(char *, Image);

//common.c
void writeToBuffer(int, int, int*, Image*, RGB*);

//rotate.c
void rotate90L(Image*, RGB*);
void rotate180(Image*, RGB*);
void rotate90R(Image*, RGB*);

//reflection.c
void mirrorY(Image*, RGB*);
void mirrorX(Image*, RGB*);
void symmetricYleft(Image*, RGB*);
void symmetricYright(Image*, RGB*);
void symmetricXup(Image*, RGB*);
void symmetricXdown(Image*, RGB*);

//resize.c
void resize (Image* image, RGB* buffer, uint16_t newWidth, uint16_t newHeight);

//crop.c
void crop (Image* image, RGB* buffer, uint16_t startX, uint16_t startY, uint16_t finalX, uint16_t finalY);

//simple.c
void binary(Image * image, bool reverse);
void displayChannels(Image* image, uint8_t channels);
void switchChannelsStr(Image* image, char* channels_str);
void switchChannels(Image* image, uint8_t channels);
void grayscale(Image * image);
void sepiascale(Image* image);

//tonal.c
void lightness(Image* image, int16_t modifier);
void contrast(Image* image, int16_t modifier);

#endif