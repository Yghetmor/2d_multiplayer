OBJS = \
	src/main.cpp \
	src/game.cpp \

CC = g++

COMPILER_FLAGS = -w -I /usr/local/include/

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = 2d_game

BIN_FOLDER = bin/

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BIN_FOLDER)$(OBJ_NAME)

clean :
	@rm $(BIN_FOLDER)*
