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

/**** Experience 2 : Driving C indifenetly ****/
int main(){

	u32 loop;;

	xil_printf( "Experience 2 - C with ultra \n\r ");


	while(1)
	{
		goForward(2000); // 2 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		goForward(1000); // 1 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		goForward(1000); // 1 m
		sleep(1);
		rotateRight(90);
		sleep(1);

		goForward(2000); // 2 m
		sleep(1);
		rotateRight(90);
		sleep(1);

		goForward(1000); // 1 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		goForward(1000); // 1 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		goForward(2000); // 2 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		goForward(3000); // 3 m
		sleep(1);
		rotateLeft(90);
		sleep(1);

		xil_printf( "Loop %d Done \n\r", loop);
		loop += 1;
	};


	xil_printf( "Experience 1 Done \n\r");


	return 0;
}
