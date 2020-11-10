##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## .o
##

SRC	=	./src/Pacman.cpp	\
		./src/entryPoint.cpp	\
		./src/PausePacman.cpp	\
		./../../../core/src/Error.cpp	\
		./../../../core/src/GameLibLoader.cpp	\
		./../../../core/src/GraphicLibLoader.cpp	\

NAME	=	../../lib_arcade_pacman.so

CXX=	g++

OBJ =	$(SRC:.cpp=.o)

CXXFLAGS =	-fPIC
CXXFLAGS +=	-Iinclude
CXXFLAGS += -I./../../../lib/src/ 
CXXFLAGS += -I./../../../core/include
CXXFLAGS += -I./../
CXXFLAGS +=	-Wall -Wextra -Wno-deprecated -Werror
CXXFLAGS += -ldl -shared

LDFLAGS		=	-ldl -shared

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ)
fclean:		clean
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re