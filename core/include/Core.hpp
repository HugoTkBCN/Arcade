/*
** EPITECH PROJECT, 2020
** Core
** File description:
** hpp
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <dirent.h>
#include <regex>
#include <cstdlib>
#include "Error.hpp"
#include "IGraphics.hpp"
#include "IGames.hpp"
#include "GraphicLibLoader.hpp"
#include "GameLibLoader.hpp"
#include "User.hpp"
#include "Menu.hpp"

#include "MacroCore.hpp"

class Core {
    public:
        Core(char *);
        ~Core();

        static int checkArgs(int, char **);
        int runArcade(void);
        static Shape fillShape(int, int, int, std::string, std::string, Color, size_t);

    protected:
    private:
        bool runLoadLibs(bool, int, int);
        bool runGame(void);

        void getGraphicsLibs(void);
        void getGamesLibs(void);
        std::string getLibName(std::string);

        void getUserName(void);
        std::string _userName;

        IGraphics *_graphicLib;

        loadGame _loaderGame;
        loadGraph _loaderGraph;

        IGames *_gameLib;
};

#endif /* !CORE_HPP_ */