#ifndef SAVE_SNAPSHOT_H
#define SAVE_SNAPSHOT_H
#include "libary_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <string.h>
#include <time.h>
#include <errno.h>


size_t jpeg_save(snapshot_t *img,char * data);
void saveFrame_jpg(uint8_t *pRGBBuffer, char * iFrame, int width, int height);
void save_snapshot(snapshot_t* snap,char* rgb_matrix);
#endif // SAVE_SNAPSHOT_H

