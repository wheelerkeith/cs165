###############################################################
# Program:
#     Week 01, Vector
#     Brother JonesL, CS235
# Author:
#     Keith Wheeler
# Summary:
#     makefile for the vector class
# Time:
#     15 hours
# Report:
#     The most difficult part was remembering everything about 
# classes. I took CS165 about a year and a half ago. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h week01.o
	g++ -o a.out week01.o 
	tar -cf week01.tar vector.h week01.cpp makefile

##############################################################
# The individual components
#      week01.o     : the driver program
##############################################################
week01.o: vector.h week01.cpp
	g++ -c week01.cpp
