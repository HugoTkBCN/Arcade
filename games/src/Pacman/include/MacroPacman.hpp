/*
** EPITECH PROJECT, 2020
** MacroPacman
** File description:
** hpp
*/

#ifndef MACROPACMAN_HPP
#define MACROPACMAN_HPP

////////////////////////////////////////////////////
//Pacman.hpp
////////////////////////////////////////////////////

#define PATH_TO_WALL "pacman_assets/images/wall.png"
#define WALL_CHAR "#"

#define PATH_TO_UP_HEAD(i) "pacman_assets/images/pacman/up/pacman_" + std::to_string(i) + ".png"
#define PATH_TO_DOWN_HEAD(i) "pacman_assets/images/pacman/down/pacman_" + std::to_string(i) + ".png"
#define PATH_TO_LEFT_HEAD(i) "pacman_assets/images/pacman/left/pacman_" + std::to_string(i) + ".png"
#define PATH_TO_RIGHT_HEAD(i) "pacman_assets/images/pacman/right/pacman_" + std::to_string(i) + ".png"
#define PATH_TO_DEAD_PACMAN(i) "pacman_assets/images/pacman/dead/pacman_dead_" + std::to_string(i) + ".png"

#define NUMBER_DEAD_SPRITES 11
#define TIME_DEAD_PACMAN 3

#define NUMBER_SPRITE_PACMAN 3

#define PATH_TO_FOOD "pacman_assets/images/food.png"
#define FOOD_CHAR "*"

#define PATH_TO_POWER "pacman_assets/images/power.png"
#define POWER_CHAR "P"

#define COLOR_SELECTED Color::YELLOW
#define COLOR_NOT_SELECTED Color::WHITE
#define COLOR_TEXT Color::WHITE
#define COLOR_TITLE Color::RED
#define COLOR_HELP Color::BLUE
#define COLOR_USERNAME Color::GREEN
#define COLOR_SUBTITLE Color::GREEN

#define SIZE_TITLE 50
#define SIZE_SUBTITLE 40
#define SIZE_TEXT 30
#define SIZE_COM 20
#define SIZE_SELECTED 40
#define SIZE_NOT_SELECTED 30
#define NO_PATH ""

#define INDEX_SHAPE_PACMAN 90
#define INDEX_SHAPE_TITLE_PACMAN INDEX_SHAPE_PACMAN
#define X_TITLE 300
#define Y_TITLE 10
#define TEXT_TITLE_PACMAN "Pacman"

#define PACMAN_SIZE 20

#define INDEX_SHAPE_WALL INDEX_SHAPE_PACMAN + 1
#define X_WALL 40
#define Y_WALL 100
#define WALL_SIZE 20


#define INDEX_SHAPE_FOOD INDEX_SHAPE_PACMAN + 2
#define FOOD_SIZE PACMAN_SIZE

#define INDEX_SHAPE_SCORE_PACMAN INDEX_SHAPE_PACMAN + 3
#define X_SCORE 10
#define Y_SCORE 10
#define TEXT_SCORE_PACMAN "Score: "
#define COLOR_SCORE Color::BLUE
#define SIZE_SCORE 30


#define HEAD_CHAR "["
#define X_HEAD 400
#define Y_HEAD 380
#define INDEX_SHAPE_PACMAN_HEAD INDEX_SHAPE_PACMAN + 4
#define INIT_LIFE 3

#define INDEX_SHAPE_POWER INDEX_SHAPE_PACMAN + 5
#define POWER_SIZE PACMAN_SIZE

#define NUMBER_GHOST 4
#define NUMBER_SPRITE_GHOST 8
#define INDEX_SHAPE_GHOST INDEX_SHAPE_PACMAN + 6
#define X_GHOST 380
#define Y_GHOST 320
#define PATH_TO_GHOST(ghostColor, i) "pacman_assets/images/ghost/" + std::to_string(ghostColor) + "/ghost_" + std::to_string(i) + ".png"
#define PATH_TO_GHOST_HUNTED(ghostColor, i) "pacman_assets/images/ghost/hunted/" + std::to_string(ghostColor) + "/ghost_" + std::to_string(i) + ".png"
#define PATH_TO_EYES(i) "pacman_assets/images/ghost/eyes/eyes_" + std::to_string(i) + ".png"
#define GHOST_SIZE PACMAN_SIZE
#define TIME_DEAD_GHOST 8

#define INDEX_SHAPE_GATE INDEX_SHAPE_PACMAN + 11
#define X_GATE 400
#define Y_UP_GATE 260
#define Y_DOWN_GATE 360
#define PATH_TO_GATE "pacman_assets/images/gate.png"
#define X_CELL_MIN 360
#define X_CELL_MAX 440
#define Y_CELL_MIN 260
#define Y_CELL_MAX 360

#define INDEX_SHAPE_HEART INDEX_SHAPE_PACMAN + 12
#define X_HEART 600
#define Y_HEART 40
#define PATH_TO_HEART "pacman_assets/images/heart.png"
#define HEART_CHAR "<3"
#define HEART_COLOR Color::RED
#define HEART_SIZE 40

#define INDEX_SHAPE_TITLE_END_PACMAN INDEX_SHAPE_PACMAN + 13
#define TEXT_TITLE_END_PACMAN "You are Dead!"
#define X_TITLE_END 300
#define Y_TITLE_END 100

#define INDEX_SHAPE_REPLAY_PACMAN INDEX_SHAPE_TITLE_PACMAN + 14
#define X_REPLAY 200
#define Y_REPLAY 300
#define TEXT_REPLAY_PACMAN "Replay"

#define INDEX_SHAPE_GO_MENU_PACMAN INDEX_SHAPE_TITLE_PACMAN + 15
#define X_GO_MENU 400
#define Y_GO_MENU 300
#define TEXT_GO_MENU_PACMAN "Menu"

#define INDEX_SHAPE_NEW_TOP_SCORE_PACMAN INDEX_SHAPE_TITLE_PACMAN + 16
#define X_NEW_TOP_SCORE 200
#define Y_NEW_TOP_SCORE 500
#define TEXT_NEW_TOP_SCORE "New Top Score !"

#define PATH_TO_MAPS "pacman_assets/maps/"
#define NUMBER_MAP 8

#define GAMING 0
#define WIN 1
#define LOSE 2

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

#define WIDTH_MAP 37
#define HEIGHT_MAP 22

#define INIT_SPEED (double)0.2
#define INIT_GHOST_SPEED (double)0.4

#define NUMBER_SCORES_BY_FILE 5
#define PATH_TO_SCORES "scores/pacman.scores"

////////////////////////////////////////////////////
//PausePacman.hpp
////////////////////////////////////////////////////

#define INDEX_SHAPE_TITLE_PAUSE_PACMAN INDEX_SHAPE_PACMAN + 20
#define X_TITLE_PAUSE 300
#define Y_TITLE_PAUSE 50
#define TEXT_TITLE_PAUSE_PACMAN "Pause"

#define TEXT_RESUME "Resume"
#define X_RESUME 300
#define Y_RESUME 200

#define TEXT_RESTART "Restart"
#define X_RESTART 300
#define Y_RESTART 300

#define TEXT_GO_MENU_PAUSE "Main Menu"
#define X_GO_MENU_PAUSE 300
#define Y_GO_MENU_PAUSE 400

#define GO_UP 1
#define GO_DOWN 2

#define FIRST_ELEM 0
#define LAST_ELEM(x) x - 1

#endif /* !MACROPACMAN_HPP */
