/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** header file for SDL2 IGraphics library
*/

#ifndef SDL2_HPP
#define SDL2_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "IGraphics.hpp"
#include "Error.hpp"

#define FONT_FILE "./fonts/fontArcadeSDL.ttf"

class Sdl2: public IGraphics {
public:
    Sdl2(void);
    ~Sdl2(void);
    void clearScreen(void) override;
    void addShape(Shape &) override;
    void drawScreen(void) override;
    void drawShape(int) override;
    Input getInput(void) override;
    Input getKeyValue(SDL_Event evt);
    bool isRunning(void) const override;
    void renderText(Shape textShape, SDL_Rect &);
    void initColors(void);
private:
    SDL_Window *_window = NULL;
    TTF_Font *_font = NULL;
    SDL_Renderer *_renderer = NULL;
    std::string _gameName = "Arcade";
    int _screenWidth = 800;
    int _screenHeight = 600; // TODO change, or pass as arg
    bool _isRunning;
    SDL_Surface *_surface;
    SDL_Color _color;
    std::map<int, Shape> _shapes;
    std::map<int, SDL_Texture *> _sprites;
    std::unordered_map<Color, SDL_Color> _colors;
};

#endif /* !SDL2_HPP */
