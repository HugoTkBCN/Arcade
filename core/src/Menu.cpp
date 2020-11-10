/*
** EPITECH PROJECT, 2020
** Menu
** File description:
** cpp
*/

#include "Menu.hpp"

/************************************************************************************/
/*                                  INIT                                            */
/************************************************************************************/

void Menu::initShapes(std::vector<std::string> graphicsAvailable)
{
    this->_graphicLib->addShape(this->_shapeTitle = Core::fillShape(INDEX_SHAPE_MENU, X_TITLE, Y_TITLE, NO_PATH, TITLE, COLOR_TITLE, SIZE_TITLE));
    this->_graphicLib->addShape(this->_shapeUserMenu = Core::fillShape(INDEX_SHAPE_MENU_USER, X_USERNAME_MENU, Y_USERNAME_MENU, NO_PATH, TEXT_USERNAME_MENU + this->_userName, COLOR_USERNAME, SIZE_COM));
    this->_graphicLib->addShape(this->_shapeGraphLib = Core::fillShape(INDEX_SELECT_GRAPH, X_TEXT_GRAPH, Y_TEXT_GRAPH, NO_PATH, TEXT_GRAPH, COLOR_SELECTED, SIZE_SELECTED));
    this->_graphicLib->addShape(this->_shapeGameLib = Core::fillShape(INDEX_SELECT_GAME, X_TEXT_GAME, Y_TEXT_GAME, NO_PATH, TEXT_GAME, COLOR_NOT_SELECTED, SIZE_NOT_SELECTED));
    this->_graphicLib->addShape(this->_shapeCommandRight = Core::fillShape(INDEX_SHAPE_MENU_RIGHT, X_HELP_RIGHT, Y_HELP_RIGHT, NO_PATH, TEXT_HELP_RIGHT, COLOR_HELP, SIZE_HELP));
    this->_graphicLib->addShape(this->_shapeCommandLeft = Core::fillShape(INDEX_SHAPE_MENU_LEFT, X_HELP_LEFT, Y_HELP_LEFT, NO_PATH, TEXT_HELP_LEFT, COLOR_HELP, SIZE_HELP));
    this->_graphicLib->addShape(this->_shapeCommandUp = Core::fillShape(INDEX_SHAPE_MENU_UP, X_HELP_UP, Y_HELP_UP, NO_PATH, TEXT_HELP_UP, COLOR_HELP, SIZE_HELP));
    this->_graphicLib->addShape(this->_shapeCommandDown = Core::fillShape(INDEX_SHAPE_MENU_DOWN, X_HELP_DOWN, Y_HELP_DOWN, NO_PATH, TEXT_HELP_DOWN, COLOR_HELP, SIZE_HELP));
    this->_graphicLib->addShape(this->_shapeCommandAction = Core::fillShape(INDEX_SHAPE_MENU_ACTION, X_HELP_ACTION, Y_HELP_ACTION, NO_PATH, TEXT_HELP_ACTION, COLOR_HELP, SIZE_HELP));
    this->_graphicLib->addShape(this->_shapeCommandPause = Core::fillShape(INDEX_SHAPE_MENU_PAUSE, X_HELP_PAUSE, Y_HELP_PAUSE, NO_PATH, TEXT_HELP_PAUSE, COLOR_HELP, SIZE_HELP));
    this->_graphicLib->addShape(this->_shapeCommandeQuit = Core::fillShape(INDEX_SHAPE_MENU_QUIT, X_HELP_QUIT, Y_HELP_QUIT, NO_PATH, TEXT_HELP_QUIT, COLOR_HELP, SIZE_HELP));
    addShapePutList(this->_nbrGames, &this->_shapesGamesAvailable, this->_gamesAvailable, INDEX_SHAPE_MENU_SELECT_GAME, X_LIST_GAME, Y_LIST_GAME);
    addShapePutList(this->_nbrGraphics, &this->_shapesGraphicsAvailable, graphicsAvailable, INDEX_SHAPE_MENU_SELECT_GRAPH, X_LIST_GRAPH, Y_LIST_GRAPH);
    this->_graphicLib->addShape(this->_shapeWelcome = Core::fillShape(INDEX_SHAPE_WELCOME, X_WELCOME, Y_WELCOME, NO_PATH, TEXT_WELCOME, COLOR_TEXT, SIZE_TITLE));
    this->_graphicLib->addShape(this->_shapeAuthor = Core::fillShape(INDEX_SHAPE_AUTHOR, X_AUTHOR, Y_AUTHOR, NO_PATH, TEXT_AUTHOR, COLOR_USERNAME, SIZE_COM));
}

void Menu::initMenu(IGraphics *graphicLib, int graphicLibUsed, std::vector<std::string> graphicsAvailable, std::vector<std::string> gamesAvailable, std::string userName)
{
    this->_graphicLib = graphicLib;

    this->_graphicLibUsed = graphicLibUsed;
    this->_gameLibUsed = NO_GAME_SELECTED;

    this->_selectedMenu = INDEX_SELECT_GRAPH;
    this->_selectedGame = FIRST_ELEM;
    this->_selectedGraphics = FIRST_ELEM;

    this->_inMenu = true;
    this->_inSelectGame = false;
    this->_inSelectGraph = false;

    this->_userName = userName;
    this->_nbrGames = gamesAvailable.size();
    this->_nbrGraphics = graphicsAvailable.size();

    this->_gamesAvailable = gamesAvailable;

    initShapes(graphicsAvailable);
}

/************************************************************************************/
/*                                  GET                                             */
/************************************************************************************/

int Menu::getGraphicLib(void)
{
    return (_graphicLibUsed);
}

int Menu::getGameLib(void)
{
    return (_gameLibUsed);
}

/************************************************************************************/
/*_                               MENU SELECTION                                  */
/************************************************************************************/

void Menu::addShapePutList(int nbrElem, std::vector<Shape> *shapesList, std::vector<std::string> messageList, int indexShapes, int x, int y)
{
    Shape graph;
    shapesList->clear();
    for (int i = 0; i < nbrElem; i++) {
        graph = Core::fillShape(indexShapes + i, x, y + i * Y_DISTANCE_LIST, NO_PATH, messageList[i], COLOR_NOT_SELECTED, SIZE_NOT_SELECTED);
        this->_graphicLib->addShape(graph);
        shapesList->push_back(graph);
    }
}

void Menu::printTopScores(void)
{
    int x = 0, y = 0, b = 0;
    std::string a;
    std::ifstream file;
    Shape shape;

    shape = Core::fillShape(INDEX_SHAPE_TOP_SCORE, X_TOP_SCORE, X_TOP_SCORE, NO_PATH, TEXT_TOP_SCORE, COLOR_TITLE, SIZE_SUBTITLE);
    this->_graphicLib->addShape(shape);
    this->_graphicLib->drawShape(shape.id);
    for (std::string game : this->_gamesAvailable) {
        file.open(TOP_SCORES_DIRECTORY+game+SCORE_FILE_END);
        y = 0;
        shape = Core::fillShape(INDEX_SHAPE_TOP_SCORE, X_GAME_TITLE_SCORE + (x * DIFF_X_TOP_SCORE), Y_GAME_TITLE_SCORE + (y * DIFF_Y_TOP_SCORE), NO_PATH, game, COLOR_SUBTITLE, SIZE_SUBTITLE);
        this->_graphicLib->addShape(shape);
        this->_graphicLib->drawShape(shape.id);
        while (file >> a >> b) {
            shape = Core::fillShape(INDEX_SHAPE_TOP_SCORE, X_SCORE_LIST + (x * DIFF_X_TOP_SCORE), Y_SCORE_LIST + (y * DIFF_Y_TOP_SCORE), "", a + ": " + std::to_string(b), COLOR_TEXT, SIZE_TEXT);
            this->_graphicLib->addShape(shape);
            this->_graphicLib->drawShape(shape.id);
            y++;
        }
        x++;
        file.close();
    }
}

void Menu::selectLib(std::vector<Shape> shapes, int selectedLib, bool *inSelectedMenu, int indexShapes, int nbrElem, bool inGameSelection)
{
    shapes[selectedLib].textColor = COLOR_SELECTED;
    shapes[selectedLib].textSize = SIZE_SELECTED;
    this->_graphicLib->addShape(shapes[selectedLib]);
    while (this->_graphicLib->isRunning() && *inSelectedMenu) {
        this->_graphicLib->clearScreen();
        for (int i = indexShapes; i < indexShapes + nbrElem; i++)
            this->_graphicLib->drawShape(i);
        inGameSelection ? printTopScores() : (void)0;
        handleEvent(this->_graphicLib->getInput());
        this->_graphicLib->drawScreen();
    }
}

void Menu::switchSelectionList(std::vector<Shape> *shapes, int *selected, int addSub)
{
    (*shapes)[*selected].textColor = COLOR_NOT_SELECTED;
    (*shapes)[*selected].textSize = SIZE_NOT_SELECTED;
    this->_graphicLib->addShape((*shapes)[*selected]);
    addSub == GO_UP ? (*selected)-- : (*selected)++;
    (*shapes)[*selected].textColor = COLOR_SELECTED;
    (*shapes)[*selected].textSize = SIZE_SELECTED;
    this->_graphicLib->addShape((Shape &)(*shapes)[*selected]);
}

void Menu::switchSelection(Shape *toSelect, Shape *toUnselect, int indexToSelect)
{
    (*toSelect).textColor = COLOR_SELECTED;
    (*toSelect).textSize = SIZE_SELECTED;
    (*toUnselect).textColor = COLOR_NOT_SELECTED;
    (*toUnselect).textSize = SIZE_NOT_SELECTED;
    this->_graphicLib->addShape((*toSelect));
    this->_graphicLib->addShape((*toUnselect));
    this->_selectedMenu = indexToSelect;
}

/***********************************************************************************/
/*                                  HANDLE EVENT                                   */
/***********************************************************************************/

void Menu::handleEvent(int input)
{
    switch (input) {
        case this->_graphicLib->UP:
            if (this->_selectedGame > FIRST_ELEM && this->_inSelectGame)
                switchSelectionList(&this->_shapesGamesAvailable, &this->_selectedGame, GO_UP);
            else if (this->_selectedGraphics > FIRST_ELEM && this->_inSelectGraph)
                switchSelectionList(&this->_shapesGraphicsAvailable, &this->_selectedGraphics, GO_UP);
            break;
        case this->_graphicLib->DOWN:
            if (this->_selectedGame < LAST_ELEM(this->_nbrGames) && this->_inSelectGame)
                switchSelectionList(&this->_shapesGamesAvailable, &this->_selectedGame, GO_DOWN);
            else if (this->_selectedGraphics < LAST_ELEM(this->_nbrGraphics) && this->_inSelectGraph)
                switchSelectionList(&this->_shapesGraphicsAvailable, &this->_selectedGraphics, GO_DOWN);
            break;
        case this->_graphicLib->LEFT:
            (this->_selectedMenu == INDEX_SELECT_GAME && this->_inMenu) ? switchSelection(&this->_shapeGraphLib, &this->_shapeGameLib, INDEX_SELECT_GRAPH) : (void)0;
            break;
        case this->_graphicLib->RIGHT:
            (this->_selectedMenu == INDEX_SELECT_GRAPH && this->_inMenu) ? switchSelection(&this->_shapeGameLib, &this->_shapeGraphLib, INDEX_SELECT_GAME) : (void)0;
            break;
        case this->_graphicLib->ACTION:
            if (this->_selectedMenu == INDEX_SELECT_GRAPH && this->_inMenu) {
                this->_inMenu = false;
                this->_inSelectGraph = true;
                selectLib(this->_shapesGraphicsAvailable, this->_selectedGraphics, &this->_inSelectGraph, INDEX_SHAPE_MENU_SELECT_GRAPH, this->_nbrGraphics, false);
                this->_inMenu = true;
            } else if (this->_selectedMenu == INDEX_SELECT_GAME && this->_inMenu){
                this->_inMenu = false;
                this->_inSelectGame = true;
                selectLib(this->_shapesGamesAvailable, this->_selectedGame, &this->_inSelectGame, INDEX_SHAPE_MENU_SELECT_GAME, this->_nbrGames, true);
                this->_inMenu = true;
            }
            if (this->_inSelectGame) {
                this->_gameLibUsed = this->_selectedGame;
                this->_inSelectGame = false;
            } else if (this->_inSelectGraph) {
                this->_graphicLibUsed = this->_selectedGraphics;
                this->_inSelectGraph = false;
            }
            break;
        case this->_graphicLib->PAUSE:
            if (this->_inSelectGraph)
                this->_inSelectGraph = false;
            else if (this->_inSelectGame)
                this->_inSelectGame = false;
            break;
    }
}

/************************************************************************************/
/*                                  MENU CORE                                       */
/************************************************************************************/

int Menu::run(IGraphics *graphicLib, int graphicLibUsed, std::vector<std::string> graphicsAvailable, std::vector<std::string> gamesAvailable, std::string userName, bool skip)
{
    initMenu(graphicLib, graphicLibUsed, graphicsAvailable, gamesAvailable, userName);
    while (this->_graphicLib->isRunning() && this->_gameLibUsed == NO_GAME_SELECTED && !skip) {
        this->_graphicLib->clearScreen();
        for (int i = INDEX_SHAPE_MENU; i <= NUMBER_SHAPES_MENU; i++)
            this->_graphicLib->drawShape(i);
        this->_graphicLib->drawShape(this->_shapeWelcome.id);
        this->_graphicLib->drawShape(this->_shapeAuthor.id);
        handleEvent(this->_graphicLib->getInput());
        this->_graphicLib->drawScreen();
    }
    if (this->_graphicLib->isRunning() == false)
        return (MENU_EXITED);
    return (EXIT_SUCCESS);
}
