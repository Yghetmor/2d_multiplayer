OBJS = \
	src/main.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2

OBJ_NAME = 2d_game

BIN_FOLDER = bin/

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BIN_FOLDER)$(OBJ_NAME)

clean :
	@rm $(BIN_FOLDER)*
