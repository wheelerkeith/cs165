###############################################################
# Program:
#     Project 2, Moonlander
#     Brother Comeau, CS165
# Author:
#     Keith Wheeler
# Summary:
#     Enter a brief description of your program here! If you do any
#     extra credit, this would be a good place to describe it.
#
#     Estimated:  0.0 hrs
#     Actual:     0.0 hrs
#       Please describe briefly what was the most difficult part
###############################################################

LFLAGS = -lGL -lglut -lGLU

###############################################################
# Programs:
#    moon:         The moon lander game
###############################################################
moon: ground.o lander.o game.o uiInteract.o uiDraw.o point.o velocity.o
	g++ -o moon ground.o lander.o game.o uiInteract.o uiDraw.o point.o velocity.o $(LFLAGS)
	tar -j -cf project2.tar makefile *.h *.cpp

###############################################################
# Individual files
#    ground.o      Displays the ground and platform
#    game.o        The moon game
#    uiInteract.o  Handles input events
#    uiDraw.o      Drawing functions
#    point.o       Point class
###############################################################
ground.o: ground.cpp ground.h
	g++ -c ground.cpp

lander.o: lander.cpp lander.h
	g++ -c lander.cpp

game.o: game.cpp uiDraw.h uiInteract.h point.h ground.h
	g++ -c game.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

velocity.o: velocity.cpp velocity.h
	g++ -c velocity.cpp

###############################################################
# General rules
###############################################################
clean:
	rm moon project2.tar *.o

all:
	moon
