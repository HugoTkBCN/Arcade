/*
** EPITECH PROJECT, 2020
** ncurses
** File description:
** hpp
*/

#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <ncurses.h>
#include "IGraphics.hpp"
#include "Error.hpp"
#include <map>
#include <unistd.h>

#define MIN_HEIGHT 80
#define MIN_WIDTH 30
#define DIV_X 10
#define DIV_Y 20
#define ERROR_MESSAGE "Screen too small, resize it please !"

class Ncurses : public IGraphics {
    public:
        Ncurses();
        ~Ncurses();

        void clearScreen() override;

        void addShape(Shape &) override;
        void drawShape(int) override;
        void drawScreen(void) override;

        Input getInput(void) override;
        int getScreenWidth(void) const;
        int getScreenHeight(void) const;

        bool isRunning(void) const override;

        void errorResizeScreen();

    protected:
    private:
        std::map<int, Shape> _shapes;
        bool _isRunning;
};

#endif /* !NCURSES_HPP */
