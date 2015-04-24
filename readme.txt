------------------------

Assignment: [OS lab1] OS state
----------


Description:
-----------
Use C++ to extract the system information from files in /proc.

My assignment solution consists of the following files:
OS_state.cpp
OS_state
makefile
readme.txt


Running my solution:
-------------------
You can run my assignment as follows:
> make
> ./OS_state

Compiler:
------------
g++

Running procedure:
-----------------
This lab consists of 2 parts: Part A and Part B.
First, run Part A following :
> ./OS_state
Secondly, run Part B following:
> ./OS_state 2 60

Assumptions:
-----------
For Part B, you need to give 2 arguments to the program. And the second agrument (sampling time) is several times larger than the first argument(period time). 

Conclusions/Remarks:
-------------------
I had problems to split a line into several words. For me, this is the most difficult part in this lab. I ended up with using a function called "split" in boost c++ library to solve this problem.


Errors/Bugs:
-------------------
I think there is error in Part B. The average amount of time of the processor in the idle mode is too large. I'm pretty sure the absolute value I get in Part A is correctly. Just this value changed too fast during the sampling period time. 
