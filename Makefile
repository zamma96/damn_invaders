#OBJS specifies which files to compile as part of the project
OBJS = Controller.cpp Model.cpp View.cpp
 
#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the libraries we're linking againt
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

CFLAGS = -I/usr/include/SDL2

#OBJ_NAME specifies the name of our executable
OBJ_NAME = game

#This is the target that compiler our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(CFLAGS) $(LINKER_FLAGS)  -o $(OBJ_NAME)