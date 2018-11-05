###############################################################
# Program:
#     Project ##, ????
#     Brother Comeau, CS165
# Author:
#     author
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
a.out: game.o uiInteract.o uiDraw.o point.o velocity.o rifle.o moveable.o bird.o bullet.o
	g++ -o a.out game.o uiInteract.o uiDraw.o point.o velocity.o rifle.o moveable.o bird.o bullet.o $(LFLAGS)
	tar -j -cf project3.tar makefile *.h *.cpp

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

rifle.o: rifle.cpp rifle.h
	g++ -c rifle.cpp
	
moveable.o: moveable.cpp moveable.here
	g++ -c moveable.cpp
	
bird.o: bird.cpp bird.here
	g++ -c bird.cpp
	
bullet.o: bullet.cpp bullet.here
	g++ -c bullet.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out project3.tar *.o

cleanbackups:
	rm backup*.tar

backup:
	tar -j -cvf $(ARCHIVE).tar *.cpp *.h makefile

all:
	a.out
