/*
** EPITECH PROJECT, 2020
** IGames
** File description:
** .hpp
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include "IGraphics.hpp"
#include "GraphicLibLoader.hpp"

typedef struct position_s {
    int x;
    int y;
} Position;

class IGames {
    public:
        virtual ~IGames(){}
        
        virtual void runGame(IGraphics *, loadGraph &, std::string) = 0;
        virtual int isGameChanged(void) = 0;
        virtual IGraphics *getLibGraphic(void) = 0;
    protected:
    private:
        //utils
        virtual void setShape(Shape &, int, int, int, std::string, std::string, Color, int) = 0;
        virtual void switchHeadDirection(std::string, int) = 0;
        virtual bool startPause(void) = 0;

        //init
        virtual void initGameShapes(bool) = 0;
        virtual void getWallFoodsPositions(std::vector<std::string>) = 0;
        virtual bool getMap(std::string) = 0;

        //print
        virtual void printAtPosition(Shape &, int, int) = 0;
        virtual void printGame(void) = 0;
        virtual void printMap(std::vector<Position>, Shape &) = 0;

        //Save Top Score
        virtual std::vector<std::pair<std::string, int>> getTopScores(void) = 0;
        virtual void setTopScore(std::vector<std::pair<std::string, int>>) = 0;
        virtual bool isTopScore(void) = 0;

        //End Game Menu
        virtual void switchSelectionEndMenu(Shape *, Shape *, int) = 0;
        virtual void endMenu(void) = 0;
        virtual void handleEventEndGame(int) = 0;
        virtual void initEndMenu(void) = 0;

        //HandleEvent
        virtual void handleEventGame(int, loadGraph &) = 0;

        //Core
        virtual void refresh(void) = 0;
};

#endif /* !IGAMES_HPP_ */
