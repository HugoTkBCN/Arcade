/*
** EPITECH PROJECT, 2020
** Menu
** File description:
** hpp
*/

#ifndef MENU_HPP
#define MENU_HPP

#include "IGraphics.hpp"
#include "Core.hpp"

#include "MacroMenu.hpp"

class Menu {
    public:
        Menu(){};
        ~Menu(){};

        int run(IGraphics *, int, std::vector<std::string>, std::vector<std::string>, std::string, bool);

        int getGraphicLib(void);
        int getGameLib(void);

    protected:
    private:
        //init
        void initShapes(std::vector<std::string>);
        void initMenu(IGraphics *, int, std::vector<std::string>, std::vector<std::string>, std::string);

        //handle event
        void handleEvent(int);

        //Menu selection
        void addShapePutList(int, std::vector<Shape> *, std::vector<std::string>, int, int, int);
        void switchSelectionList(std::vector<Shape> *, int *, int);
        void switchSelection(Shape *, Shape *, int);
        void selectLib(std::vector<Shape>, int, bool *, int, int, bool);
        void printTopScores(void);

        //Variables
        IGraphics *_graphicLib;
        int _graphicLibUsed;
        int _gameLibUsed;

        int _selectedMenu;
        int _selectedGame;
        int _selectedGraphics;

        std::vector<Shape> _shapesGamesAvailable;
        int _nbrGames;
        std::vector<std::string> _gamesAvailable;

        std::vector<Shape> _shapesGraphicsAvailable;
        int _nbrGraphics;

        bool _inMenu;
        bool _inSelectGraph;
        bool _inSelectGame;

        Shape _shapeTitle;
        Shape _shapeGraphLib;
        Shape _shapeGameLib;
        Shape _shapeCommandRight;
        Shape _shapeCommandLeft;
        Shape _shapeCommandUp;
        Shape _shapeCommandDown;
        Shape _shapeCommandAction;
        Shape _shapeCommandPause;
        Shape _shapeCommandeQuit;
        Shape _shapeUserMenu;
        Shape _shapeWelcome;
        Shape _shapeAuthor;

        std::string _userName;
};

#endif /* !MENU_HPP */
