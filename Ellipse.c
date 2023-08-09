#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

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
// Get ellipse center, major and minor axis lengths, and rotation angle from user input
int centerX, centerY, a, b;
double angle;
printf("Enter the coordinates of the center of the ellipse (x y): ");
scanf("%d %d", &centerX, &centerY);
printf("Enter the length of the major axis: ");
scanf("%d", &a);
printf("Enter the length of the minor axis: ");
scanf("%d", &b);
printf("Enter the rotation angle in degrees: ");
scanf("%lf", &angle);
// Convert rotation angle from degrees to radians
angle = angle * M_PI / 180.0;
// Start timer
clock_t start = clock();
// Draw ellipse using midpoint ellipse algorithm
int x = 0;
int y = b;
double d1 = b * b - a * a * b + 0.25 * a * a;
int dx = 2 * b * b * x;
int dy = 2 * a * a * y;
int fill;
printf("Press 1 to fill, press 0 for empty widget");
scanf("%d",&fill );
if(fill==0)
{
	while (dx < dy) {
	// Set RGB values of pixels on ellipse to white
	int index1 = ((int)(centerY + y * cos(angle) - x * sin(angle)) * width + (int)(centerX + x * cos(angle) + y * sin(angle))) * 3;
	imageData[index1] = 0;
	imageData[index1 + 1] = 255;
	imageData[index1 + 2] = 0;
	int index2 = ((int)(centerY - y * cos(angle) - x * sin(angle)) * width + (int)(centerX + x * cos(angle) - y * sin(angle))) * 3;
	imageData[index2] = 0;
	imageData[index2 + 1] = 255;
	imageData[index2 + 2] = 0;
	int index3 = ((int)(centerY - y * cos(angle) + x * sin(angle)) * width + (int)(centerX - x * cos(angle) - y * sin(angle))) * 3;
	imageData[index3] = 0;
	imageData[index3 + 1] = 255;
	imageData[index3 + 2] = 0;
	int index4 = ((int)(centerY + y * cos(angle) + x * sin(angle)) * width + (int)(centerX - x * cos(angle) + y * sin(angle))) * 3;
	imageData[index4] = 0;
	imageData[index4 + 1] = 255;
	imageData[index4 + 2] = 0;
	if (d1 < 0) {
	x += 1;
	dx += 2 * b * b;
	d1 += dx + b * b;
	}
	else {
	x += 1;
	y -= 1;
	dx += 2 * b * b;
	dy -= 2 * a * a;
	d1 += dx - dy + b * b;
	}
	}
	double d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
	while (y >= 0) {
	// Set RGB values of pixels on ellipse to white
	int index1 = ((int)(centerY + y *cos(angle) - x * sin(angle)) * width + (int)(centerX + x * cos(angle) + y * sin(angle))) * 3;
	imageData[index1] = 0;
	imageData[index1 + 1] = 255;
	imageData[index1 + 2] = 0;
	int index2 = ((int)(centerY - y * cos(angle) - x * sin(angle)) * width + (int)(centerX + x * cos(angle) - y * sin(angle))) * 3;
	imageData[index2] = 0;
	imageData[index2 + 1] = 255;
	imageData[index2 + 2] = 0;
	int index3 = ((int)(centerY - y * cos(angle) + x * sin(angle)) * width + (int)(centerX - x * cos(angle) - y * sin(angle))) * 3;
	imageData[index3] = 0;
	imageData[index3 + 1] = 255;
	imageData[index3 + 2] = 0;
	int index4 = ((int)(centerY + y * cos(angle) + x * sin(angle)) * width + (int)(centerX - x * cos(angle) + y * sin(angle))) * 3;
	imageData[index4] = 0;
	imageData[index4 + 1] = 255;
	imageData[index4 + 2] = 0;
	if (d2 > 0) {
	y -= 1;
	dy -= 2 * a * a;
	d2 += a * a - dy;
	}
	else {
	y -= 1;
	x += 1;
	dx += 2 * b * b;
	dy -= 2 * a * a;
	d2 += dx - dy + a * a;
	}
	}
}
if(fill==1)
{
	while (dx < dy) {
	 // Set RGB values of pixels inside ellipse to white
	 for (int i = centerX - x; i <= centerX + x; i++) {
	 for (int j = centerY - y; j <= centerY + y; j++) {
	 double dx1 = i - centerX;
	 double dy1 = j - centerY;
	 double dx2 = dx1 * cos(angle) + dy1 * sin(angle);
	 double dy2 = -dx1 * sin(angle) + dy1 * cos(angle);
	 if (dx2 * dx2 / (a * a) + dy2 * dy2 / (b * b) <= 1) {
	 int index = (j * width + i) * 3;
	 imageData[index] = 255;
	 imageData[index + 1] = 255;
	 imageData[index + 2] = 255;
	 }
	 }
	 }
	 if (d1 < 0) {
	 x += 1;
	 dx += 2 * b * b;
	 d1 += dx + b * b;
	 }
	 else {
	 x += 1;
	 y -= 1;
	 dx += 2 * b * b;
	 dy -= 2 * a * a;
	 d1 += dx - dy + b * b;
	 }
	}
	double d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
	while (y >= 0) {
	 // Set RGB values of pixels inside ellipse to white
	 for (int i = centerX - x; i <= centerX + x; i++) {
	 for (int j = centerY - y; j <= centerY + y; j++) {
	 double dx1 = i - centerX;
	 double dy1 = j - centerY;
	 double dx2 = dx1 * cos(angle) + dy1 * sin(angle);
	 double dy2 = -dx1 * sin(angle) + dy1 * cos(angle);
	 if (dx2 * dx2 / (a * a) + dy2 * dy2 / (b * b) <= 1) {
	 int index = (j * width + i) * 3;
	 imageData[index] = 0;
	 imageData[index + 1] = 255;
	 imageData[index + 2] = 0500;
	 }
	 }
	 }
	 if (d2 > 0) {
	 y -= 1;
	 dy -= 2 * a * a;
	 d2 += a * a - dy;
	 }
	 else {
	 y -= 1;
	 x += 1;
	 dx += 2 * b * b;
	 dy -= 2 * a * a;
	 d2 += dx - dy + a * a;
	 }
	}
}
else
{
	printf("Error:Please enter valid fill value");
}
// Stop timer
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
// Display time taken
printf("Time taken: %f seconds\n", timeTaken);
return 0;
}
