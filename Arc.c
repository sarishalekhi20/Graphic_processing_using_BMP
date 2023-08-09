#include <stdint.h>
#include <math.h>6
#include "header.h"
#include <stdio.h>
void drawArc(uint8_t* imageData, int width, int height) {
int centerX, centerY, radius, angleStart, angleEnd;
printf("Enter the coordinates of the center (x y): ");
scanf("%d %d", &centerX, &centerY);
printf("Enter the radius: ");
scanf("%d", &radius);
printf("Enter the starting angle (in degrees): ");
scanf("%d", &angleStart);
printf("Enter the ending angle (in degrees): ");
scanf("%d", &angleEnd);
if (centerX > 1024 || centerY > 1024 || radius > 1024) {
printf("Error: wrong coordinates\n");
return;
}
// Convert angles from degrees to radians
double startRad = angleStart * M_PI / 180.0;
double endRad = angleEnd * M_PI / 180.0;
int fill;
printf("Press 1 for a filled arc, press 0 for an empty arc: ");
scanf("%d", &fill);
if (fill == 0) {
// Draw the empty arc
for (double theta = startRad; theta <= endRad; theta += 0.003) {
int x = centerX + radius * cos(theta);
int y = centerY + radius * sin(theta);
if (x >= 0 && x < width && y >= 0 && y < width) {
int index = (y * width + x) * 3;
imageData[index] = 0; // Blue component
imageData[index + 1] = 255; // Green component
imageData[index + 2] = 0; // Red component
}
}
// Draw lines from center to start and end points of the arc
int startX = centerX + radius * cos(startRad);
int startY = centerY + radius * sin(startRad);
int endX = centerX + radius * cos(endRad);
int endY = centerY + radius * sin(endRad);
drawLineC(imageData, width, startX, startY, centerX, centerY);
drawLineC(imageData, width, endX, endY, centerX, centerY);
}
else if (fill == 1) {
// Draw the filled arc
	 int x, y;
	 double distance, angle;
	 for (x = 0; x < width; x++) {
	 for (y = 0; y < height; y++) {
	 // Calculate the distance from the center of the image
	 distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
	 // Check if the pixel falls within the arc
	 if (distance <= radius) {
	 // Calculate the angle of the pixel
	 angle = atan2(y - centerY, x - centerX);
	 // Check if the angle is within the desired range
	 if (startRad <= angle && angle <= endRad) {
	 // Set the pixel value to the desired color
	 	 int index = (y * width + x) * 3;
	 	 imageData[index] = 0; // Blue component
	 	 imageData[index + 1] = 255; // Green component
	 	 imageData[index + 2] = 0; // Red component
	 }
	 }
	 }
	 }
}
else {
printf("Error: enter a valid fill value (0 or 1)\n");
}
}
