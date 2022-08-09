#include "save_snapshot.h"


size_t ppm_save(snapshot_t *img,char * data) {
    printf("save ppm\n %d",img->width);
    FILE *   fp=fopen(img->file_name,"wb+");
    size_t n = 0;
    n +=fprintf(fp, "P6\n# THIS IS A COMMENT\n%d %d\n%d\n",
                img->width, img->height, 0xFF);
    n += fwrite(data, 1, img->width * img->height * 3, fp);
    fclose(fp);
    return n;
}
size_t jpeg_save(snapshot_t *img,char * data)
{
    saveFrame_jpg((uint8_t *)data,img->file_name,img->width,img->height);
}
void saveFrame_jpg(uint8_t *pRGBBuffer, char * iFrame, int width, int height)
{

    struct jpeg_compress_struct cinfo;

    struct jpeg_error_mgr jerr;

    char szFilename[1024];
    int row_stride;

    FILE *fp;

    JSAMPROW row_pointer[1];//One row of bitmap

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_compress(&cinfo);


    sprintf(szFilename, "testZipi%s.jpg", iFrame);//Picture name is video name + number
    fp = fopen(szFilename, "wb");

    if(fp == NULL)
            return;

    jpeg_stdio_dest(&cinfo, fp);

    cinfo.image_width = width;//is the width and height of the image, in pixels
    cinfo.image_height = height;
    cinfo.input_components = 3;//Here is 1, which means grayscale image, if it is a color bitmap, it is 3
    cinfo.in_color_space = JCS_RGB;//JCS_GRAYSCALE means grayscale image, JCS_RGB means color image

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality (&cinfo, 80, 1);

    jpeg_start_compress(&cinfo, TRUE);


    row_stride = cinfo.image_width * 3;//The number of bytes in each row, if it is not an index image, it needs to be multiplied by 3 here

   //Compress each row
    while (cinfo.next_scanline <cinfo.image_height) {
        row_pointer[0] = &(pRGBBuffer[cinfo.next_scanline * row_stride]);
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    fclose(fp);
}
void save_snapshot(snapshot_t* snap,char* rgb_matrix){
    snapshot_t s;
    s.width=SNAPSHOT_WIDTH;
    s.height=SNAPSHOT_HEIGHT;
    s.file_name="imagezipi_11_25.bmp";
    ppm_save(&s,rgb_matrix);
    jpeg_save(&s,rgb_matrix);
}
