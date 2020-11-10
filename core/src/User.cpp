/*
** EPITECH PROJECT, 2020
** User
** File description:
** cpp
*/

#include "User.hpp"

User::User(IGraphics *graphicLib)
{
    this->_graphicLib = graphicLib;
    this->_enterUserNameShape = Core::fillShape(INDEX_SHAPE_ENTER_USER_NAME, X_ASK_NAME, Y_ASK_NAME, NO_PATH, TEXT_ASK_NAME, COLOR_TEXT, SIZE_TITLE);
    this->_graphicLib->addShape(this->_enterUserNameShape);
    this->_userNameShape = Core::fillShape(INDEX_SHAPE_USERNAME, X_USERNAME, Y_USERNAME, NO_PATH, INIT_USER_NAME, COLOR_USERNAME_INPUT, SIZE_SUBTITLE);
    this->_graphicLib->addShape(this->_userNameShape);
    InitKeboard();
    this->_nbrKeys = this->_keyboard.size();
    this->_keySelected = INIT_KEY_SELECTED;
}

User::~User()
{
}

void User::addShapeToKeyBoard(Shape graph, int id, int x, int y, std::string path, std::string message, Color color, int size)
{
    graph = Core::fillShape(id, x, y, path, message, color, size);
    this->_graphicLib->addShape(graph);
    this->_keyboard.push_back(graph);
}

void User::InitKeboard()
{
    std::string letter;
    Shape graph;
    int i, y, x = 0;

    for (i = 0, y = 0 , x = 0; KEYBOARD[i]; i++, x++) {
        letter.push_back(KEYBOARD[i]);
        if (i % LETTER_PER_LINE == 0) {
            x = 0;
            y++;
        }
        addShapeToKeyBoard(graph, INDEX_SHAPE_KEYBOARD + i, X_KEYBOARD + x * X_SEPARATION_KEYBOARD, Y_KEYBOARD + y * Y_SEPARATION_KEYBOARD, NO_PATH, letter, COLOR_NOT_SELECTED, SIZE_NOT_SELECTED);
        letter = "";
    }
    addShapeToKeyBoard(graph, INDEX_SHAPE_KEYBOARD + i++, X_DELETE, Y_DELETE, NO_PATH, TEXT_DELETE, COLOR_NOT_SELECTED, SIZE_NOT_SELECTED);
    addShapeToKeyBoard(graph, INDEX_SHAPE_KEYBOARD + i, X_DONE, Y_DONE, NO_PATH, TEXT_DONE, COLOR_NOT_SELECTED, SIZE_NOT_SELECTED);
}

void User::printKeyboard()
{
    for (int i = INDEX_SHAPE_KEYBOARD; i < INDEX_SHAPE_KEYBOARD + this->_nbrKeys; i++)
        this->_graphicLib->drawShape(i);
}

void User::switchSelectedKey(std::vector<Shape> *shapes, int *selected, int index)
{
    (*shapes)[*selected].textColor = COLOR_NOT_SELECTED;
    (*shapes)[*selected].textSize = SIZE_NOT_SELECTED;
    this->_graphicLib->addShape((*shapes)[*selected]);
    *selected = index;
    (*shapes)[*selected].textColor = COLOR_SELECTED;
    (*shapes)[*selected].textSize = SIZE_SELECTED;
    this->_graphicLib->addShape((*shapes)[*selected]);
}

void User::handleEvent(int input)
{
    switch (input) {
        case IGraphics::UP:
            if (this->_keySelected == INDEX_SPACE(this->_nbrKeys))
                switchSelectedKey(&this->_keyboard, &this->_keySelected, INDEX_LAST_KEY(this->_nbrKeys));
            else if (this->_keySelected >= LETTER_PER_LINE && this->_keySelected != INDEX_DELETE(this->_nbrKeys))
                switchSelectedKey(&this->_keyboard, &this->_keySelected, INDEX_LINE_UP(this->_keySelected));
            break;
        case IGraphics::DOWN:
            if (this->_keySelected < INDEX_LAST_LINE && this->_keySelected != INDEX_DELETE(this->_nbrKeys))
                switchSelectedKey(&this->_keyboard, &this->_keySelected, INDEX_LINE_DOWN(this->_nbrKeys, this->_keySelected));
            else if (this->_keySelected != INDEX_DELETE(this->_nbrKeys))
                switchSelectedKey(&this->_keyboard, &this->_keySelected, INDEX_SPACE(this->_nbrKeys));
            break;
        case IGraphics::LEFT:
            if (this->_keySelected == INDEX_DELETE(this->_nbrKeys))
                switchSelectedKey(&this->_keyboard, &this->_keySelected, INDEX_LAST_CHAR_FIST_LINE);
            else if (this->_keySelected > INDEX_FIRST_CHAR_FIST_LINE && this->_keySelected != INDEX_SPACE(this->_nbrKeys))
                switchSelectedKey(&this->_keyboard, &this->_keySelected, INDEX_LEFT_KEY(this->_keySelected));
            break;
        case IGraphics::RIGHT:
            if (this->_keySelected == INDEX_LAST_CHAR_FIST_LINE)
                switchSelectedKey(&this->_keyboard, &this->_keySelected, INDEX_DELETE(this->_nbrKeys));
            else if (this->_keySelected < LAST_CHAR_LINE(this->_keySelected) && this->_keySelected < INDEX_DELETE(this->_nbrKeys))
                switchSelectedKey(&this->_keyboard, &this->_keySelected, INDEX_RIGHT_KEY(this->_keySelected));
            break;
        case IGraphics::ACTION:
            if (this->_keySelected == INDEX_SPACE(this->_nbrKeys))
                this->_userNameShape.message.push_back(LAST_CHAR);
            else if (this->_keySelected == INDEX_DELETE(this->_nbrKeys) && this->_userNameShape.message.size() > 1) {
                this->_userNameShape.message.pop_back();
                this->_graphicLib->addShape(this->_userNameShape);
            } else if (this->_keySelected != INDEX_DELETE(this->_nbrKeys)) {
                this->_userNameShape.message.push_back(this->_keyboard[this->_keySelected].message[0]);
                this->_graphicLib->addShape(this->_userNameShape);
            }
            break;
        default:
            break;
    }
}

std::string User::getUserName(void)
{
    this->_keyboard[this->_keySelected].textColor = COLOR_SELECTED;
    this->_keyboard[this->_keySelected].textSize = SIZE_SELECTED;
    this->_graphicLib->addShape(this->_keyboard[this->_keySelected]);
    while (this->_graphicLib->isRunning() && this->_userNameShape.message.back() != LAST_CHAR && this->_userNameShape.message.size() > 0) {
        this->_graphicLib->clearScreen();
        this->_graphicLib->drawShape(INDEX_SHAPE_ENTER_USER_NAME);
        handleEvent(this->_graphicLib->getInput());
        printKeyboard();
        this->_graphicLib->drawShape(this->_userNameShape.id);
        this->_graphicLib->drawScreen();
    }
    (this->_userNameShape.message[0] == INIT_USER_NAME[0]) ? this->_userNameShape.message.erase(0, 1) : 0;
    if (this->_userNameShape.message.size() > 1)
        this->_userNameShape.message.erase(this->_userNameShape.message.size() - 1, this->_userNameShape.message.size());
    return (this->_userNameShape.message);
}