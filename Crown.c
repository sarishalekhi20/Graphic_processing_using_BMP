#include <stdint.h>
#include <math.h>
#include "header.h"
#include <stdio.h>
void drawCrown(uint8_t* imageData, int width, int height) {
int centerX, centerY, innerRadius, outerRadius, angleStart,angleEnd,
	indent, visb, styleset;
printf("Enter widget id: ");
scanf("%d", &indent);
printf("Visibility(if you want it to be visible enter 1, else enter 0):");
scanf("%d", &visb);
printf("Enter the styleset: ");
scanf("%d", &styleset);
printf("Enter the coordinates of the center (x y): ");
scanf("%d %d", &centerX, &centerY);
printf("Enter the inner radius: ");
scanf("%d", &innerRadius);
printf("Enter the outer radius: ");
scanf("%d", &outerRadius);
printf("Enter the starting angle (in degrees): ");
scanf("%d", &angleStart);
printf("Enter the ending angle (in degrees): ");
scanf("%d", &angleEnd);
if (centerX > 1024 || centerY > 1024 || innerRadius > 1024 || outerRadius > 1024 || outerRadius <=innerRadius){
printf("Error: wrong coordinates or radius\n");
return;
}
// Convert angles from degrees to radians
double startRad = angleStart * M_PI / 180.0;
double endRad = angleEnd * M_PI / 180.0;
int fill;
	 printf("Please enter 1 if you want a filled crown and 0 if you want it to be empty");
	 scanf("\n%d", &fill);
	 if(fill==0)
	 {
		 // Draw the outer arc
		 for (double theta = startRad; theta <= endRad; theta += 0.002){
		 int x = centerX + outerRadius * cos(theta);
		 int y = centerY + outerRadius * sin(theta);
		 if (x >= 0 && x < width && y >= 0 && y < width) {
		 int index = (y * width + x) * 3;
		 imageData[index] = 0; // Blue component
		 imageData[index + 1] = 255; // Green component
		 imageData[index + 2] = 0; // Red component
		 }
		 }
		 // Draw the inner arc
		 for (double theta = startRad; theta <= endRad; theta += 0.003){
		 int x = centerX + innerRadius * cos(theta);
		 int y = centerY + innerRadius * sin(theta);
		 if (x >= 0 && x < width && y >= 0 && y < width) {
		 int index = (y * width + x) * 3;
		 imageData[index] = 0; // Blue component
		 imageData[index + 1] = 255; // Green component
		 imageData[index + 2] = 0; // Red component
		 }
		 }
		 int outerStartX = centerX + outerRadius * cos(startRad);
		 int outerStartY = centerY + outerRadius * sin(startRad);
		 int outerEndX = centerX + outerRadius * cos(endRad);
		 int outerEndY = centerY + outerRadius * sin(endRad);
		 int innerStartX = centerX + innerRadius * cos(startRad);
		 int innerStartY = centerY + innerRadius * sin(startRad);
		 int innerEndX = centerX + innerRadius * cos(endRad);
		 int innerEndY = centerY + innerRadius * sin(endRad);
		 // Draw lines between the end points
		 drawLineC(imageData, width, outerStartX, outerStartY, innerStartX, innerStartY);
		 drawLineC(imageData, width, outerEndX, outerEndY, innerEndX, innerEndY);
	 }
	 else if(fill==1){
		 int x, y;
		 double distance, angle;
		 for (x = 0; x < width; x++) {
		 for (y = 0; y < height; y++) {
		 distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
		 angle = atan2(y - centerY, x - centerX);
		 if (innerRadius <= distance && distance <= outerRadius && startRad <= angle && angle <= endRad) {
		 int index = (y * width + x) * 3;
		 imageData[index] = 0; // Blue component
		 imageData[index + 1] = 255; // Green component
		 imageData[index + 2] = 0; // Red component
		 }
		 }
		 }
	 }
	 else{
		 printf("Error:please enter valid value of fill");
	 }
}
void drawLineC(uint8_t* imageData, int width, int x1, int y1, int x2, int y2) {
int dx = abs(x2 - x1);
int dy = abs(y2 - y1);
int sx = (x1 < x2) ? 1 : -1;
int sy = (y1 < y2) ? 1 : -1;
int err = dx - dy;
while (1) {
int index = (y1 * width + x1) * 3;
imageData[index] = 0; // Blue component
imageData[index + 1] = 255; // Green component
imageData[index + 2] = 0; // Red component
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
