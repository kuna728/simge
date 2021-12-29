#include "../main.h"


void writeToBuffer(int i, int j, int * n, Image * image, RGB* buffer)
{
    buffer[*n] = image->data[i+j*image->width]; 
    (*n)++;
}