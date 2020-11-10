/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** graphic lib loader
*/

#include "GraphicLibLoader.hpp"

GraphicLibLoader::GraphicLibLoader()
{
    this->_handle = nullptr;
    this->_libLoaded = false;
    this->_entryPoint = nullptr;
}

GraphicLibLoader::~GraphicLibLoader()
{
    unloadLib();
}

IGraphics *GraphicLibLoader::loadLib(std::string pathToLib)
{
    if (this->_handle != nullptr && this->_libLoaded == true)
        unloadLib();
    if ((this->_handle = dlopen(pathToLib.c_str(), RTLD_LAZY))) {
        IGraphics* (*create_graphics)();
        create_graphics = (IGraphics* (*)())dlsym(this->_handle, "entryPoint");
        this->_entryPoint = (IGraphics*)create_graphics();
        this->_libLoaded = true;
    } else {
        std::cout << dlerror() << std::endl;
        throw Error("dlopen", "GraphicLibLoader::loadLib");
    }
    return (this->_entryPoint);
}

void GraphicLibLoader::unloadLib()
{
    if (this->_handle != nullptr && this->_libLoaded == true)
        dlclose(this->_handle);
    this->_handle = nullptr;
    this->_libLoaded = false;
    this->_entryPoint = nullptr;
}
