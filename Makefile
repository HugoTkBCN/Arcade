##
## EPITECH PROJECT, 2020
## arcade
## File description:
## Makefile
##

SRC	=	./core/src/main.cpp	\
		./core/src/Menu.cpp	\
		./core/src/Core.cpp	\
		./core/src/Error.cpp	\
		./core/src/GraphicLibLoader.cpp	\
		./core/src/GameLibLoader.cpp	\
		./core/src/User.cpp

NAME	=	arcade

CPP	=	g++

OBJ =	$(SRC:.cpp=.o)

CPPFLAGS = -I./core/include
CPPFLAGS += -I./lib/src/
CPPFLAGS += -I./games/src/
CPPFLAGS +=	-Wall -Wextra -Werror

LDFLAGS		=	-ldl -lncurses

all: games graphicals core

core: $(OBJ)
	$(CPP) -o $(NAME) $(OBJ) $(LDFLAGS)

graphicals:
	make -C ./lib

games:
	make -C ./games

clean:
	make clean -C ./lib
	make clean -C ./games
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./lib
	make fclean -C ./games
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re core graphicals games arcade
