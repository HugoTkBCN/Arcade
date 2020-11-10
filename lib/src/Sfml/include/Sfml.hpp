/*
** EPITECH PROJECT, 2020
** Sfml
** File description:
** hpp
*/

#ifndef SFML_HPP
#define SFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include "IGraphics.hpp"

#define FONT_FILE "./fonts/fontArcadeSFML.ttf"

typedef struct drawable_t {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
} drawable_s;

typedef struct sound_t {
    sf::SoundBuffer buffer;
    sf::Sound sound;
} sound_s;

class Sfml : public IGraphics {
    public:
        Sfml();
        ~Sfml();

        virtual void clearScreen();
        virtual void addShape(Shape &) ;
        virtual void drawScreen(void);
        virtual void drawShape(int) override; // here key is the map's key
        virtual Input getInput();
        virtual bool isRunning(void) const; // check game
    protected:
    private:
        Input getEvent();
        sf::RenderWindow *_window;
        std::map<int, drawable_s> _sprites;
        std::map<int, Shape_s> _shapes;
        std::map<int, sound_s> _sounds;
        std::map<Color, sf::Color> _colors;
        bool _isRunning = true;
};

#endif /* !SFML_HPP */
