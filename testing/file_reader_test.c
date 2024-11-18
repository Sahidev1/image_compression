
// current directory is testing
// import from ../file_reader/file_reader.h
#include "../bmp_reader/bmp_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){



    printf("start\n");
    
    if (argc < 2) {
        printf("Error, no filepath given");
        return 1;
    }

    if(access(argv[1], F_OK) != 0){
        printf("Error, file does not exist");
        return 1;
    } else {
        printf("file exists\n");
    }

    const char* filePath = argv[1];
    printf("file path: %s\n", filePath);

    FILE *fptr = fopen(filePath, "rb");
    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    bmp_data* data = malloc(sizeof(bmp_data));
    
    printf("start read\n");

    int read = read_bmp(filePath, data);
    printf ("read status: %d\n", read);

    printf("file size: %d\n", data->header->file_size);
    printf("data offset: %d\n", data->header->data_offset);
    printf("width: %d\n", data->info->width);
    printf("height: %d\n", data->info->height);
    printf("bits per pixel: %d\n", data->info->bits_per_pixel);
    printf("compression: %d\n", data->info->compression);
    printf("imagesize: %d\n", data->info->imagesize);
    printf("Xpixels_perM: %d\n", data->info->Xpixels_perM);
    printf("Ypixels_perM: %d\n", data->info->Ypixels_perM);
    printf("colors_used: %d\n", data->info->colors_used);
    printf("important_colors: %d\n", data->info->important_colors);

    printf("first color in pixel data: %x\n", *data->pixel_data);

    if(argc > 2){
        if (strcmp(argv[2], "print") == 0){
            printf("printing pixel data\n");
            int x, y;
            uint32_t pixel;
            int bytes_per_pixel = data->info->bits_per_pixel / 8;
            uint32_t* pixel_ptr = data->pixel_data;
            for (int i = 0; i < data->info->imagesize; i++){
                pixel = *pixel_ptr;
                y = i / (data->info->width);
                x = i % (data->info->width + data->info->width%32);
                printf("x: %d, y: %d, pixel: %x\n", x, y, pixel);
                pixel_ptr = (uint32_t*)((((char*)pixel_ptr)) + bytes_per_pixel);
                printf("addr %p\n", pixel_ptr);

            }
        }
    }

    return 0;
}