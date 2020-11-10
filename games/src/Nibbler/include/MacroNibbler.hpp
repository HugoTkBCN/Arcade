/*
** EPITECH PROJECT, 2020
** MacroNibbler
** File description:
** hpp
*/

#ifndef MACRONIBBLER_HPP
#define MACRONIBBLER_HPP

////////////////////////////////////////////////////
//Nibbler.hpp
////////////////////////////////////////////////////

#define PATH_TO_MAPS "nibbler_assets/maps/"

#define PATH_TO_WALL "nibbler_assets/images/wall.png"
#define WALL_CHAR "#"
#define X_MAP_MIN X_WALL
#define X_MAP_MAX X_WALL + WALL_SIZE * (36 - 1)
#define Y_MAP_MIN Y_WALL
#define Y_MAP_MAX Y_WALL + WALL_SIZE * (22 - 1)

#define HEAD_CHAR "A"
#define BODY_CHAR "B"
#define TAIL_CHAR "C"

#define PATH_TO_UP_HEAD "nibbler_assets/images/headUp.png"
#define PATH_TO_DOWN_HEAD "nibbler_assets/images/headDown.png"
#define PATH_TO_LEFT_HEAD "nibbler_assets/images/headLeft.png"
#define PATH_TO_RIGHT_HEAD "nibbler_assets/images/headRight.png"
#define PATH_TO_BODY "nibbler_assets/images/body.png"
#define PATH_TO_UP_TAIL "nibbler_assets/images/tailUp.png"
#define PATH_TO_DOWN_TAIL "nibbler_assets/images/tailDown.png"
#define PATH_TO_LEFT_TAIL "nibbler_assets/images/tailLeft.png"
#define PATH_TO_RIGHT_TAIL "nibbler_assets/images/tailRight.png"

#define PATH_TO_FOOD "nibbler_assets/images/food.png"
#define FOOD_CHAR "F"

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

#define INDEX_SHAPE_NIBBLER 70
#define INDEX_SHAPE_TITLE_NIBBLER INDEX_SHAPE_NIBBLER
#define X_TITLE 300
#define Y_TITLE 10
#define TEXT_TITLE_NIBBLER "Nibbler"

#define NUMBER_MAP 7
#define INDEX_SHAPE_WALL INDEX_SHAPE_TITLE_NIBBLER + 1
#define X_WALL 40
#define Y_WALL 100
#define WALL_SIZE 20

#define X_HEAD 400
#define Y_HEAD 300
#define INDEX_SHAPE_HEAD_SNAKE INDEX_SHAPE_TITLE_NIBBLER + 2
#define INDEX_SHAPE_BODY_SNAKE INDEX_SHAPE_TITLE_NIBBLER + 3
#define INDEX_SHAPE_TAIL_SNAKE INDEX_SHAPE_TITLE_NIBBLER + 4
#define SNAKE_SIZE WALL_SIZE

#define INDEX_SHAPE_FOOD INDEX_SHAPE_TITLE_NIBBLER + 5
#define FOOD_SIZE SNAKE_SIZE

#define INDEX_SHAPE_SCORE_NIBBLER INDEX_SHAPE_TITLE_NIBBLER + 6
#define X_SCORE 10
#define Y_SCORE 10
#define TEXT_SCORE_NIBBLER "Score: "
#define COLOR_SCORE Color::BLUE
#define SIZE_SCORE 30

#define INDEX_SHAPE_TITLE_END_NIBBLER INDEX_SHAPE_TITLE_NIBBLER + 7
#define TEXT_TITLE_END_NIBBLER "You are Dead!"
#define X_TITLE_END 300
#define Y_TITLE_END 100

#define INDEX_SHAPE_REPLAY_NIBBLER INDEX_SHAPE_TITLE_NIBBLER + 8
#define X_REPLAY 200
#define Y_REPLAY 300
#define TEXT_REPLAY_NIBBLER "Replay"

#define INDEX_SHAPE_GO_MENU_NIBBLER INDEX_SHAPE_TITLE_NIBBLER + 9
#define X_GO_MENU 400
#define Y_GO_MENU 300
#define TEXT_GO_MENU_NIBBLER "Menu"

#define INDEX_SHAPE_NEW_TOP_SCORE_NIBBLER INDEX_SHAPE_TITLE_NIBBLER + 10
#define X_NEW_TOP_SCORE 200
#define Y_NEW_TOP_SCORE 500
#define TEXT_NEW_TOP_SCORE "New Top Score !"

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

#define CLOCKS_PER_MICRO_SEC (CLOCKS_PER_SEC / 1000000)
#define INIT_SPEED (double)0.3
#define SPEED_MIN 0.1
#define FOOD_WIN_SPEED 0.025
#define INIT_SIZE 4

#define GAMING 0
#define WIN 1
#define LOSE 2

#define NUMBER_SCORES_BY_FILE 5
#define PATH_TO_SCORES "scores/nibbler.scores"

////////////////////////////////////////////////////
//PauseNibbler.hpp
////////////////////////////////////////////////////

#define INDEX_SHAPE_TITLE_PAUSE_NIBBLER INDEX_SHAPE_NIBBLER + 11
#define X_TITLE_PAUSE 300
#define Y_TITLE_PAUSE 50
#define TEXT_TITLE_PAUSE_NIBBLER "Pause"

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

#endif /* !MACRONIBBLER_HPP */