#ifndef BMP_READER_H
#define BMP_READER_H

#include <stdint.h>

typedef struct Bmp_header {
    uint32_t file_size;
    uint32_t reserved;
    uint32_t data_offset;
} bmp_header;

typedef struct Bmp_info_header {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t imagesize;     
    uint32_t Xpixels_perM;
    uint32_t Ypixels_perM;
    uint32_t colors_used;
    uint32_t important_colors;
} bmp_info_header;

typedef struct Bmp_data {
    char sig[2];
    bmp_header* header;
    bmp_info_header* info;
    uint32_t* pixel_data;
} bmp_data;

int read_bmp(const char *filePath, bmp_data *data);

#endif 

