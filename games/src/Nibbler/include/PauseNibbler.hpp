/*
** EPITECH PROJECT, 2020
** PauseNibbler
** File description:
** hpp
*/

#ifndef PAUSENIBBLER_HPP_
#define PAUSENIBBLER_HPP_

#include "IGraphics.hpp"
#include "Nibbler.hpp"
#include <vector>

#include "MacroNibbler.hpp"

class PauseNibbler {
    public:
        PauseNibbler(){};
        ~PauseNibbler(){};
        int runPauseNibbler(IGraphics *);
        enum Option {
            RESUME,
            RESTART,
            MENU
        };
    protected:
    private:
        bool _inPauseNibbler;
        IGraphics *_graphicLib;
        Shape _shapePauseNibblerTitle;
        int _nbrOptions;
        std::vector<Shape> _shapesMenuOptions;
        int _selectedOption;
        void initPauseNibbler(IGraphics *);
        int handleEventPauseNibbler(int);
        void switchSelectionList(std::vector<Shape> *, int *, int);
};

#endif /* !PAUSENIBBLER_HPP_ */
