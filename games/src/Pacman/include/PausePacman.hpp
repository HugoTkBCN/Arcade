/*
** EPITECH PROJECT, 2020
** PausePacman
** File description:
** hpp
*/

#ifndef PAUSEPACMAN_HPP_
#define PAUSEPACMAN_HPP_

#include "IGraphics.hpp"
#include "Pacman.hpp"
#include <vector>

#include "MacroPacman.hpp"

class PausePacman {
    public:
        PausePacman(){};
        ~PausePacman(){};
        int runPausePacman(IGraphics *);
        enum Option {
            RESUME,
            RESTART,
            MENU
        };
    protected:
    private:
        bool _inPausePacman;
        IGraphics *_graphicLib;
        Shape _shapePausePacmanTitle;
        int _nbrOptions;
        std::vector<Shape> _shapesMenuOptions;
        int _selectedOption;
        void initPausePacman(IGraphics *);
        int handleEventPausePacman(int);
        void switchSelectionList(std::vector<Shape> *, int *, int);
};

#endif /* !PAUSEPACMAN_HPP_ */
