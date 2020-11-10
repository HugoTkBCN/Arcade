##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## .o
##

SRC	=	./src/Ncurses.cpp	\
		./../../../core/src/Error.cpp	\
		./src/entryPoint.cpp

NAME	=	../../lib_arcade_ncurses.so

CXX =	g++

OBJ =	$(SRC:.cpp=.o)

CXXFLAGS = -fPIC
CPPFLAGS += -I./include 
CPPFLAGS += -I./../../../core/include
CPPFLAGS += -I./../
CXXFLAGS +=	-Wall -Wextra -Wno-deprecated -Werror
CXXFLAGS += -lncurses

LDFLAGS		=	-shared

all:	$(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	@rm -rf $(OBJ)

fclean:		clean
	@rm -rf $(NAME)

re:	fclean all