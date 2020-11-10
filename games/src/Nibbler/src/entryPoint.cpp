/*
** EPITECH PROJECT, 2020
** Entrypoint
** File description:
** Nibbler
*/

#include <iostream>
#include "Nibbler.hpp"

IGames *object = nullptr;

__attribute__((constructor))
void init()
{
    object = new Nibbler();
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
