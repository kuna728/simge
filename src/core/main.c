#include "../main.h"
#include "printClear.c"
#include <getopt.h>


int main (int argc, char **argv)
{
	argv[0] = "simge";
	Py_Initialize();
	RGB * buffer = NULL;
	int c, modifier;
	char *fout = NULL, *fin = NULL, *temp;
	char delim[] = ",";
	static struct option long_options[] =
	{
	  {"help",      no_argument,       0, 'h'},
	  {"rotate",    required_argument, 0, 'r'},
	  {"mirror",    required_argument, 0, 'm'},
	  {"symmetric", required_argument, 0, 's'},
	  {"resize",    required_argument, 0, 'n'},
	  {"crop",      required_argument, 0, 'p'},
	  {"binary",    required_argument, 0, 'b'},
	  {"grayscale", no_argument,       0, 'g'},
	  {"sepiascale",no_argument,       0, 'e'},
	  {"switch",    required_argument, 0, 'w'},
	  {"lightness", required_argument, 0, 'l'},
	  {"contrast",  required_argument, 0, 'c'},
	  {NULL, 0, 0, '\0'}
	};
	char optStr[] = "hr:m:s:n:p:b:gew:l:c:";
	while (1)
	{
		int option_index = 0;
		c = getopt_long (argc, argv, optStr, long_options, &option_index);
		if (c == -1)
			break;
		if(c=='h')
			printHelpMessage(NULL, NULL);
		if(c=='?')
		 	clearAndExit(NULL, NULL);
	}

	if ((optind + 2) == argc){
	  	fin = argv[optind];
	  	fout = argv[++optind];
	}
	else{
	 	fprintf(stderr, "simge: input and output file must be specified\n");
	  	printHelpPrompt();
	  	clearAndExit(buffer, NULL);
	}

	Image image = {fin, 0, 0, 0, 3, NULL};
	if(loadImage(&image)){
	  	fprintf(stderr, "simge: %s: No such file or directory\n", fin);
	  	clearAndExit(buffer, image.data);
	}

	optind = 0;       
	while (1)
	{
		int option_index = 0;
	  	c = getopt_long (argc, argv, optStr, long_options, &option_index);
	  	if (c == -1)
			break;

	  	switch (c){
			case 'r':
		  		LOG(stderr, "option -r (--rotate) with value `%s'\n", optarg);
		  		buffer = malloc(image.size+1);
		  		if(!strcmp(optarg, "90") || !strcmp(optarg, "90R") || !strcmp(optarg, "90r"))
					rotate90R(&image, buffer);
		  		else if(!strcmp(optarg, "180"))
					rotate180(&image, buffer);
		  		else if(!strcmp(optarg, "-90") || !strcmp(optarg, "90L") || !strcmp(optarg, "90l") || !strcmp(optarg, "270"))
					rotate90L(&image, buffer); 
		  		else
			  		printClearExit(optarg, buffer, image.data);
				break;

			case 'm':
			  	LOG(stderr, "option -m (--mirror) with value `%s'\n", optarg);
			  	buffer = malloc(image.size+1);
			  	if(!strcmp(optarg, "X") || !strcmp(optarg, "x"))
				  	mirrorX(&image, buffer);
			  	else if(!strcmp(optarg, "Y") || !strcmp(optarg, "y"))
				  	mirrorY(&image, buffer);
			  	else
				  	printClearExit(optarg, buffer, image.data);
			  	break;

			case 's':
			  	LOG(stderr, "option -s (--symmetric) with value `%s'\n", optarg);
			  	buffer = malloc(image.size+1);
			  	if(!strcmp(optarg, "l") || !strcmp(optarg, "L") || !strcmp(optarg, "left") || !strcmp(optarg, "Left"))
				  	symmetricYleft(&image, buffer);
			  	else if(!strcmp(optarg, "r") || !strcmp(optarg, "R") || !strcmp(optarg, "right") || !strcmp(optarg, "Right"))
				  	symmetricYright(&image, buffer);
			  	else if(!strcmp(optarg, "u") || !strcmp(optarg, "U") || !strcmp(optarg, "up") || !strcmp(optarg, "Up"))
				  	symmetricXup(&image, buffer);
			  	else if(!strcmp(optarg, "d") || !strcmp(optarg, "D") || !strcmp(optarg, "down") || !strcmp(optarg, "Down"))
				  	symmetricXdown(&image, buffer);
			  	else
				  	printClearExit(optarg, buffer, image.data);
			  	break;

			case 'n':
				LOG(stderr, "option -i (--resize) with value `%s'\n", optarg);
				temp = strtok(optarg, delim);
				int nh = -1, nw = (uint16_t)atoi(temp);
				if((temp = strtok(NULL, delim)))
			  		nh = (uint16_t)atoi(temp);
				else
			  		nh = nw;
				if((nh > 10000 || nh < 1) || (nw > 10000 || nw < 1))
			  		printClearExit(optarg, buffer, image.data);
				buffer = malloc(nh*nw*image.bpp+1);
				resize(&image, buffer, nw, nh == -1 ? nw : nh);
				break;

			case 'p':
				LOG(stderr, "option -p (--crop) with value `%s'\n", optarg);
				temp = strtok(optarg, delim);
				int sx = (uint16_t)atoi(temp), sy, fx, fy;
				if((temp = strtok(NULL, delim)))
				  	sy = (uint16_t)atoi(temp);
				if((temp = strtok(NULL, delim)))
				  	fx = (uint16_t)atoi(temp);
				if((temp = strtok(NULL, delim)))
				  	fy = (uint16_t)atoi(temp);
				if(sx < 0 || sy < 0 || fx > image.width || 
				  	fy > image.height || sx >= fx || sy >= fy )
				  	printClearExit(optarg, buffer, image.data);
				buffer = malloc((fx-sx)*(fy-sy)*image.bpp+1);
				crop(&image, buffer, sx, sy, fx, fy);
				break;

			case 'b': 
			  	LOG(stderr, "option -b (--binary) optarg:%s\n", optarg);
			  	buffer = malloc(image.size+1);
			  	if(!strcmp(optarg, "1") || !strcmp(optarg, "n") || !strcmp(optarg, "normal") || 
				   !strcmp(optarg, "N") || !strcmp(optarg, "Normal") || !strcmp(optarg, "10"))
					binary(&image, false);
			  	else if(!strcmp(optarg, "0") || !strcmp(optarg, "r") || !strcmp(optarg, "reversed") || 
				 	    !strcmp(optarg, "R") || !strcmp(optarg, "Reversed") || !strcmp(optarg, "01"))
					binary(&image, true);
			  	else
					printClearExit(optarg, buffer, image.data);
			  	break;

			case 'g':
				LOG(stderr, "option -g (--grayscale)\n");
				grayscale(&image);
				break;
		
			case 'e':
		  		LOG(stderr, "option -e (--sepiascale)\n");
		  		sepiascale(&image);
		  		break;
		
			case 'w':
		  		LOG(stderr, "option -w (--switch) with value `%s'\n", optarg);
		  		if(strlen(optarg) != 3)
					printClearExit(optarg, buffer, image.data);
		  		for(int i=0; i<=2; i++)
					if(!(optarg[i]=='R' || optarg[i]=='G' || optarg[i]=='B' || optarg[i]=='0' || 
				 		 optarg[i]=='r' || optarg[i]=='g' || optarg[i]=='b' || optarg[i]=='-'))
			  			printClearExit(optarg, buffer, image.data);
		  		switchChannelsStr(&image, optarg);
		  	break;
		
			case 'l':
		  		LOG(stderr, "option -l (--lightness) with value `%s'\n", optarg);
		  		modifier = atoi(optarg);
		  		if(modifier > 255 || modifier < -255)
					printClearExit(optarg, buffer, image.data);
		  		lightness(&image, modifier);
		  		break;;
		
			case 'c':
		  		LOG(stderr, "option -p (--contrast) with value `%s'\n", optarg);
		  		modifier = atoi(optarg);
		  		if(modifier > 360 || modifier < 0)
					printClearExit(optarg, buffer, image.data);
		  		contrast(&image, modifier);          
		  		break;

			case '?':
		  		break;
	  	}
	}

	if(saveImage(fout, image)){
	 	fprintf(stderr, "simge: %s: No such file or directory\n", fout);
	 	clearAndExit(buffer, image.data);
	}
	free(image.data);

	Py_Finalize();
	return 0;
}
