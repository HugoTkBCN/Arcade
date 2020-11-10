/*
** EPITECH PROJECT, 2020
** User
** File description:
** hpp
*/

#ifndef USER_HPP
#define USER_HPP

#include "IGraphics.hpp"
#include "Core.hpp"
#include <math.h>

#include "MacroUser.hpp"

class User {
    public:
        User(IGraphics *);
        ~User();
        std::string getUserName(void);
    protected:
    private:
        void printKeyboard(void);
        void InitKeboard(void);
        void addShapeToKeyBoard(Shape, int, int, int, std::string, std::string, Color, int);
        void handleEvent(int);
        void switchSelectedKey(std::vector<Shape> *, int *, int);

        std::vector<Shape> _keyboard;
        int _nbrKeys;
        int _keySelected;
        Shape _userNameShape;
        Shape _enterUserNameShape;
        IGraphics *_graphicLib;
};

#endif /* !USER_HPP */
