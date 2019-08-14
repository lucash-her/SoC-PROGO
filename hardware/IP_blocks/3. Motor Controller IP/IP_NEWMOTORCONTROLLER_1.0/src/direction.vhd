----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 07.03.2019 12:01:18
-- Design Name: 
-- Module Name: direction - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------
-- 
-- 
-- Copyright (c) 2019 Lucas HERAUD
-- 
-- Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
-- to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
-- and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
-- 
-- The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
-- 
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- ITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
-- WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-- 
--
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity direction is

  
  Port (clk : IN STD_LOGIC;
        motor_position : IN STD_LOGIC;          -- LEFT or RIGHT
        direction_choice : IN STD_LOGIC;        -- FORWARD or BACKWARD
        motor_rotation_dir : OUT STD_LOGIC);    -- Depending on the two last parameter, it give the direction the motor chould turn
end direction;

architecture Behavioral of direction is
  constant LEFT             : STD_LOGIC := '0';
  constant RIGHT            : STD_LOGIC := '1';
  constant FORWARD          : STD_LOGIC := '0';
  constant BACKWARD         : STD_LOGIC := '1';
  
  constant CLOCK_WISE       : STD_LOGIC := '0';
  constant ANTI_CLOCK_WISE  : STD_LOGIC := '1';
  
begin
    process(clk)
    begin
        if (clk'EVENT AND clk = '1') then
            
            -- If motor on the left of robot            
            if (motor_position = LEFT) then
                
                -- If asked to go forward
                if (direction_choice = FORWARD) then
                    motor_rotation_dir <= CLOCK_WISE;
                
                -- Else If asked to go Backward                                
                else
                    motor_rotation_dir <= ANTI_CLOCK_WISE;
                end if;
                
            -- Else if motor on the right of robot
            else
                -- If asked to go forward
                if (direction_choice = FORWARD) then
                    motor_rotation_dir <= ANTI_CLOCK_WISE;
                
                -- Else If asked to go backward                
                else
                    motor_rotation_dir <= CLOCK_WISE;
                end if;
            end if;      
        end if;

    end process;
end Behavioral;
