/*
** EPITECH PROJECT, 2020
** Nibbler
** File description:
** hpp
*/

#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "IGames.hpp"
#include "IGraphics.hpp"
#include "Error.hpp"
#include "PauseNibbler.hpp"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "MacroNibbler.hpp"

typedef struct snake_s {
    std::vector<Position> snakePositions;
    int direction;
    int size;
} Snake;

class Nibbler : public IGames {
    public:
        Nibbler(){};
        ~Nibbler(){};

        void runGame(IGraphics *, loadGraph &, std::string) override;
        static Shape fillGameShape(int, int, int, std::string, std::string, Color, size_t);
        int isGameChanged(void);
        IGraphics *getLibGraphic(void) override;

    protected:
    private:
        //utils
        void setShape(Shape &, int, int, int, std::string, std::string, Color, int) override;
        void switchHeadDirection(std::string, int) override;
        void changeTailDirection(void);
        bool startPause(void) override;

        Position _tmpPos;
        Position _savePos;

        //init
        void initGame(void);
        void initSnake(void);
        void initGameShapes(bool) override;
        void getWallFoodsPositions(std::vector<std::string>) override;
        bool getMap(std::string) override;

        //Print
        void printAtPosition(Shape &, int, int) override;
        void printGame(void) override;
        void printMap(std::vector<Position>, Shape &) override;
        void printSnake(void);

        //Save Top Score
        static bool sortBySec(const std::pair<std::string, int> &, const std::pair<std::string, int> &);
        std::vector<std::pair<std::string, int>> getTopScores(void) override;
        void setTopScore(std::vector<std::pair<std::string, int>>) override;
        bool isTopScore(void) override;
        
        //End Game Menu
        void switchSelectionEndMenu(Shape *, Shape *, int) override;
        void endMenu(void) override;
        void handleEventEndGame(int) override;
        void initEndMenu(void) override;

        Shape _shapeTitleEnd;
        Shape _shapeReplay;
        Shape _shapeMenu;
        Shape _shapeNewTopScore;
        int _selectedEndGame;
        bool _inEndMenu;

        //check Obstacle
        bool checkObstacles(int, int);
        void checkWalls(int, int);
        int roundForMap(int, int);
        bool isOtherObstacle(int, int);
        Position getNewFoodPositions(void);
        bool checkFoods(int, int);
        void checkBody(int, int);

        //HandleEvent
        void handleEventGame(int, loadGraph &) override;

        //Move Snake
        void moveForwardSnake(void);
        void moveHead(void);
        void moveBody(void);

        //Snake Variables
        Snake _snake;
        double _snakeSpeed;
        double _saveSnakeSpeed;

        
        //Game Variables
        int _gameStatus;
        int _score;
        std::vector<Position> _wallsPosition;
        std::vector<Position> _foodsPosition;

        //Shapes Game
        Shape _shapeNibblerTitle;
        Shape _shapeWall;
        Shape _shapeFood;
        Shape _shapeHeadSnake;
        Shape _shapeBodySnake;
        Shape _shapeTailSnake;
        Shape _shapeNibblerScore;

        //Core Variables
        IGraphics *_libGraphic;
        bool _inNibbler;
        std::string _userName;
        int _changeGame;

        //Clocks
		std::chrono::steady_clock::time_point _clockGame;
        std::chrono::steady_clock::time_point _instantTime;
        std::chrono::duration<double> _timePasted;

        //Core
        void refresh(void) override;
};

#endif /* !NIBBLER_HPP */