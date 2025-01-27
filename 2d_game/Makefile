OBJS = \
	src/main.cpp \
	src/game.cpp \
	src/entity.cpp \
	src/camera.cpp \
	src/map.cpp \
	src/player.cpp \
	src/monster.cpp \
	src/projectile.cpp \
	src/clock.cpp \
	src/online_game.cpp \

CC = g++

COMPILER_FLAGS = -std=c++20 -Wall -I /usr/local/include/

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = 2d_game

BIN_FOLDER = bin/

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BIN_FOLDER)$(OBJ_NAME)

clean :
	@rm $(BIN_FOLDER)*
