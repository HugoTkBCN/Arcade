/*
** EPITECH PROJECT, 2020
** game li loader
** File description:
** cpp
*/

#include "GameLibLoader.hpp"

GameLibLoader::GameLibLoader()
{
    this->_handle = nullptr;
    this->_libLoaded = false;
    this->_entryPoint = nullptr;
}

GameLibLoader::~GameLibLoader()
{
    unloadLib();
}

IGames *GameLibLoader::loadLib(std::string pathToLib)
{
    if (this->_handle != nullptr && this->_libLoaded == true)
        unloadLib();
    if ((this->_handle = dlopen(pathToLib.c_str(), RTLD_LAZY))) {
        IGames* (*create_games)();
        create_games = (IGames* (*)())dlsym(this->_handle, "entryPoint");
        this->_entryPoint = (IGames*)create_games();
        this->_libLoaded = true;
    } else {
        std::cout << dlerror() << std::endl;
        throw Error("./dlopen");
    }
    return (this->_entryPoint);
}

void GameLibLoader::unloadLib()
{
    if (this->_handle != nullptr && this->_libLoaded == true)
        dlclose(this->_handle);
    this->_handle = nullptr;
    this->_libLoaded = false;
    this->_entryPoint = nullptr;
}
