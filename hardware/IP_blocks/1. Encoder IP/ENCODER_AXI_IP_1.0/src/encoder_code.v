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
////
// Source: https://www.fpga4fun.com/QuadratureDecoder.html
////

`timescale 1ns / 1ps

module quad(input clk, 
            input quadA, 
            input quadB, 
            output wire [31:0] count_o);
            
//input clk, quadA, quadB;
reg [31:0] count;
initial count = 32'h7FFFFFFF;

reg quadA_delayed, quadB_delayed;
always @(posedge clk) quadA_delayed <= quadA;
always @(posedge clk) quadB_delayed <= quadB;

wire count_enable = quadA ^ quadA_delayed ^ quadB ^ quadB_delayed;
wire count_direction = quadA ^ quadB_delayed;

//reg [31:0] count;
always @(posedge clk)
    begin
        if(count_enable)
            begin
                if(count_direction) count<=count+1; else count<=count-1;
            end
    end

assign count_o = count;
endmodule
