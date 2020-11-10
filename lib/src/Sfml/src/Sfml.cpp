/*
** EPITECH PROJECT, 2020
** Sfml
** File description:
** cpp
*/

#include "Sfml.hpp"

Sfml::Sfml()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arcade");
    this->_colors[WHITE] = sf::Color::White;
    this->_colors[BLACK] = sf::Color::Black;
    this->_colors[YELLOW] = sf::Color::Yellow;
    this->_colors[RED] = sf::Color::Red;
    this->_colors[GREEN] = sf::Color::Green;
    this->_colors[BLUE] = sf::Color::Blue;
    this->_window->setFramerateLimit(60);
}

Sfml::~Sfml()
{
    this->_window->close();
    delete this->_window;
}

void Sfml::clearScreen()
{
    this->_window->clear();
}

void Sfml::addShape(Shape &shape)
{
    this->_shapes[shape.id] = shape;
    if (shape.filePath != "") {
        if (!this->_sprites[shape.id].texture.loadFromFile(shape.filePath))
            return;
        this->_sprites[shape.id].sprite.setTexture(this->_sprites[shape.id].texture);
    } else {
        if (!this->_sprites[shape.id].font.loadFromFile(FONT_FILE))
            return;
        this->_sprites[shape.id].text.setFont(this->_sprites[shape.id].font);
        this->_sprites[shape.id].text.setCharacterSize(shape.textSize);
        this->_sprites[shape.id].text.setString(shape.message);
    }
}

void Sfml::drawScreen(void)
{
    this->_window->display();
}

void Sfml::drawShape(int key)
{
    this->_sprites[key].sprite.setPosition(this->_shapes[key].x, this->_shapes[key].y);
    this->_window->draw(this->_sprites[key].sprite);
    this->_sprites[key].text.setPosition(this->_shapes[key].x, this->_shapes[key].y);
    this->_sprites[key].text.setCharacterSize(this->_shapes[key].textSize);
    this->_sprites[key].text.setFillColor(_colors[this->_shapes[key].textColor]);
    this->_window->draw(this->_sprites[key].text);
}

IGraphics::Input Sfml::getEvent()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return this->ACTION;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return this->LEFT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return this->RIGHT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return this->UP;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return this->DOWN;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return this->PAUSE;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        this->_isRunning = false;
        return this->QUIT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        return this->PREV_GAME;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        return this->NEXT_GAME;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        return this->PREV_LIB;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        return this->NEXT_LIB;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        return this->RESTART_GAME;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        return this->MENU;
    return this->NO_INPUT;
}

IGraphics::Input Sfml::getInput()
{
    sf::Event event;
    while (this->_window->pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->_isRunning = false;
            return IGraphics::QUIT;
        case sf::Event::KeyPressed:
            return getEvent();
        default:
            return this->NO_INPUT;
        }
    }
    return this->NO_INPUT;
}

bool Sfml::isRunning(void) const
{
    return this->_isRunning;
}
