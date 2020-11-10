/*
** EPITECH PROJECT, 2020
** Entrypoint
** File description:
** Pacman
*/

#include <iostream>
#include "Pacman.hpp"

IGames *object = nullptr;

__attribute__((constructor))
void init()
{
    object = new Pacman();
}

__attribute__((destructor))
void end()
{
    delete object;
}

extern "C" IGames *entryPoint()
{
    return object;
}
