#include "../main.h"
#define VALUEOR255(value) (value > 255 ? 255 : value)


void binary(Image* image, bool reverse)
{
    double avg = 0;
    for(int i=0; i<(image->size/image->bpp); i++)
        avg += (image->data[i].R + image->data[i].G + image->data[i].B) / 3.0;
    avg /= (image->size/image->bpp);
    for(int i=0; i<(image->size/image->bpp); i++)
    {
        double val = (image->data[i].R + image->data[i].G + image->data[i].B) / 3.0;
        if(val > avg)
           image->data[i].R = image->data[i].G = image->data[i].B = reverse ? 0 : 255;
        else
            image->data[i].R = image->data[i].G = image->data[i].B = reverse ? 255 : 0;
    } 
}

void grayscale(Image* image)
{
    for(int i=0; i<(image->size/image->bpp); i++)
    {
        //uint8_t val = 0.299*image->data[i].R + 0.587*image->data[i].G + 0.114*image->data[i].B + 0.5;
        uint8_t val = (image->data[i].R + image->data[i].G + image->data[i].B) / 3.0;
        image->data[i].R = image->data[i].G = image->data[i].B = val;
    }
}

void sepiascale(Image* image)
{
    for(int i=0; i<(image->size/image->bpp); i++)
    {
        image->data[i].R = VALUEOR255(image->data[i].R*0.393 + image->data[i].G*0.769 + image->data[i].B*0.189);
        image->data[i].G = VALUEOR255(image->data[i].R*0.349 + image->data[i].G*0.686 + image->data[i].B*.168);
        image->data[i].B = VALUEOR255(image->data[i].R*0.272 + image->data[i].G*0.534 + image->data[i].B*0.131);
    } 
}

void displayChannels(Image* image, uint8_t channels)
{ 
    for(int i=0; i<(image->size/image->bpp); i++)
    {
        image->data[i].R= (channels>>2 & 0b1) ?  image->data[i].R : 0; 
        image->data[i].G= (channels>>1 & 0b1) ?  image->data[i].G : 0; 
        image->data[i].B= (channels & 0b1) ?  image->data[i].B : 0;
    }
}

void switchChannelsStr(Image* image, char* channels_str)
{
    uint8_t channels = 0;
    for(int i=2; i>=0; i--)
    {
        if(channels_str[2-i]=='R' || channels_str[2-i]=='r')
            channels += (0b01<<(i*2));
        else if(channels_str[2-i]=='G' || channels_str[2-i]=='g')
            channels += (0b10<<(i*2));
        else if(channels_str[2-i]=='B' || channels_str[2-i]=='b')
            channels += (0b11<<(i*2));
    }
    switchChannels(image, channels);
}

void switchChannels(Image* image, uint8_t channels)
{
    for(int i=0; i<(image->size/image->bpp); i++)
    {
        if((channels>>4 & 0b11) == 0b01)
            image->data[i].R = image->data[i].R;
        else if((channels>>4 & 0b11) == 0b10)
            image->data[i].R = image->data[i].G;
        else if((channels>>4 & 0b11) == 0b11)
            image->data[i].R = image->data[i].B;
        else
            image->data[i].R = 0;
        
        if((channels>>2 & 0b11) == 0b10)
            image->data[i].G = image->data[i].G;
        else if((channels>>2 & 0b11) == 0b01)
            image->data[i].G = image->data[i].R;
        else if((channels>>2 & 0b11) == 0b11)
            image->data[i].G = image->data[i].B;
        else
            image->data[i].G = 0;

        if((channels & 0b11) == 0b11)
            image->data[i].B = image->data[i].B;
        else if((channels & 0b11) == 0b10)
            image->data[i].B = image->data[i].G;
        else if((channels & 0b11) == 0b01)
            image->data[i].B = image->data[i].R;
        else
            image->data[i].B = 0;
    }
}


