#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#pragma pack(push, 1)
typedef struct {
uint16_t type;
uint32_t size;
uint16_t reserved1;
uint16_t reserved2;
uint32_t offset;
} BMPHeader;
typedef struct {
uint32_t size;
int32_t width;
int32_t height;
uint16_t planes;
uint16_t bitsPerPixel;
uint32_t compression;
uint32_t imageSize;
int32_t xPixelsPerMeter;
int32_t yPixelsPerMeter;
uint32_t colorsUsed;
uint32_t colorsImportant;
} BMPInfoHeader;
#pragma pack(pop)
int main() {




	// Define rectangle dimensions and data
	int width = 1024;
	int height = 1024;
	uint8_t imageData[width * height * 3]; // 3 bytes per pixel (RGB)
	// Set all pixels to black
	for (int i = 0; i < width * height * 3; i += 3) {
	    imageData[i] = 0;
	    imageData[i + 1] = 0;
	    imageData[i + 2] = 0;
	}
	// Get rectangle coordinates and dimensions from user input
	int x, y, w, h;
	printf("Enter the coordinates of the top-left corner of the rectangle (x y): ");
	scanf("%d %d", &x, &y);
	printf("Enter the width of the rectangle: ");
	scanf("%d", &w);
	printf("Enter the height of the rectangle: ");
	scanf("%d", &h);
	// Set RGB values of pixels inside rectangle to white
int fill;
printf("Press 1 for a filled circle, press 0 for an empty circle");
scanf("%d",&fill );
if(fill==0)
{
	for (int i = x; i < x + w; i++) {
	    int index1 = (y * width + i) * 3;
	    imageData[index1] = 0;
	    imageData[index1 + 1] = 255;
	    imageData[index1 + 2] = 0;
	    int index2 = ((y + h - 1) * width + i) * 3;
	    imageData[index2] = 0;
	    imageData[index2 + 1] = 255;
	    imageData[index2 + 2] = 0;
	}
	for (int j = y; j < y + h; j++) {
	    int index1 = (j * width + x) * 3;
	    imageData[index1] = 0;
	    imageData[index1 + 1] = 255;
	    imageData[index1 + 2] = 0;
	    int index2 = (j * width + x + w - 1) * 3;
	    imageData[index2] = 0;
	    imageData[index2 + 1] = 255;
	    imageData[index2 + 2] = 0;
	}
}


if(fill==1)
{
	for (int i = x; i < x + w; i++) {
	    for (int j = y; j < y + h; j++) {
	        int index = (j * width + i) * 3;
	        imageData[index] = 0;
	        imageData[index + 1] = 255;
	        imageData[index + 2] = 0;
	    }
	}
}
else{
	printf("Error: please enter valid fill value");
}
	// Open file for writing
	FILE* fp = fopen("image.bmp", "wb");
	if (fp == NULL) {
	    printf("Error: could not open file\n");
	    return 1;
	}
	// Write BMP header
	BMPHeader header;
	header.type = 0x4D42; // "BM"
	header.size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + width * height * 3;
	header.reserved1 = 0;
	header.reserved2 = 0;
	header.offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader);
	fwrite(&header, sizeof(BMPHeader), 1, fp);
	// Write BMP info
	BMPInfoHeader infoHeader;
	infoHeader.size = sizeof(BMPInfoHeader);
	infoHeader.width = width;
	infoHeader.height = height;
	infoHeader.planes = 1;
	infoHeader.bitsPerPixel = 24; // 3 bytes per pixel (RGB)
	infoHeader.compression = 0;
	infoHeader.imageSize = width * height * 3;
	infoHeader.xPixelsPerMeter = 0;
	infoHeader.yPixelsPerMeter = 0;
	infoHeader.colorsUsed = 0;
	infoHeader.colorsImportant = 0;
	fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, fp);
	// Write image data
	fwrite(imageData, width * height * 3, 1, fp);
	// Close file
	fclose(fp);


}
