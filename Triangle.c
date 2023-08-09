#include <stdint.h>
#include <math.h>
#include "header.h"
#include <stdio.h>
void drawTriangle(uint8_t* imageData, int width, int height)
{
	 // Draw the triangle
	 int x1, y1, x2, y2, x3, y3;
	 printf("Enter the coordinates of the second endpoint (x1 y1): ");
	 	 scanf("%d %d", &x1, &y1);
	 printf("Enter the coordinates of the first endpoint (x2 y2): ");
	 	 	 scanf("%d %d", &x2, &y2);
	 printf("Enter the coordinates of the second endpoint (x3 y3): ");
	 	 	 	scanf("%d %d", &x3, &y3);
	 	 	 if (x2 > 1024 || x1 > 1024 || y2 > 1024 || y1 > 1024 || x3>1024 ||y3>1024) {
	 	 	 printf("Error: wrong coordinates\n");
	 	 	 }
	 int fill;
	 printf("Please enter 1 if you want a filled triangle adn 0 if you want it to be empty");
	 scanf("\n%d", &fill);
	 if(fill==1)
	 {
		 if (y1 > y2) {
		 	 	 swap(&x1, &x2);
		 	 	 swap(&y1, &y2);
		 	 	 }
		 	 	 if (y1 > y3) {
		 	 	 swap(&x1, &x3);
		 	 	 swap(&y1, &y3);
		 	 	 }
		 	 	 if (y2 > y3) {
		 	 	 swap(&x2, &x3);
		 	 	 swap(&y2, &y3);
		 	 	 }
		 	 	 // Calculate slopes of the two triangle edges
		 	 	 float slope1 = (float)(x2 - x1) / (y2 - y1);
		 	 	 float slope2 = (float)(x3 - x1) / (y3 - y1);
		 	 	 // Draw the filled triangle
		 	 	 for (int y = y1; y <= y3; y++) {
		 	 	 int startX = x1 + (y - y1) * slope1;
		 	 	 int endX = x1 + (y - y1) * slope2;
		 	 	 if (startX > endX) {
		 	 	 swap(&startX, &endX);
		 	 	 }
		 	 	 for (int x = startX; x <= endX; x++) {
		 	 	 if (x >= 0 && x < width && y >= 0 && y < height) {
		 	 	 int index = (y * width + x) * 3;
		 	 	 imageData[index] = 0; // Red component
		 	 	 imageData[index + 1] = 255; // Green component
		 	 	 imageData[index + 2] = 0; // Blue component
		 	 	 }
		 	 	 }
		 	 	 }
	 }
	 else if(fill==0)
	 {
		 // Draw the boundary of the triangle
		 drawLineT(imageData, width, height, x1, y1, x2, y2);
		 drawLineT(imageData, width, height, x2, y2, x3, y3);
		 drawLineT(imageData, width, height, x3, y3, x1, y1);
	 }
	 else
	 {
		 printf("Error: please enter valid fill");
	 }
}
void drawLineT(uint8_t* imageData, int width, int height, int x1, int y1, int x2, int y2) {
int bytesPerPixel = 3; // Assuming 24-bit BMP (3 bytes per pixel)
// Bresenham's line algorithm
int dx = abs(x2 - x1);
int dy = abs(y2 - y1);
int sx = (x1 < x2) ? 1 : -1;
int sy = (y1 < y2) ? 1 : -1;
int err = dx - dy;
while (1) {
if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
int index = (y1 * width + x1) * bytesPerPixel;
imageData[index] = 0; // Red component
imageData[index + 1] = 255; // Green component
imageData[index + 2] = 0; // Blue component
}
if (x1 == x2 && y1 == y2) {
break;
}
int e2 = 2 * err;
if (e2 > -dy) {
err -= dy;
x1 += sx;
}
if (e2 < dx) {
err += dx;
y1 += sy;
}
}
}
void swap(int* a, int* b) {
int temp = *a;
*a = *b;
*b = temp;
}
