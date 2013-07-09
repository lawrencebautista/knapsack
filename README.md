Knapsack
========

Contains two executables for solving the knapsack problem: ksbb and ksdp
ksbb solves the problem using a branch and bound algorithm.
ksdp solves the problem using a dynamic programming algorithm.

The branch and bound algorithm is more functional as it isn't limited by available memory. The dynamic programming algorithm works fine as long as the input size isn't too large.

The makefile compiles both executables.
To run the executables the syntax is the following:
	./ksdp <datafile>
	./ksbb <datafile>

Examples of data files are found in the data directory.
