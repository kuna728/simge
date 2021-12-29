#!/bin/bash

gcc -o simge src/core/common.c src/core/load.c src/core/main.c src/core/save.c src/essentials/crop.c src/essentials/reflection.c src/essentials/resize.c src/essentials/rotate.c src/effects/simple.c src/effects/tonal.c -lm -I/usr/include/python3.8  -lpython3.8