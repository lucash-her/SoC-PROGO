//////////////////////////////////////////////////////////////////////////////////
// Company: Heriot-Watt University - MACS
// Engineer: Lucas HERAUD
// 
// Create Date: 26.02.2019 15:37:09
// Design Name: 
// Module Name: hc_sr04.v
// Project Name: 
// Target Devices: PYNQ-Z2
// Tool Versions: 
// Description: HC SR04 Sensor
//      calculate the distance to objetc (in cm)
// 
// Dependencies: 
// 
// Revision:
// Revision 1.00 - Working module
// Additional Comments:
//      Inspired by https://github.com/borisfba/fpga-distance/blob/master/sonic.v
// 
//////////////////////////////////////////////////////////////////////////////////
/*
 *
 * Copyright (c) 2019 Lucas HERAUD
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
 
module ultrasonic(
   input clock,                 // 100MHz Clock
	output trig,                // Binary signal
	input echo,                 // Binary signal
	output reg [32:0] distance  // Distance in cm 
);

reg [32:0] us_counter = 0;
reg _trig = 1'b0;

reg [9:0] one_us_cnt = 0;
wire one_us = (one_us_cnt == 0);

// Trigger Pulce
reg [9:0] ten_us_cnt = 0;
wire ten_us = (ten_us_cnt == 0);

// Measurment Cycle
reg [21:0] seventy_ms_cnt = 0;
wire seventy_ms = (seventy_ms_cnt == 0);

assign trig = _trig;

always @(posedge clock) begin
	one_us_cnt <= (one_us ? 100 : one_us_cnt) - 1;
	
	// Trigger pulce 
	ten_us_cnt <= (ten_us ? 1000 : ten_us_cnt) - 1;
	 
	// Measurment Cycle
	seventy_ms_cnt <= (seventy_ms ? 7000000 : seventy_ms_cnt) - 1; 
	
	// If trigger pulce still on but the cycle should end 
	if (ten_us && _trig)
		_trig <= 1'b0;
	
	// Check if echo has arrived and calculate distance (at each us)
	if (one_us) begin	
		if (echo)
			us_counter <= us_counter + 1;
		else if (us_counter) begin
		    // Formula available on sensor datasheet
			distance <= us_counter / 58; 
			us_counter <= 0;
		end
	end
	
   // If new measurment cycle, we send trigger pulce 
   if (seventy_ms)
		_trig <= 1'b1;
end

endmodule
