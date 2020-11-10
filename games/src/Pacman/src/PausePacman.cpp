/*
** EPITECH PROJECT, 2020
** PausePacman
** File description:
** cpp
*/

#include "PausePacman.hpp"

void PausePacman::initPausePacman(IGraphics *graphicLib)
{
    Shape graph;
    this->_selectedOption = RESUME;
    this->_graphicLib = graphicLib;
    this->_inPausePacman = true;
    this->_shapePausePacmanTitle = Pacman::fillGameShape(INDEX_SHAPE_TITLE_PAUSE_PACMAN, X_TITLE_PAUSE, Y_TITLE_PAUSE, NO_PATH, TEXT_TITLE_PAUSE_PACMAN, COLOR_TITLE, SIZE_TITLE);
    this->_graphicLib->addShape(this->_shapePausePacmanTitle);
    graph = Pacman::fillGameShape(INDEX_SHAPE_TITLE_PAUSE_PACMAN + 1, X_RESUME, Y_RESUME, NO_PATH, TEXT_RESUME, COLOR_SELECTED, SIZE_SELECTED);
    this->_graphicLib->addShape(graph);
    this->_shapesMenuOptions.push_back(graph);
    graph = Pacman::fillGameShape(INDEX_SHAPE_TITLE_PAUSE_PACMAN + 2, X_RESTART, Y_RESTART, NO_PATH, TEXT_RESTART, COLOR_NOT_SELECTED, SIZE_NOT_SELECTED);
    this->_graphicLib->addShape(graph);
    this->_shapesMenuOptions.push_back(graph);
    graph = Pacman::fillGameShape(INDEX_SHAPE_TITLE_PAUSE_PACMAN + 3, X_GO_MENU_PAUSE, Y_GO_MENU_PAUSE, NO_PATH, TEXT_GO_MENU_PAUSE, COLOR_NOT_SELECTED, SIZE_NOT_SELECTED);
    this->_graphicLib->addShape(graph);
    this->_shapesMenuOptions.push_back(graph);
    this->_nbrOptions = this->_shapesMenuOptions.size();
}

void PausePacman::switchSelectionList(std::vector<Shape> *shapes, int *selected, int addSub)
{
    (*shapes)[*selected].textColor = COLOR_NOT_SELECTED;
    (*shapes)[*selected].textSize = SIZE_NOT_SELECTED;
    this->_graphicLib->addShape((*shapes)[*selected]);
    addSub == GO_UP ? (*selected)-- : (*selected)++;
    (*shapes)[*selected].textColor = COLOR_SELECTED;
    (*shapes)[*selected].textSize = SIZE_SELECTED;
    this->_graphicLib->addShape((Shape &)(*shapes)[*selected]);
}

int PausePacman::handleEventPausePacman(int input)
{
    switch (input) {
    case IGraphics::UP:
        if (this->_selectedOption > FIRST_ELEM)
            switchSelectionList(&this->_shapesMenuOptions, &this->_selectedOption, GO_UP);
        break;
    case IGraphics::DOWN:
        if (this->_selectedOption < LAST_ELEM(this->_nbrOptions))
            switchSelectionList(&this->_shapesMenuOptions, &this->_selectedOption, GO_DOWN);
        break;
    case IGraphics::ACTION:
        this->_inPausePacman = false;
        if (this->_selectedOption == RESUME)
            return (RESUME);
        else if (this->_selectedOption == RESTART)
            return (RESTART);
        else if (this->_selectedOption == MENU)
            return (MENU);
        break;
    case IGraphics::PAUSE:
        this->_inPausePacman = false;
        break;
    default:
        break;
    }
    return (RESUME);
}

int PausePacman::runPausePacman(IGraphics *graphicLib)
{
    int ret = RESUME;
    initPausePacman(graphicLib);
    while (this->_graphicLib->isRunning() && this->_inPausePacman) {
        this->_graphicLib->clearScreen();
        ret = handleEventPausePacman(this->_graphicLib->getInput());
        this->_graphicLib->drawShape(INDEX_SHAPE_TITLE_PAUSE_PACMAN);
        for (Shape i : this->_shapesMenuOptions)
            graphicLib->drawShape(i.id);
        this->_graphicLib->drawScreen();
    }
    return (ret);
}
