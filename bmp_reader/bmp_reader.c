#include "bmp_reader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int file_read_errorcheck(FILE* f){
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    } 
    int e = ferror(f);
    if (e != 0) perror("file read error!");
    return e;
}

int read_bmp(const char *filePath, bmp_data *data)
{
    FILE *fptr = fopen(filePath, "rb");  

    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }

//    printf("success open file\n");

    char sig[2];
    
    char* expSig = "BM";

    fread(&sig[0], sizeof(char), 2, fptr);

    if(file_read_errorcheck(fptr)) return 1;
    if(strcmp(&sig[0], expSig) != 0){
        perror("invalid file format, please use BMP files");
        return 1;
    }

 //   printf("success read sig\n");
    
    data->sig[0] = 'B';
    data->sig[1] = 'M';
    
    bmp_header* header = malloc(sizeof(bmp_header));
    fread(header, sizeof(uint32_t), 3, fptr);

    if(file_read_errorcheck(fptr)) return 1;
    data->header = header;

   // printf("success read header");

    bmp_info_header* info = malloc(sizeof(bmp_info_header));
    fread(info, sizeof(uint32_t), 10, fptr );
    if(file_read_errorcheck(fptr)) return 1;
    data->info = info;

    //printf("success read info");

    int word_padded_width = data->info->width + (data->info->width % 4);

    uint32_t* pixel_data = malloc((word_padded_width * data->info->height)*sizeof(uint32_t));
    fread(pixel_data, sizeof(uint32_t), word_padded_width * data->info->height, fptr);
    if(file_read_errorcheck(fptr)) return 1;
    data->pixel_data = pixel_data;

    fclose(fptr);
    //printf("success read pixel data");
    
    return 0;
}