/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** main file
*/

#include "Core.hpp"

void displayUsage(char *binaryName)
{
    std::cout << "Usage:" << "\n";
    std::cout << binaryName << " LIBRARY"<< "\n\n";
    std::cout << "LIBRARY    The graphics rendering library" << "\n\n";
    std::cout << "Read the documentation (./doc/Arcade_documentation.pdf) for more information" << "\n";
}

int main(int ac, char **av)
{
    int ret = 0;
    if ((ret = Core::checkArgs(ac, av)) != 0) {
        displayUsage(av[0]);
        return (ret == EXIT_HELP ? EXIT_SUCCESS : EXIT_ERROR);
    } else {
        Core core(av[1]);
        return (core.runArcade());
    }
    return (84);
}
