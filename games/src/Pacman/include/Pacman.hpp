/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** hpp
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGames.hpp"
#include "IGraphics.hpp"
#include "Error.hpp"
#include "PausePacman.hpp"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "MacroPacman.hpp"

typedef struct person_s {
    Position positions;
    Shape shape;
    int direction;
    bool isAlive;
    clock_t clockDead;
} Person;

class Pacman : public IGames{
    public:
        Pacman(){};
        ~Pacman(){};

        void runGame(IGraphics *, loadGraph &, std::string) override;
        static Shape fillGameShape(int, int, int, std::string, std::string, Color, size_t);
        int isGameChanged(void);
        IGraphics *getLibGraphic(void);
    protected:
    private:
        //utils
        void setShape(Shape &, int, int, int, std::string, std::string, Color, int) override;
        void switchHeadDirection(std::string, int) override;
        bool startPause(void) override;

        //init
        void initGame(bool);
        void initGhost(void);
        void initGameShapes(bool) override;
        void initPerson(Person &, int, int);
        void getWallFoodsPositions(std::vector<std::string>) override;
        bool getMap(std::string) override;

        //Print
        void printAtPosition(Shape &, int, int) override;
        void printGame(void) override;
        void moveEyes(Person &);
        void printGhost(void);
        void printPacman(void);
        bool ghostInCell(void);
        void printGates(void);
        void printHearts(void);
        void printMap(std::vector<Position>, Shape &) override;

        //Save Top Score
        static bool sortBySec(const std::pair<std::string, int> &, const std::pair<std::string, int> &);
        std::vector<std::pair<std::string, int>> getTopScores(void) override;
        void setTopScore(std::vector<std::pair<std::string, int>>) override;
        bool isTopScore(void) override;
        
        //End Game Menu
        void switchSelectionEndMenu(Shape *, Shape *, int) override;
        void checkWin(void);
        Person &getDeadGhost(int, int);
        void checkLose(void);
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
        bool checkObstacles(int, int, bool);
        void checkWalls(Person &, int, int, bool);
        void checkFoods(int, int);
        void checkPower(int, int);

        //HandleEvent
        void handleEventGame(int, loadGraph &) override;

        //move ghosts
        bool checkGhost(int, int);
        void moveGhost(int, int, Person &);
        void getDirectionGhost(Person &, int);
        void moveGhosts(void);

        //Shapes Game
        Shape _shapePacmanTitle;
        Shape _shapeWall;
        Shape _shapeFood;
        Shape _shapePower;
        Shape _shapePacmanScore;
        Shape _shapeGate;
        Shape _shapeHeart;

        //Ghost Variables
        std::vector<Person> _ghost;
        int _indexSpriteGhost;
        double _ghostSpeed;
        bool _ghostHunting;

        //Power Variables
        bool _gotPower;
        clock_t _clockPower;

        //Pacman Variables
        Person _pacman;
        double _gameSpeed;
        int _indexSpritePacman;
        int _indexSpriteDeadPacman;
        int _pacmanHearts;

        //Game Variables
        int _gameStatus;
        int _score;
        bool _printGate;
        std::vector<Position> _wallsPosition;
        std::vector<Position> _foodsPosition;
        std::vector<Position> _powerPosition;

        //Core Variables
        IGraphics *_libGraphic;
        bool _inPacman;
        std::string _userName;
        int _changeGame;

        //Clocks
		std::chrono::steady_clock::time_point _clockGame;
        std::chrono::steady_clock::time_point _clockGhost;
        clock_t _clockStart;
        std::chrono::steady_clock::time_point _instantTime;
        std::chrono::duration<double> _timePasted;
        
        //Core
        void refresh(void) override;
};

#endif /* !PACMAN_HPP_ */
