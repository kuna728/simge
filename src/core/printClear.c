#include "../main.h"

void clearAndExit(RGB * buffer, RGB * data);
void printHelpPrompt();


void printClearExit( char * optarg, RGB * buffer, RGB * data)
{
    fprintf(stderr, "simge: invalid field value '%s'\n", optarg);
    printHelpPrompt();
    clearAndExit(buffer, data);
}

void printHelpPrompt()
{
    fprintf(stderr, "Try 'simge --help' for more information.\n");
}

void printHelpMessage(RGB * buffer, RGB * data)
{
    char * helpMessage = 
"Usage: simge [options]... <file_in> <file_out>\n"
"Images editing, manipulating and filtering program.\n\n"
"Options:\n"
"  -r <angle>,       --rotate <angle>      Rotates image by angle. Angle must be in {90, 180, 270}.\n"
"  -m <axis>,        --mirror <axis>       Mirrors image to the axis. Axis must be in {x, y}.\n"
"  -s <side>,        --symmetric <side>    Reflects image side symmetric. Side must be in {l, u, r, d}.\n"
"  -n <dimension>,   --resize <dimension>  Resizes image. Dimension format is 'new_width[,new_height]'.\n"
"                                            Resizes both sides with new_width if new_height is not given. \n"
"  -p <coordinates>, --crop <coordinates>  Crops image. Coordinates format is 'start_x,start_y,final_x,final_y'.\n"
"  -b <method>,      --binary <method>     Converts image to binary. Method must be in (n, r).\n"
"  -g,               --grayscale           Converts image to grayscale.\n"
"  -e,               --sepiascale          Converts image to sepiascale.\n"
"  -w <channels>,    --switch <channels>   Switch or disable image's RGB channels. Channels value must be like '___',\n"
"                                            each of '_' must be in (R,G,B,0).\n"
"  -l <value>,       --lightness <value>   Sets image lightness to value. Value must be integer in range <-255,255>.\n"
"  -c <value>,       --contrast <value>    Sets image contrast to value. Value must be integer in range <0,360>.\n\n"
"Options order is relevant. For example running program with options '-r180 -p100,100,200,200' (rotate then crop)\n"
"is not equivalent to running program with options '-p100,100,200,200 -r180' (crop then rotate).\n"
"Output file format is specified by given extension (Python Pillow is used for compression and decompression purposes).\n\n"
"Project homepage: https://www.github.com/kuna7/simge/\n";
    fprintf(stderr, "%s", helpMessage);
    clearAndExit(buffer, data);
}

void clearAndExit(RGB * buffer, RGB * data)
{
    if(buffer) free(buffer);
    if(data) free(data);
    exit(1);
}