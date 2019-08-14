SoC-PROGO / MSc project - Repository

Heriot-Watt University - MACS

August 2019

 Board: PYNQ-Z2
 
 System on Chip: Zynq 7020

 Title: Design and Implementation of a System on Chip Architecture and a Domain Specific Language for a Programmable Ground Rover
 
 Abstract:  
Autonomous ground rovers make it possible to realise a wide range of useful tasks deployed in real world scenarios. These include swam robotics, object tracking, and simultaneous localisation and mapping (SLAM). To maximise their autonomy they must consume energy efficiently. For wide adoption they must be easy to program. In dynamic environments with moving objects and with uneven terrain, they must be capable of sensing their physical environment in real-time and perform on-the-spot tank turns.

The problem with many existing ground rovers is that they are developed with one of these goals in mind. For example, they may consume energy efficiently but cannot be repurposed beyond a hard coded predefined algorithm, or a rover is programmable but uses a general purpose software stack that is both energy inefficient and unable to process sensor data in real-time.

This dissertation presents the design and implementation of a new ground rover designed and implemented from scratch, called SoC-PROGO (System on Chip architecture for a PROgrammable Ground rOver). It comprises a mechanical robot, a heterogeneous SoC architecture that makes use of an ARM CPU and a FPGA, and a Domain Specific Language (DSL) to easily write algorithms for the rover to carry out.

The functional correctness and scalability of the DSL is evaluated, as is the energy efficiency of SoC-PROGO. SoC-PROGO is available both as open source hardware and open source software, enabling future work to evaluate SoC-PROGO and its DSL with state-of-the-art SLAM and autonomous tracking algorithms.

