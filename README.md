# Depth of market simulator.
Author: @jzry, all right reserved.

## About
This algorithm is designed to extract extract statistics from intraday depth of market. Input stream may be changed, but the default input is user generated and simulated for showcase.

## Demo
Open your command line and do the following:
1) type "g++ DOM.cpp" in the command line in the same directory that the cpp file is in.
2) type "./a.out (number of orders)" in the terminal -- put in the number of randomly assigned orders you would like to simulate.
3) Change MAX_RAND_VAL to any number to change max order limit.
4) Toggle DEBUG to either 0 or 1 if you want to see some debugging hints.

## Custom Input Parameters
The default input parameters are user generated through the command line, however if you would like to implement streaming data (real time data, yahoo finance, etc), then change the INPUT tag from DEFAULT to CUSTOM.
