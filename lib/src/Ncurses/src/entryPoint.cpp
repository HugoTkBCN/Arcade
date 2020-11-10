/*
** EPITECH PROJECT, 2020
** Entrypoint
** File description:
** ncurses
*/

#include <iostream>
#include "Ncurses.hpp"

IGraphics *object = nullptr;

__attribute__((constructor))
void init()
{
    object = new Ncurses();
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
