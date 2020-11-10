/*
** EPITECH PROJECT, 2020
** Core
** File description:
** cpp
*/

#include "Core.hpp"

Core::Core(char *pathLibGraph)
{
    this->_loaderGraph.graphicsPaths.push_back(pathLibGraph);
    this->_loaderGraph.graphicsAvailable.push_back(getLibName(pathLibGraph));
    getGraphicsLibs();
    getGamesLibs();
    this->_loaderGraph.graphicLibUsed = 0;
    this->_loaderGame.gameLibUsed = -1;
}

Core::~Core()
{
    this->_loaderGraph.loaderGraphic.unloadLib();
}

Shape Core::fillShape(int id, int x, int y, std::string filePath, std::string message, Color textColor, size_t textSize)
{
    Shape shape;

    shape.x = x;
    shape.y = y;
    shape.id = id;
    shape.message = message;
    shape.filePath = filePath;
    shape.textColor = textColor;
    shape.textSize = textSize;
    return (shape);
}

std::string Core::getLibName(std::string lib)
{
    std::string name;

    if (lib[1] == '/')
        name = lib.substr(strlen("./lib/lib_arcade_"));
    else if (lib[3] == '/')
        name = lib.substr(strlen("lib/lib_arcade_"));
    else
        name = lib.substr(strlen("lib_arcade_"));
    return (name.substr(0, name.length() - 3));
}

void Core::getGraphicsLibs(void)
{
    struct dirent **pathLib;
    std::cmatch tmp;
    std::regex const regexLib("^lib_arcade_[a-zA-Z0-9_]*.so");
    int nbrFiles = 0;
    std::string nameLib;

    if ((nbrFiles = scandir("./lib", &pathLib, nullptr, alphasort)) < 0)
        throw Error("./lib : no such file or directory");
    for (int i = 0 ; i < nbrFiles ; i++) {
        nameLib = pathLib[i]->d_name;
        if (std::regex_match(nameLib.c_str(), tmp, regexLib) &&
            std::find(this->_loaderGraph.graphicsPaths.begin(), this->_loaderGraph.graphicsPaths.end(), "lib/" + nameLib) == this->_loaderGraph.graphicsPaths.end() &&
            std::find(this->_loaderGraph.graphicsPaths.begin(), this->_loaderGraph.graphicsPaths.end(), "./lib/" + nameLib) == this->_loaderGraph.graphicsPaths.end()) {
            this->_loaderGraph.graphicsPaths.push_back("lib/" + nameLib);
            this->_loaderGraph.graphicsAvailable.push_back(getLibName(nameLib));
        }
        free(pathLib[i]);
    }
}

void Core::getGamesLibs(void)
{
    struct dirent **pathLib;
    std::cmatch tmp;
    std::regex const regexLib("^lib_arcade_[a-zA-Z0-9_]*.so");
    int nbrFiles = 0;
    std::string nameLib;

    if ((nbrFiles = scandir("./games", &pathLib, nullptr, alphasort)) < 0)
        throw Error("./games : no such file or directory");
    for (int i = 0 ; i < nbrFiles ; i++) {
        nameLib = pathLib[i]->d_name;
        if (std::regex_match(nameLib.c_str(), tmp, regexLib)) {
            this->_loaderGame.gamesPaths.push_back("games/" + nameLib);
            this->_loaderGame.gamesAvailable.push_back(getLibName(nameLib));
        }
        free(pathLib[i]);
    }
}

int Core::checkArgs(int ac, char **av)
{
    if (ac != 2)
        return (EXIT_ERROR);
    if (strlen(av[1]) == 2)
        if (av[1][0] == '-' && av[1][1] == 'h')
            return (EXIT_HELP);
    std::ifstream libPath(av[1]);
    if (libPath.fail())
        return (EXIT_ERROR);
    return (EXIT_SUCCESS);
}

bool Core::runLoadLibs(bool skip, int gameLibChosedInMenu, int graphLibChosedInMenu)
{
    if (gameLibChosedInMenu != this->_loaderGame.gameLibUsed && !skip) {
        this->_loaderGame.gameLibUsed = gameLibChosedInMenu;
        this->_gameLib = this->_loaderGame.loaderGame.loadLib(this->_loaderGame.gamesPaths[this->_loaderGame.gameLibUsed]);
    }
    if (graphLibChosedInMenu != this->_loaderGraph.graphicLibUsed) {
        this->_loaderGraph.graphicLibUsed = graphLibChosedInMenu;
        this->_graphicLib = this->_loaderGraph.loaderGraphic.loadLib(this->_loaderGraph.graphicsPaths[this->_loaderGraph.graphicLibUsed]);
    }
    return (false);
}

bool Core::runGame(void)
{
    this->_gameLib->runGame(this->_graphicLib, this->_loaderGraph, this->_userName);
    this->_graphicLib = this->_gameLib->getLibGraphic();
    if (this->_gameLib->isGameChanged() != 0) {
        if (this->_gameLib->isGameChanged() == 1)
            this->_loaderGame.gameLibUsed = this->_loaderGame.gameLibUsed - 1 >= 0 ?
                this->_loaderGame.gameLibUsed - 1 : (int)this->_loaderGame.gamesPaths.size() - 1;
        else
            this->_loaderGame.gameLibUsed = this->_loaderGame.gameLibUsed + 1 <= (int)this->_loaderGame.gamesPaths.size() - 1 ?
                this->_loaderGame.gameLibUsed + 1 : 0;
        this->_gameLib = this->_loaderGame.loaderGame.loadLib(this->_loaderGame.gamesPaths[this->_loaderGame.gameLibUsed]);
        return (true);
    }
    return (false);
}

int Core::runArcade(void)
{
    this->_graphicLib = this->_loaderGraph.loaderGraphic.loadLib(this->_loaderGraph.graphicsPaths[this->_loaderGraph.graphicLibUsed]);
    User user(this->_graphicLib);
    this->_userName = user.getUserName();
    Menu menu;
    bool skip = false;
    while (this->_graphicLib->isRunning()) {
        if (menu.run(this->_graphicLib, this->_loaderGraph.graphicLibUsed, this->_loaderGraph.graphicsAvailable,
                     this->_loaderGame.gamesAvailable, this->_userName, skip) == MENU_EXITED)
            return (EXIT_SUCCESS);
        skip = runLoadLibs(skip, menu.getGameLib(), menu.getGraphicLib());
        if (this->_graphicLib->isRunning())
            skip = runGame();
    }
    return (EXIT_SUCCESS);
}
