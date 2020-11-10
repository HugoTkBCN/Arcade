/*
** EPITECH PROJECT, 2020
** Sld2
** File description:
** cpp
*/

#include "Sdl2.hpp"

Sdl2::Sdl2(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw Error(SDL_GetError(), "Sdl2::Sdl2");
    TTF_Init();
    _window = SDL_CreateWindow(_gameName.c_str(), SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, _screenWidth,
                               _screenHeight, SDL_WINDOW_SHOWN);
    if (!_window)
        throw Error(SDL_GetError(), "Sdl2::Sdl2");
    _font = TTF_OpenFont(FONT_FILE, 24);
    if (!_font)
        throw Error(SDL_GetError(), "Sdl2::Sdl2");
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    initColors();
    _isRunning = true;
}

Sdl2::~Sdl2(void)
{
    for (std::pair<int, SDL_Texture *> sprite: _sprites)
        SDL_DestroyTexture(sprite.second);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_Quit();
}

void Sdl2::initColors(void)
{
    _colors[WHITE] = {255, 255, 255, 0};
    _colors[BLACK] = {0, 0, 0, 0};
    _colors[YELLOW] = {255, 239, 25, 255};
    _colors[RED] = {255, 0, 0, 255};
    _colors[GREEN] = {0, 255, 0, 255};
    _colors[BLUE] = {0, 0, 255, 255};
}

void Sdl2::clearScreen(void)
{
    SDL_RenderClear(_renderer);
}

void Sdl2::drawScreen(void)
{
    SDL_UpdateWindowSurface(_window);
    SDL_RenderPresent(_renderer);
}

void Sdl2::renderText(Shape textShape, SDL_Rect &textRect)
{
    int width, height = 0;

    TTF_CloseFont(_font);
    _font = TTF_OpenFont(FONT_FILE, textShape.textSize);
    if (!_font)
        throw Error(SDL_GetError(), "Sdl2::Sdl2");
    else if (_colors.find(textShape.textColor) == _colors.end())
        throw Error("Invalid font color", "Sdl2::renderText");
    _color = _colors[textShape.textColor];
    _surface = TTF_RenderText_Solid(_font, textShape.message.c_str(), _color);
    _sprites[textShape.id] = SDL_CreateTextureFromSurface(_renderer, _surface);
    width = _surface->w;
    height = _surface->h;
    SDL_FreeSurface(_surface);
    textRect.x = textShape.x;
    textRect.y = textShape.y;
    textRect.w = width;
    textRect.h = height;
}

void Sdl2::drawShape(int key)
{
    SDL_Rect textureRect;
    int w, h = 0;

    if (_sprites.find(key) == _sprites.end()
        || _shapes.find(key) == _shapes.end()) { // check if is in map
        std::cerr << "Error: Cannot find shape at index " << key << "\n";
        return;
    }
    else if (_shapes[key].filePath != "") { // is a sprite
        SDL_QueryTexture(_sprites[key], NULL, NULL, &w, &h);
        textureRect.x = _shapes[key].x;
        textureRect.y = _shapes[key].y;
        textureRect.w = w;
        textureRect.h = h;
    } else // else, it is a text
        renderText(_shapes[key], textureRect);
    // draw it
    SDL_RenderCopy(_renderer, _sprites[key], NULL, &textureRect);
}

void Sdl2::addShape(Shape &shape)
{
    std::string saveFilepath = "";
    if (_shapes[shape.id].filePath != "")
        saveFilepath = _shapes[shape.id].filePath;
    _shapes[shape.id] = shape;
    if (shape.filePath != "") { // if is a sprite, not a text
        if (!_sprites[shape.id])
            _sprites[shape.id] = IMG_LoadTexture(_renderer, shape.filePath.c_str());
        else if (_shapes[shape.id].filePath != saveFilepath)
            _sprites[shape.id] = IMG_LoadTexture(_renderer, shape.filePath.c_str());
        if (!_sprites[shape.id])
            std::cerr << "Error opening sprite " << shape.filePath << "\n" << SDL_GetError();
    } else {
        SDL_Rect textRect;
        renderText(shape, textRect);
    }
}

bool Sdl2::isRunning(void) const { return (_isRunning); }

IGraphics::Input Sdl2::getKeyValue(SDL_Event evt)
{
    switch (evt.key.keysym.sym) {
    case SDLK_q:
        _isRunning = false;
        return (Input::QUIT);
    case SDLK_LEFT:
        return (Input::LEFT);
    case SDLK_UP:
        return (Input::UP);
    case SDLK_RIGHT:
        return (Input::RIGHT);
    case SDLK_DOWN:
        return (Input::DOWN);
    case SDLK_SPACE: case SDLK_RETURN:
        return (Input::ACTION);
    case SDLK_ESCAPE:
        return (Input::PAUSE);
    case SDLK_1:
        return (Input::PREV_GAME);
    case SDLK_2:
        return (Input::NEXT_GAME);
    case SDLK_3:
        return (Input::PREV_LIB);
    case SDLK_4:
        return (Input::NEXT_LIB);
    case SDLK_5:
        return (Input::RESTART_GAME);
    case SDLK_6:
        return (Input::MENU);
    default:
        break;
    }
    return (Input::NO_INPUT);
}

IGraphics::Input Sdl2::getInput(void)
{
    SDL_Event evt;

    while (SDL_PollEvent(&evt) == 1) {
        switch (evt.type) {
        case SDL_QUIT:
            _isRunning = false;
            return (Input::QUIT);
        case SDL_KEYDOWN:
            return (getKeyValue(evt));
        default:
            break;
        }
    }
    return (Input::NO_INPUT);
}
