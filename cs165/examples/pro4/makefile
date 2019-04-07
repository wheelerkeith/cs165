###############################################################
# Program:
#     Project 4, Asteroids
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

# for the linux VM in vmware, you need to add '-lGL' to LFLAGS
LFLAGS = -lGL -lglut -lGLU

# vars for the backup feature
PACKAGE   = backup
VERSION   = ` date +"%Y%m%d_%H%M%S" `
ARCHIVE   = $(PACKAGE)-$(VERSION)

###############################################################
# Programs:
#    moon:         The moon lander game
###############################################################
a.out: game.o uiInteract.o uiDraw.o point.o  ship.o asteroid.o velocity.o bullet.o astro.o
	g++ -o a.out game.o uiInteract.o uiDraw.o point.o ship.o asteroid.o velocity.o bullet.o astro.o $(LFLAGS)
	tar -j -cf project4.tar makefile *.h *.cpp

###############################################################
# Individual files
#    rifle.o       Displays the rifle
#    game.o        The skeet game
#    uiInteract.o  Handles input events
#    uiDraw.o      Drawing functions
#    point.o       Point class
#    velocity.o    velocity class
###############################################################
game.o: game.cpp uiDraw.h uiInteract.h point.h
	g++ -c game.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

ship.o: ship.h ship.cpp
	g++ -c ship.cpp

asteroid.o: asteroid.cpp asteroid.h
	g++ -c asteroid.cpp

#velocity.o: velocity.cpp velocity.h
#	g++ -c velocity.cpp

bullet.o: bullet.cpp bullet.h
	g++ -c bullet.cpp

astro.o: astro.cpp astro.h
	g++ -c astro.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out project4.tar *.o

cleanbackups:
	rm backup*.tar

backup:
	tar -j -cvf $(ARCHIVE).tar *.cpp *.h makefile

all:
	a.out
