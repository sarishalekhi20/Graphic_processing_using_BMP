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
// Define image dimensions and data
int width = 1024;
int height = 1024;
uint8_t imageData[width * height * 3]; // 3 bytes per pixel (RGB)
// Set all pixels to black
for (int i = 0; i < width * height * 3; i += 3) {
imageData[i] = 0;
imageData[i + 1] = 0;
imageData[i + 2] = 0;
}
// Get circle center and radius from user input
int centerX, centerY, radius;
printf("Enter the coordinates of the center of the circle (x y): ");
scanf("%d %d", &centerX, &centerY);
printf("Enter the radius of the circle: ");
scanf("%d", &radius);
clock_t start = clock();
// Draw circle using midpoint circle algorithm
int x = radius;
int y = 0;
int err = 0;
int fill;
printf("Press 1 for a filled circle, press 0 for an empty circle");
scanf("%d",&fill );
if(fill==0)
{
	while (x >= y) {
	 // Set RGB values of pixels on circle to red
	 int index1 = ((centerY + y) * width + centerX + x) * 3;
	 imageData[index1] = 255;
	 imageData[index1 + 1] = 0;
	 imageData[index1 + 2] = 0;
	 int index2 = ((centerY + x) * width + centerX + y) * 3;
	 imageData[index2] = 255;
	 imageData[index2 + 1] = 0;
	 imageData[index2 + 2] = 0;
	 int index3 = ((centerY + x) * width + centerX - y) * 3;
	 imageData[index3] = 255;
	 imageData[index3 + 1] = 0;
	 imageData[index3 + 2] = 0;
	 int index4 = ((centerY + y) * width + centerX - x) * 3;
	 imageData[index4] = 255;
	 imageData[index4 + 1] = 0;
	 imageData[index4 + 2] = 0;
	 int index5 = ((centerY - y) * width + centerX - x) * 3;
	 imageData[index5] = 255;
	 imageData[index5 + 1] = 0;
	 imageData[index5 + 2] = 0;
	 int index6 = ((centerY - x) * width + centerX - y) * 3;
	 imageData[index6] = 255;
	 imageData[index6 + 1] = 0;
	 imageData[index6 + 2] = 0;
	 int index7 = ((centerY - x) * width + centerX + y) * 3;
	 imageData[index7] = 255;
	 imageData[index7 + 1] = 0;
	 imageData[index7 + 2] = 0;
	 int index8 = ((centerY - y) *width + centerX + x) * 3;
	 imageData[index8] = 255;
	 imageData[index8 + 1] = 0;
	 imageData[index8 + 2] = 0;
	 if (err <= 0) {
	 y += 1;
	 err += 2 * y + 1;
	 }
	 if (err > 0) {
	 x -= 1;
	 err -= 2 * x + 1;
	 }
	 }
}
if(fill==1)
{
	int x = radius;
	int y = 0;
	int err = 0;
	while (x >= y) {
	 // Set RGB values of pixels inside circle to red
	 for (int i = centerX - x; i <= centerX + x; i++) {
	 for (int j = centerY - y; j <= centerY + y; j++) {
	 int dx = i - centerX;
	 int dy = j - centerY;
	 if (dx * dx + dy * dy <= radius * radius) {
	 int index = (j * width + i) * 3;
	 imageData[index] = 0;
	 imageData[index + 1] = 255;
	 imageData[index + 2] = 0;
	 }
	 }
	 }
	 for (int i = centerX - y; i <= centerX + y; i++) {
	 for (int j = centerY - x; j <= centerY + x; j++) {
	 int dx = i - centerX;
	 int dy = j - centerY;
	 if (dx * dx + dy * dy <= radius * radius) {
	 int index = (j * width + i) * 3;
	 imageData[index] = 0;
	 imageData[index + 1] = 255;
	 imageData[index + 2] = 0;
	 }
	 }
	 }
	 if (err <= 0) {
	 y += 1;
	 err += 2 * y + 1;
	 }
	 if (err > 0) {
	 x -= 1;
	 err -= 2 * x + 1;
	 }
	}
}
else
{
	printf("Error:Please enter valid fill value");
}
clock_t end = clock();
double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
//Open file for writing
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
printf("Time taken: %f seconds\n", timeTaken);
return 0;
}
