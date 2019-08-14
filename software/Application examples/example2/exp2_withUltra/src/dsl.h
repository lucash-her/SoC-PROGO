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

#ifndef SRC_DSL_H_
#define SRC_DSL_H_

#include "xparameters.h"
#include "xil_io.h"
#include "xbasic_types.h"
#include "sleep.h"
#include "math.h"
#include "xstatus.h"


/*** For Odom ***/
#define LEFT_TICKS_PER_MM		2.26
#define RIGHT_TICKS_PER_MM 		2.26

#define TOLERANCE_TICK 			100


#define WHEEL_BASE_MM 			245


float g_absolute_theta;
float g_theta;

s32 g_X_pos;
s32 g_Y_pos;

s32 g_dist;
s32 g_absolute_dist;

s32 last_l, last_r;


/*****************************************************************************
* This function drives the robot forward for a given distance
*
* @param	i_distance_cm contains the distance (in mm) the robot has to reach before stopping
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note    None.
*
******************************************************************************/
int goForward(s32 i_distance_mm);

/*****************************************************************************
* This function drives the robot backward for a given distance
*
* @param	i_distance_mm contains the distance (in mm) the robot has to reach before stopping
*
* @return	XST_SUCCESS if successful else XST_FAILURE
*
* @note     None.
*
******************************************************************************/
int goBackward(s32 i_distance_mm);

/*****************************************************************************
* This function turn the robot left for a given angle (Tank Turn)
*
* @param	i_angle_deg contains the angle (in deg) the robot has to turn to the left (tank turn)
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note    None.
*
******************************************************************************/
int rotateLeft(float i_deg);

/*****************************************************************************
* This function turn the robot right for a given angle (Tank Turn)
*
* @param	i_angle_deg contains the angle (in deg) the robot has to turn to the right (tank turn)
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note    None.
*
******************************************************************************/
int rotateRight(float i_deg);



/*****************************************************************************
* This function drives the robot forward until the Ultra Sonic sensor detect an obstacle
*
* @param	None.
* @return	XST_SUCCESS if successful else XST_FAILURE.
* @note    None.
*
******************************************************************************/
int goForwardUntil(void);

/*****************************************************************************
* This function drives the robot backward until the Ultra Sonic sensor detect an obstacle
*
* @param	None.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note    None.
*
******************************************************************************/
int goBackwardUntil(void);


/*****************************************************************************
* This function returns the X coordinate of the ground robot
*
* @param	None.
* @return	The X coordinate (in mm) of the ground rover (in relation to the origin)
* @note    None.
*
******************************************************************************/
s32 getX_coord();

/*****************************************************************************
* This function returns the Y coordinate of the ground robot
*
* @param	None.
* @return	The Y coordinate (in mm) of the ground rover (in relation to the origin)
* @note    None.
*
******************************************************************************/
s32 getY_coord();

/*****************************************************************************
* This function returns radial distance of the ground robot
*
* @param	None.
* @return	The radial distance (in mm) of the ground robot from the origin
* @note    None.
*
******************************************************************************/
s32 getRadial_distance();

/*****************************************************************************
* This function returns the polar angle of the ground robot
*
* @param	None.
* @return   The polar angle (in degree) of the ground robot
* @note    None.
*
******************************************************************************/
s32 getPolar_angle();


/*****************************************************************************
* This function returns the distance to the closest obstacle detected by the front Ultra Sonic sensor
*
* @param	None.
*
* @return	Distance (in mm) to the closest obstacle detected by the front Ultra Sonic sensor
*
* @note    None.
*
******************************************************************************/
u32 getDistToObstacle_frontSensor(void);

/*****************************************************************************
* This function returns the distance to the closest obstacle detected by the back Ultra Sonic sensor
*
* @param	None.
*
* @return	Distance (in mm) to the closest obstacle detected by the front Ultra Sonic sensor
*
* @note    None.
*
******************************************************************************/
u32 getDistToObstacle_backSensor(void);



#endif /* SRC_DSL_H_ */
