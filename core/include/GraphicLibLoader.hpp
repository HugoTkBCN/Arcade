/*
** EPITECH PROJECT, 2020
** lib loader graphic
** File description:
** hpp
*/

#ifndef GRAPHICLIBLOADER_HPP
#define GRAPHICLIBLOADER_HPP

#include <string>
#include <iostream>
#include <dlfcn.h>
#include "IGraphics.hpp"
#include "Error.hpp"
#include <vector>

class GraphicLibLoader {
    public:
        GraphicLibLoader();
        ~GraphicLibLoader();

        IGraphics *loadLib(std::string);
        void unloadLib();

    protected:
    private:
        void *_handle;
        bool _libLoaded;
        IGraphics *_entryPoint;
};

typedef struct loadGraph_s {
    std::vector<std::string> graphicsPaths;
    std::vector<std::string> graphicsAvailable;
    int graphicLibUsed;
    GraphicLibLoader loaderGraphic;
} loadGraph;

#endif /* !GRAPHICLIBLOADER_HPP */