/*
** EPITECH PROJECT, 2020
** IGraphics
** File description:
** hpp
*/

#ifndef IGRAPHICS_HPP
#define IGRAPHICS_HPP

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

enum Color {
    WHITE,
    BLACK,
    YELLOW,
    RED,
    GREEN,
    BLUE,
};

typedef struct Shape_s {
    int x;
    int y;
    std::string filePath; // can be empty for ncurses
    std::string message; // check if empty
    size_t textSize = 24;
    Color textColor = WHITE;
    int id;
} Shape;

/*

  Each Game handles a map of resources (Shapes) to pass
  to the graphic engine to render

   GRAPHICS                              |     GAME
  ______________________________________________________
                                         |
    int id -> sf::Sprite (for example)   |     map { { int id -> Shape } }

*/

class IGraphics
{
public:
    enum Input
    {
        PREV_GAME,
        NEXT_GAME,
        PREV_LIB,
        NEXT_LIB,
        RESTART_GAME,
        MENU,
        NO_INPUT,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        PAUSE,
        ACTION,
        QUIT
    };
    virtual ~IGraphics() {}
    virtual void clearScreen() = 0;
    virtual void addShape(Shape &) = 0;
    virtual void drawScreen(void) = 0;
    virtual void drawShape(int key) = 0; // here key is the map's key
    virtual Input getInput() = 0;
    virtual bool isRunning(void) const = 0; // check game
};

#endif /* !IGRAPHICS_HPP */
