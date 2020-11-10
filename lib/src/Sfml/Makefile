##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## .o
##

SRC	=	./src/Sfml.cpp	\
		./src/entryPoint.cpp

NAME	=	../../lib_arcade_sfml.so

CPP =	g++

OBJ =	$(SRC:.cpp=.o)

CPPFLAGS = -fPIC -shared
CPPFLAGS += -I./include 
CPPFLAGS += -I./../../../core/include
CPPFLAGS += -I./../
CPPFLAGS +=	-Wall -Wextra -Wno-deprecated -Werror
CPPFLAGS += -lsfml-graphics -lsfml-window -lsfml-system

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)
fclean:		clean
	@rm -rf $(NAME)

re:	fclean all