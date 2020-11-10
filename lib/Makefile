##
## EPITECH PROJECT, 2019
## Arcade
## File description:
## Makefile
##

all: $(OBJ)
	make -C ./src/Ncurses
	make -C ./src/Sdl2
	make -C ./src/Sfml

clean:
	make clean -C ./src/Ncurses
	make clean -C ./src/Sdl2
	make clean -C ./src/Sfml

fclean: clean
	make fclean -C ./src/Ncurses
	make fclean -C ./src/Sdl2
	make fclean -C ./src/Sfml

re: fclean all

.PHONY: all clean fclean re