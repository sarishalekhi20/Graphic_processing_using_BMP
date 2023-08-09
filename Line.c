#include <stdint.h>
#include <stdio.h>
#include <time.h>
#pragma pack(push, 1)
typedef struct {
uint16_t type; // Magic identifier: "BM"
uint32_t size; // File size in bytes
uint16_t reserved1; // Not used
uint16_t reserved2; // Not used
uint32_t offset; // Offset to image data in bytes from beginning of file
} BMPHeader;
typedef struct {
uint32_t size; // Size of this header in bytes
int32_t width; // Image width in pixels
int32_t height; // Image height in pixels
uint16_t planes; // Number of color planes
uint16_t bitsPerPixel; // Number of bits per pixel
uint32_t compression; // Compression methods used
uint32_t imageSize; // Size of uncompressed image in bytes
int32_t xPixelsPerMeter; // Horizontal resolution in pixels per meter
int32_t yPixelsPerMeter; // Vertical resolution in pixels per meter
uint32_t colorsUsed; // Number of colors in the image
uint32_t colorsImportant; // Minimum number of important colors
} BMPInfoHeader;
#pragma pack(pop)
int main() {
// Start timer
clock_t start = clock();
// Define image dimensions and data
int width = 1024;
int height = 1024;
uint8_t imageData[width * height * 3]; // 3 bytes per pixel (RGB)
// Set all pixels to white
for (int i = 0; i < width * height * 3; i += 3) {
// Check if pixel is selected
// if () {
// Set RGB values to 255 (white)
imageData[i] = 0; //colour-blue
imageData[i + 1] = 0; //green
imageData[i + 2] = 0; //red
// }
}
// Get line endpoints from user input
int x0, y0, x1, y1;
printf("Enter the coordinates of the first endpoint (x0 y0): ");
scanf("%d %d", &x0, &y0);
printf("Enter the coordinates of the second endpoint (x1 y1): ");
scanf("%d %d", &x1, &y1);
if(x0>1024 || x1>1024 || y0>1024 || y1>1024){
	printf("Error:wrong coordinates\n");
}
// Draw line using Bresenham's line algorithm
int dx = abs(x1 - x0);
int dy = abs(y1 - y0);
int sx = x0 < x1 ? 1 : -1;
int sy = y0 < y1 ? 1 : -1;
int err = dx - dy;
while (x0 != x1 || y0 != y1) {
// Set RGB values of pixel on line 
int index = (y0 * width + x0) * 3;
imageData[index] = 225; //blue
imageData[index + 1] = 225; //green
imageData[index + 2] = 0; //red
int e2 = 2 * err;
if (e2 > -dy) {
err -= dy;
x0 += sx;
}
if (e2 < dx) {
err += dx;
y0 += sy;
}
}
// End timer
clock_t end = clock();
double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
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
// Write BMP info header
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
// Display time taken
printf("Time taken: %f seconds\n", timeTaken);
return 0;
}


