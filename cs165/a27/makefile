###############################################################
# Program:
#     Assignment 27, Non-Member friend operators
#     Brother Comeau, CS165
# Author:
#     author one
#     author two
# Summary:
#     Enter a brief description of your program here! If you do any
#     extra credit, this would be a good place to describe it.
#
#     Estimated:  0.0 hrs
#     Actual:     0.0 hrs
#       Please describe briefly what was the most difficult part
###############################################################
a.out: assign27.o point.o velocity.o
	g++ -o a.out assign27.o point.o velocity.o
	tar -j -cf assign27.tar *.h *.cpp makefile

point.o: point.cpp point.h
	g++ -c point.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

assign27.o: assign27.cpp velocity.h
	g++ -c assign27.cpp

clean:
	rm *.out *.o *.tar
