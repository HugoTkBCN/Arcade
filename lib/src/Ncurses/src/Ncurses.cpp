/*
** EPITECH PROJECT, 2020
** ncurses
** File description:
** cpp
*/

#include "Ncurses.hpp"

Ncurses::Ncurses()
{
    initscr();
    if(has_colors() == FALSE) {
        endwin();
        throw Error("Your terminal does not support color\n");
    }
    start_color();
    init_pair(Color::WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(Color::BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(Color::YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(Color::RED, COLOR_RED, COLOR_BLACK);
    init_pair(Color::GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(Color::BLUE, COLOR_BLUE, COLOR_BLACK);
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, TRUE);
    noecho();
    this->_isRunning = true;
    cbreak();
}

Ncurses::~Ncurses()
{
    endwin();
}

void Ncurses::clearScreen()
{
    clear();
}

void Ncurses::addShape(Shape &shape)
{
    if (shape.id >= 0) {
        int oldX = shape.x;
        int oldY = shape.y;
        shape.x = (shape.x / DIV_X);
        shape.y = (shape.y / DIV_Y);
        this->_shapes[shape.id] = shape;
        shape.x = oldX;
        shape.y = oldY;
    }
}

void Ncurses::drawShape(int key)
{
    if (this->_shapes[key].message != "") {
        if (this->_shapes[key].textColor)
            attron(COLOR_PAIR(this->_shapes[key].textColor));
        mvprintw(this->_shapes[key].y, this->_shapes[key].x, this->_shapes[key].message.c_str());
        if (this->_shapes[key].textColor)
            attroff(COLOR_PAIR(this->_shapes[key].textColor));
    }
}

void Ncurses::errorResizeScreen()
{
    std::string message = ERROR_MESSAGE;
    while ((getScreenWidth() < MIN_WIDTH || getScreenHeight() < MIN_HEIGHT) && isRunning()) {
        clearScreen();
        mvprintw(LINES / 2, COLS / 2 - (message.length() / 2), message.c_str());
        getInput();
        refresh();
        usleep(100000);
    }
}

void Ncurses::drawScreen(void)
{
    if (getScreenWidth() < MIN_WIDTH || getScreenHeight() < MIN_HEIGHT) {
        errorResizeScreen();
    }
    refresh();
    usleep(100000);
}

IGraphics::Input Ncurses::getInput(void)
{
    switch (getch()) {
        case 'q':
            _isRunning = false;
            return (QUIT);
        case ' ': case 10:
            return (ACTION);
        case 27:
            return (PAUSE);
        case KEY_UP:
            return (UP);
        case KEY_DOWN:
            return (DOWN);
        case KEY_LEFT:
            return (LEFT);
        case KEY_RIGHT:
            return (RIGHT);
        case '1':
            return (PREV_GAME);
        case '2':
            return (NEXT_GAME);
        case '3':
            return (PREV_LIB);
        case '4':
            return (NEXT_LIB);
        case '5':
            return (RESTART_GAME);
        case '6':
            return (MENU);
        default :
            return (NO_INPUT);
    }
    return (NO_INPUT);
}

int Ncurses::getScreenWidth(void) const
{
    return (getmaxy(stdscr));
}

int Ncurses::getScreenHeight(void) const
{
    return (getmaxx(stdscr));
}

bool Ncurses::isRunning(void) const
{ 
    return (_isRunning); 
}
