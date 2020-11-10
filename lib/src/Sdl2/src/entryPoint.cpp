/*
** EPITECH PROJECT, 2020
** Entrypoint
** File description:
** sdl2
*/

#include <iostream>
#include "Sdl2.hpp"

IGraphics *object = nullptr;

__attribute__((constructor))
void init()
{
    object = new Sdl2();
}

__attribute__((destructor))
void end()
{
    delete object;
}

extern "C" IGraphics *entryPoint()
{
    return object;
}
