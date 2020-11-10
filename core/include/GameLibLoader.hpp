/*
** EPITECH PROJECT, 2020
** Game lib loader
** File description:
** hpp
*/

#ifndef GAMELIBLOADER_HPP
#define GAMELIBLOADER_HPP

#include <string>
#include <iostream>
#include <dlfcn.h>
#include "IGames.hpp"
#include "Error.hpp"
#include <vector>

class GameLibLoader {
    public:
        GameLibLoader();
        ~GameLibLoader();
        IGames *loadLib(std::string);
        void unloadLib();
    protected:
    private:
        void *_handle;
        bool _libLoaded;
        IGames* _entryPoint;
};

typedef struct loadGame_s {
    std::vector<std::string> gamesPaths;
    std::vector<std::string> gamesAvailable;
    int gameLibUsed;
    GameLibLoader loaderGame;
} loadGame;

#endif /* !GAMELIBLOADER_HPP */
