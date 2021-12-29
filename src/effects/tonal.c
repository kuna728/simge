#include "../main.h"

uint8_t Ylightness(uint8_t value, int16_t modifier)
{
    if((value+modifier)>255)
        return 255;
    if((value+modifier)<0)
        return 0;
    return value + modifier;
}

void lightness(Image* image, int16_t modifier)
{
    for(int i=0; i<(image->size/image->bpp); i++)
    {
        image->data[i].R = Ylightness(image->data[i].R, modifier);
        image->data[i].G = Ylightness(image->data[i].G, modifier);
        image->data[i].B = Ylightness(image->data[i].B, modifier);
    }
}

uint8_t Ycontrast(uint8_t value, int16_t modifier)
{
    if(modifier==360)
        return value > 127.5 ? 255 : 0;
    
    int ret =  (int)(tan((modifier / 720.0) * M_PI) * (value - 127.5) + 127.5);

    if (ret > 255)
        return 255;
    if (ret < 0)
        return 0;
    return ret;
}

void contrast(Image* image, int16_t modifier)
{
    for(int i=0; i<(image->size/image->bpp); i++)
    {
        image->data[i].R = Ycontrast(image->data[i].R, modifier);
        image->data[i].G = Ycontrast(image->data[i].G, modifier);
        image->data[i].B = Ycontrast(image->data[i].B, modifier);
    }
}

