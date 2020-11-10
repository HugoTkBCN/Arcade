##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## .o
##

ROOT_SRC	=	../../../core/src/

SRC	=	./src/Sdl2.cpp	\
		./src/entryPoint.cpp	\
		$(ROOT_SRC)Error.cpp

NAME	=	../../lib_arcade_sdl2.so

CPP =	g++

OBJ =	$(SRC:.cpp=.o)

CPPFLAGS = -fPIC -shared
CPPFLAGS += -I./include
CPPFLAGS += -I./../../../core/include
CPPFLAGS += -I./../
CPPFLAGS +=	-Wall -Wextra -Wno-deprecated -Werror
CPPFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)
fclean:		clean
	@rm -rf $(NAME)

re:	fclean all
