TLSF (Two-Level Segregate Fit) :
==============================

TLSF is a design that has cost of O(1) for dynamic memory allocation and deallocation for real time requirement.

Bounded Response Time : 
-----------------------

The worst-case execution time (WCET) of memory allocation and deallocation has be independent of application data. TLSF has a constant cost O(1).

Fast :
-------- 

Additionally to a bounded cost, the allocator has to be efficient and fast enough. TLSF executes a maximum of 168 processor instructions in a x86 architecture. Depending on the compiler version and optimisation flags, it can be slightly lower or higher.

Efficient Memory Use : 
-----------------------

Traditionally, real-time systems run for long periods of time and some (embedded applications), have strong constraints of memory size. Fragmentation can have a significant impact on such systems. A way to measure this efficiency is the memory fragmentation incurred by the allocator. TLSF has an average fragmentation lower than 15 %. The maximum fragmentation measured is lower than 25%.

USAGE :
--------

The program is in C language. You simply must have a C compiler.

    The test case file "testapp.c" is provided which can be modified as per requirement.
    A make file is also provided which will produce a executable file name "testapp",you can change the name of 
    executable be changing in the makefile. 	


RUN (for Linux) : 
------------------

    Download all the files into a directory and then run 
    command : make 

    It will create an executable which can be run by. 
    command : ./executable-name 

CONTRIBUTION : 
---------------

			Please fork this repository and contribute back.
			Any contribution is welcome. 
