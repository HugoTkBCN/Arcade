/*
** EPITECH PROJECT, 2020
** Entrypoint
** File description:
** Sfml
*/

#include <iostream>
#include "Sfml.hpp"

IGraphics *object = nullptr;

__attribute__((constructor))
void init()
{
    object = new Sfml();
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
