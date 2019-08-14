/*
 * dsl.c
 *
 *  Created on: Aug 2, 2019
 *      Author: lucas
 */


	/**
 *
Copyright (c) 2015 Jonas Galdikas
Permission  is  hereby  granted,  free  of  charge,  to  any  person  obtaining  a  copy  of  this software and associated documentation files (the �Software�),  to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/

/*
 * dsl.c
 *
 *  Created on: Aug 2, 2019
 *      Author: lucas
 */

#include "dsl.h"


/****
 * 		Private Function
 ****/

void odom()
{
	u32 l_samp, r_samp;
	s32  l_ticks, r_ticks;
	s32 l_dist_mm, r_dist_mm, dist_mm;

	//INIT
	l_samp = 0;
	r_samp = 0;
	l_ticks = 0;
	r_ticks = 0;



	usleep(10000); //20 ms

		/* Read raw value from encoders */
	l_samp = Xil_In32 (XPAR_ENCODER_AXI_IP_0_S00_AXI_BASEADDR) ;
	r_samp = Xil_In32 (XPAR_ENCODER_AXI_IP_1_S00_AXI_BASEADDR) ;

	/* Determine how many ticks sience last reading */
	l_ticks = (s32)(l_samp - last_l);
	r_ticks = (s32)(r_samp - last_r);


	/* Update last reading for next loop */
	last_l = l_samp;
	last_r = r_samp;

	if( (l_ticks < TOLERANCE_TICK) && (l_ticks > -TOLERANCE_TICK) )
	{
		if( (r_ticks < TOLERANCE_TICK) && (r_ticks > -TOLERANCE_TICK) )
		{

			/* Ticks to cm conversion */
			l_dist_mm = l_ticks/LEFT_TICKS_PER_MM;
			r_dist_mm = r_ticks/RIGHT_TICKS_PER_MM;

			/* calculate dist traveled since last loop */
			dist_mm = (l_dist_mm + r_dist_mm) / 2;
			g_dist = g_dist + dist_mm;
			g_absolute_dist = g_absolute_dist + dist_mm;

			/* accumulate total rotation around center */
			g_theta += (float)(l_dist_mm - r_dist_mm) / (float)(WHEEL_BASE_MM);
			g_theta -= (float)((int)(g_theta/M_TWOPI))*M_TWOPI;

			g_absolute_theta += (float)(l_dist_mm - r_dist_mm) / (float)(WHEEL_BASE_MM);
			g_absolute_theta -= (float)((int)(g_absolute_theta/M_TWOPI))*M_TWOPI;


			/* Update coords */
			g_X_pos += (s32)(dist_mm * cos(g_absolute_theta));
			g_Y_pos += (s32)(dist_mm * sin(g_absolute_theta));
		}
		else{
			xil_printf( "### Incoherent val : r_ticks: %d\n\r ", r_ticks);
		}
	}

	else{
		xil_printf( "### Incoherent val : l_ticks: %d \n\r ", l_ticks);
	}
}


/****
 * 		DSL Function
 ****/


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
int goForward(s32 i_distance_mm)
{
	xil_printf("____ FORWARD (%d mm) ____\n\r",i_distance_mm);


	g_dist = 0;
	g_theta = 0;

	last_l = Xil_In32 (XPAR_ENCODER_AXI_IP_0_S00_AXI_BASEADDR) ;
	last_r = Xil_In32 (XPAR_ENCODER_AXI_IP_1_S00_AXI_BASEADDR) ;


	/////////////////////////////////////////////////////// Forward


	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x01 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x00 ) ;


	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x98  ) ;


	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x98  ) ;

			/////////////////
			/// ODOM CODE ///
			/////////////////

	while(g_dist < i_distance_mm)
	{
		odom();
	};

	/////////////////////////////////////////////////////// STOP
	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x00 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x01 ) ;

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x98  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x98  ) ;

	usleep(10000);

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x00  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x00  ) ;

	odom();

	///////////////////////////////////////////////////////

	return XST_SUCCESS;
}


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
int goBackward(s32 i_distance_mm)
{
	s32 distance_mm;

	distance_mm = (- i_distance_mm);


	xil_printf("____ BACKWARD (%d cm) ____\n\r",distance_mm);

	g_dist = 0;
	g_theta = 0;

	last_l = Xil_In32 (XPAR_ENCODER_AXI_IP_0_S00_AXI_BASEADDR) ;
	last_r = Xil_In32 (XPAR_ENCODER_AXI_IP_1_S00_AXI_BASEADDR) ;


	/////////////////////////////////////////////////////// Forward


	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x00 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x01 ) ;

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x98  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x98  ) ;


			/////////////////
			/// ODOM CALL ///
			/////////////////
	while(g_dist > distance_mm)
	{
		odom();
	};

	//================== STOP ==================//
	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x01 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x00 ) ;

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x98  ) ;


	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x98  ) ;

	usleep(10000);

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x00  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x00  ) ;

	odom();

	///////////////////////////////////////////////////////

	return XST_SUCCESS;

}


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
int rotateLeft(float i_deg)
{
	float i_rad;

	g_dist = 0;
	g_theta = 0;

	i_rad = -i_deg* M_PI /180;

	last_l = Xil_In32 (XPAR_ENCODER_AXI_IP_0_S00_AXI_BASEADDR) ;
	last_r = Xil_In32 (XPAR_ENCODER_AXI_IP_1_S00_AXI_BASEADDR) ;

	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x00 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x00 ) ;


	///////////////////////////////////////////////////////


	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0xA0  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0xA0  ) ;

	while( i_rad < g_theta )
	{
		odom();
	};


	/********** STOP **********/

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x00  ) ;


	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x00  ) ;

	return XST_SUCCESS;
}


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
int rotateRight(float i_deg)
{
	float i_rad;

	g_dist = 0;
	g_theta = 0;

	i_rad = i_deg* M_PI /180;

	last_l = Xil_In32 (XPAR_ENCODER_AXI_IP_0_S00_AXI_BASEADDR) ;
	last_r = Xil_In32 (XPAR_ENCODER_AXI_IP_1_S00_AXI_BASEADDR) ;

	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x01 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x01 ) ;

	///////////////////////////////////////////////////////

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0xA7  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0xA7 ) ;

	while( i_rad > g_theta )
	{
		odom();
	};


	/********** STOP **********/

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x00  ) ;


	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x00  ) ;


	return XST_SUCCESS;
}


/*****************************************************************************
* This function drives the robot forward until the Ultra Sonic sensor detect an obstacle
*
* @param	None.
* @return	XST_SUCCESS if successful else XST_FAILURE.
* @note    None.
*
******************************************************************************/
int goForwardUntil(){

	u32 read_ultra = 0;

	g_dist = 0;
	g_theta = 0;

	last_l = Xil_In32 (XPAR_ENCODER_AXI_IP_0_S00_AXI_BASEADDR) ;
	last_r = Xil_In32 (XPAR_ENCODER_AXI_IP_1_S00_AXI_BASEADDR) ;


	/////////////////////////////////////////////////////// Forward


	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x01 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x00 ) ;


	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x98  ) ;


	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x98  ) ;

	/* Reading UltraSonic Sensor */
	// While no obstacle at 20 cm
	do{
		odom();
		//read_ultra = Xil_In32(XPAR_HCSR04_AXI_IP_0_S00_AXI_BASEADDR);
	}while(read_ultra > 50);



	/////////////////////////////////////////////////////// STOP
	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x00 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x01 ) ;

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x98  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x98  ) ;

	usleep(10000);

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x00  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x00  ) ;

	odom();

	///////////////////////////////////////////////////////

	return XST_SUCCESS;
}

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
int goBackwardUntil(void)
{
	u32 read_ultra = 0;

	g_dist = 0;
	g_theta = 0;

	last_l = Xil_In32 (XPAR_ENCODER_AXI_IP_0_S00_AXI_BASEADDR) ;
	last_r = Xil_In32 (XPAR_ENCODER_AXI_IP_1_S00_AXI_BASEADDR) ;


	/////////////////////////////////////////////////////// Forward


	/** LEFT - M1**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 4, 0x00 ) ;

	/** RIGHT - M2**/
	// Motor Direction
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 4, 0x01 ) ;

	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x98  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x98  ) ;


	/* Reading UltraSonic Sensor */
	// While no obstacle at 20 cm
	do{
		odom();
	//	read_ultra = Xil_In32(XPAR_HCSR04_AXI_IP_1_S00_AXI_BASEADDR);
	}while(read_ultra > 50);



	/** LEFT - M1**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_0_S00_AXI_BASEADDR + 8, 0x00  ) ;

	/** RIGHT - M2**/
	// Set Duty Cycle to
	Xil_Out32 (XPAR_IP_NEWMOTORCONTROLLER_1_S00_AXI_BASEADDR + 8, 0x00  ) ;

	odom();

	///////////////////////////////////////////////////////

	return XST_SUCCESS;
}



/*****************************************************************************
* This function returns the X coordinate of the ground robot
*
* @param	None.

* @return	The X coordinate (in mm) of the ground rover (in relation to the origin)

* @note    None.
*
******************************************************************************/
s32 getX_coord()
{
	return g_X_pos;
}

/*****************************************************************************
* This function returns the Y coordinate of the ground robot
*
* @param	None.
* @return	The Y coordinate (in mm) of the ground rover (in relation to the origin)
* @note    None.
*
******************************************************************************/
s32 getY_coord()
{
	return g_Y_pos;
}

/*****************************************************************************
* This function returns radial distance of the ground robot
*
* @param	None.
* @return	The radial distance (in mm) of the ground robot from the origin
* @note    None.
*
******************************************************************************/
s32 getRadial_distance()
{
	return g_absolute_dist;
}

/*****************************************************************************
* This function returns the polar angle of the ground robot
*
* @param	None.
* @return   The polar angle (in degree) of the ground robot
* @note    None.
*
******************************************************************************/
s32 getPolar_angle()
{
	s32 angle_deg;

	angle_deg = (s32)(g_absolute_theta * 180 / M_PI);

	return angle_deg;
}
