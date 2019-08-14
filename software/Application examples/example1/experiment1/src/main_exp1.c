/*
 *
 * Copyright (c) 2019 Lucas HERAUD
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ”Software”),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED ”AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#include "dsl.h"



/**** Experience 1 : Driving in square ****/
int main(){

	s32 polarAngle, radialDistance;

	xil_printf( "Experience 1 - Square \n\r ");


	for(int idx = 0; idx < 5; idx++)
	{
		goForward(500); // 1 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		radialDistance = getRadial_distance();
		polarAngle = getPolar_angle();
		xil_printf( "1- Distance = %d mm - Angle = %d deg \n\r", radialDistance, polarAngle);

		goForward(500); // 1 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		radialDistance = getRadial_distance();
		polarAngle = getPolar_angle();
		xil_printf( "2- Distance = %d mm - Angle = %d deg \n\r", radialDistance, polarAngle);


		goForward(500); // 1 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		radialDistance = getRadial_distance();
		polarAngle = getPolar_angle();
		xil_printf("3- Distance = %d mm - Angle = %d deg \n\r", radialDistance, polarAngle);


		goForward(500); // 1 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		radialDistance = getRadial_distance();
		polarAngle = getPolar_angle();
		xil_printf( "Distance = %d mm - Angle = %d deg \n\r", radialDistance, polarAngle);
	}
	xil_printf( "Experience 1 Done \n\r");


	return 0;
}
