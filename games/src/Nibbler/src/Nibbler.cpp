/*
** EPITECH PROJECT, 2020
** Nibbler
** File description:
** cpp
*/

#include "Nibbler.hpp"

/************************************************************************************/
/*                                   UTILS                                          */
/************************************************************************************/

int Nibbler::isGameChanged(void)
{
    return (this->_changeGame);
}

IGraphics *Nibbler::getLibGraphic(void)
{
    return (this->_libGraphic);
}

void Nibbler::setShape(Shape &shape, int index, int x, int y, std::string path, std::string message, Color color, int size)
{
    shape = fillGameShape(index, x, y, path, message, color, size);
    this->_libGraphic->addShape(shape);
}

Shape Nibbler::fillGameShape(int id, int x, int y, std::string filePath, std::string message, Color textColor, size_t textSize)
{
    Shape shape;

    shape.x = x;
    shape.y = y;
    shape.id = id;
    shape.message = message;
    shape.filePath = filePath;
    shape.textColor = textColor;
    shape.textSize = textSize;
    return (shape);
}

bool Nibbler::startPause(void)
{
    PauseNibbler pause;
    int ret = pause.runPauseNibbler(this->_libGraphic);

    if (ret == PauseNibbler::RESTART)
        initGame();
    else if (ret == PauseNibbler::MENU)
        return (false);
    return (true);
}

void Nibbler::changeTailDirection(void)
{
    if (this->_shapeTailSnake.y < this->_snake.snakePositions.back().y)
        this->_shapeTailSnake.filePath = PATH_TO_DOWN_TAIL;
    else if (this->_shapeTailSnake.y > this->_snake.snakePositions.back().y)
        this->_shapeTailSnake.filePath = PATH_TO_UP_TAIL;
    else if (this->_shapeTailSnake.x > this->_snake.snakePositions.back().x)
        this->_shapeTailSnake.filePath = PATH_TO_LEFT_TAIL;
    else if (this->_shapeTailSnake.x < this->_snake.snakePositions.back().x)
        this->_shapeTailSnake.filePath = PATH_TO_RIGHT_TAIL;
    this->_libGraphic->addShape(this->_shapeTailSnake);
}

void Nibbler::switchHeadDirection(std::string pathToSprite, int direction)
{
    this->_shapeHeadSnake.filePath = pathToSprite;
    this->_libGraphic->addShape(this->_shapeHeadSnake);
    this->_snake.direction = direction;
}

/************************************************************************************/
/*                                   INIT                                           */
/************************************************************************************/

void Nibbler::getWallFoodsPositions(std::vector<std::string> map)
{
    int y = 0, x= 0;

    this->_wallsPosition.clear();
    this->_foodsPosition.clear();
    for (std::string &line : map) {
        x = 0;
        for (char &character : line) {
            if (character == '#')
                this->_wallsPosition.push_back(Position{X_WALL + x * WALL_SIZE, Y_WALL + y * WALL_SIZE});
            else if (character == '*')
                this->_foodsPosition.push_back(Position{X_WALL + x * FOOD_SIZE, Y_WALL + y * FOOD_SIZE});
            x++;
        }
        y++;
    }
}

bool Nibbler::getMap(std::string filePath)
{
    std::ifstream in(filePath.c_str());
    std::vector<std::string> map;
    std::string str;

    if(!in)
        return (false);
    while (std::getline(in, str))
        if(str.size() > 0)
            map.push_back(str);
    in.close();
    getWallFoodsPositions(map);
    return (true);
}

void Nibbler::initGameShapes(bool initSnake)
{
    setShape(this->_shapeNibblerTitle, INDEX_SHAPE_TITLE_NIBBLER, X_TITLE, Y_TITLE, NO_PATH, TEXT_TITLE_NIBBLER, COLOR_TITLE, SIZE_TITLE);
    setShape(this->_shapeNibblerScore, INDEX_SHAPE_SCORE_NIBBLER, X_SCORE, Y_SCORE, NO_PATH, TEXT_SCORE_NIBBLER + std::to_string(this->_score), COLOR_SCORE, SIZE_SCORE);
    setShape(this->_shapeWall, INDEX_SHAPE_WALL, X_WALL, Y_WALL, PATH_TO_WALL, WALL_CHAR, Color::BLUE, WALL_SIZE);
    initSnake ? setShape(this->_shapeHeadSnake, INDEX_SHAPE_HEAD_SNAKE, X_HEAD, Y_HEAD, PATH_TO_RIGHT_HEAD, HEAD_CHAR, Color::GREEN, SNAKE_SIZE) : void(0);
    initSnake ? setShape(this->_shapeBodySnake, INDEX_SHAPE_BODY_SNAKE, X_HEAD, X_HEAD, PATH_TO_BODY, BODY_CHAR, Color::GREEN, SNAKE_SIZE) : void(0);
    initSnake ? setShape(this->_shapeTailSnake, INDEX_SHAPE_TAIL_SNAKE, X_HEAD, X_HEAD, PATH_TO_RIGHT_TAIL, TAIL_CHAR, Color::GREEN, SNAKE_SIZE) : void(0);
    setShape(this->_shapeFood, INDEX_SHAPE_FOOD, X_HEAD, X_HEAD, PATH_TO_FOOD, FOOD_CHAR, Color::YELLOW, FOOD_SIZE);
}

void Nibbler::initSnake(void)
{
    this->_snake.direction = DIR_RIGHT;
    this->_snake.size = INIT_SIZE;
    this->_snake.snakePositions.clear();
    for (int i = 0; i < this->_snake.size; i++)
        this->_snake.snakePositions.push_back(Position{X_HEAD - (i * SNAKE_SIZE), Y_HEAD});
    this->_snakeSpeed = INIT_SPEED;
    this->_saveSnakeSpeed = INIT_SPEED;
}

void Nibbler::initGame(void)
{
    this->_score = 0;
    this->_inNibbler = true;
    this->_gameStatus = GAMING;
    this->_changeGame = 0;
    initSnake();
    srand(time(NULL));
    if(!getMap(PATH_TO_MAPS+std::to_string(rand() % NUMBER_MAP + 1) +".txt"))
        throw Error("No such file");
    initGameShapes(true);
    srand(time(NULL));
    this->_clockGame = std::chrono::steady_clock::now();
}

/************************************************************************************/
/*                                   PRINT                                          */
/************************************************************************************/

void Nibbler::printAtPosition(Shape &shape, int x, int y)
{
    shape.x = x;
    shape.y = y;
    this->_libGraphic->addShape(shape);
    this->_libGraphic->drawShape(shape.id);
}

void Nibbler::printSnake(void)
{
    int i = 0;
    printAtPosition(this->_shapeHeadSnake, this->_snake.snakePositions[i].x, this->_snake.snakePositions[i].y);
    for (i = 1; i < this->_snake.size - 1; i++)
        printAtPosition(this->_shapeBodySnake, this->_snake.snakePositions[i].x, this->_snake.snakePositions[i].y);
    printAtPosition(this->_shapeTailSnake, this->_snake.snakePositions[i].x, this->_snake.snakePositions[i].y);

}

void Nibbler::printMap(std::vector<Position> positions, Shape &shape)
{
    for (Position &pos : positions)
        printAtPosition(shape, pos.x, pos.y);
}

void Nibbler::printGame(void)
{
    this->_libGraphic->drawShape(INDEX_SHAPE_TITLE_NIBBLER);
    this->_libGraphic->drawShape(INDEX_SHAPE_SCORE_NIBBLER);
    printMap(this->_wallsPosition, this->_shapeWall);
    printMap(this->_foodsPosition, this->_shapeFood);
    printSnake();
}

/************************************************************************************/
/*                               SAVE TOP SCORE                                     */
/************************************************************************************/

std::vector<std::pair<std::string, int>> Nibbler::getTopScores(void)
{
    std::ifstream file(PATH_TO_SCORES);
    std::string a;
    int b;
    std::vector<std::pair<std::string, int>> topScores;
    std::pair<std::string, int> line;

    while (file >> a >> b) {
        line.first = a;
        line.second = b;
        topScores.push_back(line);
    }
    file.close();
    return (topScores);
}

void Nibbler::setTopScore(std::vector<std::pair<std::string, int>> topScores)
{
    std::ofstream file(PATH_TO_SCORES);
    int i = 0;

    if (file.is_open())
        for (std::pair<std::string, int> topScore : topScores) {
            file << topScore.first << " " << topScore.second << "\n";
            i++;
            if (i == NUMBER_SCORES_BY_FILE)
                break;
        }
    file.close();
}

bool Nibbler::sortBySec(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
    return (a.second > b.second);
}

bool Nibbler::isTopScore(void)
{
    std::vector<std::pair<std::string, int>> topScores = getTopScores();

    for (int i = 0; i < (int)topScores.size(); i++) {
        if (_score > topScores[i].second) {
            std::pair<std::string, int> myTopScore;
            myTopScore.first = this->_userName;
            myTopScore.second = this->_score;
            topScores.push_back(myTopScore);
            sort(topScores.begin(), topScores.end(), sortBySec);
            setTopScore(topScores);
            return (true);
        }
    }
    return (false);
}

/************************************************************************************/
/*                               END GAME MENU                                      */
/************************************************************************************/

void Nibbler::switchSelectionEndMenu(Shape *toSelect, Shape *toUnselect, int indexToSelect)
{
    (*toSelect).textColor = COLOR_SELECTED;
    (*toSelect).textSize = SIZE_SELECTED;
    (*toUnselect).textColor = COLOR_NOT_SELECTED;
    (*toUnselect).textSize = SIZE_NOT_SELECTED;
    this->_libGraphic->addShape((*toSelect));
    this->_libGraphic->addShape((*toUnselect));
    this->_selectedEndGame = indexToSelect;
}

void Nibbler::handleEventEndGame(int input)
{
    if (input ==IGraphics::LEFT && this->_selectedEndGame == 1)
        switchSelectionEndMenu(&this->_shapeReplay, &this->_shapeMenu, 0);
    else if (input == IGraphics::RIGHT && this->_selectedEndGame == 0)
        switchSelectionEndMenu(&this->_shapeMenu, &this->_shapeReplay, 1);
    else if (input == IGraphics::ACTION) {
        this->_selectedEndGame == 0 ? initGame() : (void)0;
        this->_inNibbler = this->_selectedEndGame == 1 ? false : true;
        this->_inEndMenu = false;
    } else if (input == IGraphics::PAUSE) {
        this->_inEndMenu = false;
        this->_inNibbler = false;
    }
}

void Nibbler::initEndMenu(void)
{
    setShape(this->_shapeTitleEnd, INDEX_SHAPE_TITLE_END_NIBBLER, X_TITLE_END, Y_TITLE_END, NO_PATH, TEXT_TITLE_END_NIBBLER, COLOR_TITLE, SIZE_TITLE);
    setShape(this->_shapeReplay, INDEX_SHAPE_REPLAY_NIBBLER, X_REPLAY, Y_REPLAY, NO_PATH, TEXT_REPLAY_NIBBLER, COLOR_SELECTED, SIZE_SELECTED);
    setShape(this->_shapeMenu, INDEX_SHAPE_GO_MENU_NIBBLER, X_GO_MENU, Y_GO_MENU, NO_PATH, TEXT_GO_MENU_NIBBLER, COLOR_NOT_SELECTED, SIZE_NOT_SELECTED);
    setShape(this->_shapeNibblerScore, INDEX_SHAPE_SCORE_NIBBLER, X_SCORE, Y_SCORE, NO_PATH, TEXT_SCORE_NIBBLER + std::to_string(this->_score), COLOR_SCORE, SIZE_SCORE);
    setShape(this->_shapeNewTopScore, INDEX_SHAPE_NEW_TOP_SCORE_NIBBLER, X_NEW_TOP_SCORE, Y_NEW_TOP_SCORE, NO_PATH, TEXT_NEW_TOP_SCORE, COLOR_SUBTITLE, SIZE_TITLE);
    this->_inEndMenu = true;
    this->_selectedEndGame = 0;
}

void Nibbler::endMenu(void)
{
    bool topScore = false;
    initEndMenu();
    if (isTopScore())
        topScore = true;
    while (this->_libGraphic->isRunning() && this->_inEndMenu) {
        this->_libGraphic->clearScreen();
        this->_libGraphic->drawShape(this->_shapeTitleEnd.id);
        this->_libGraphic->drawShape(this->_shapeReplay.id);
        this->_libGraphic->drawShape(this->_shapeMenu.id);
        this->_libGraphic->drawShape(this->_shapeNibblerScore.id);
        topScore  ? this->_libGraphic->drawShape(this->_shapeNewTopScore.id) : (void)0;
        handleEventEndGame(this->_libGraphic->getInput());
        this->_libGraphic->drawScreen();
    }
}

/************************************************************************************/
/*                                 CHECK OBSTACLES                                  */
/************************************************************************************/

void Nibbler::checkWalls(int x, int y)
{
    for (Position &pos : this->_wallsPosition)
        if (x == pos.x && y == pos.y)
            this->_gameStatus = LOSE;
}

bool Nibbler::isOtherObstacle(int x, int y)
{
    for (Position &pos : this->_wallsPosition)
        if (x == pos.x && y == pos.y)
            return (true);
    for (Position &pos : this->_foodsPosition)
        if (x == pos.x && y == pos.y)
            return (true);
    return (false);
}

int Nibbler::roundForMap(int number, int precision)
{
    return (((number + (precision / 2)) / precision ) * precision);
}

Position Nibbler::getNewFoodPositions(void)
{
    Position newPos = Position{0, 0};

    while (newPos.x < X_MAP_MIN || newPos.x > X_MAP_MAX || newPos.y < Y_MAP_MIN || newPos.y > Y_MAP_MAX || isOtherObstacle(newPos.x, newPos.y)) {
        newPos.x = roundForMap(rand() % ( X_MAP_MAX - X_MAP_MIN + 1 ) + X_MAP_MIN, WALL_SIZE);
        newPos.y = roundForMap(rand() % ( Y_MAP_MAX - Y_MAP_MIN + 1 ) + Y_MAP_MIN, WALL_SIZE);
    }
    return (newPos);
}

bool Nibbler::checkFoods(int x, int y)
{
    int i = 0;
    for (Position &pos : this->_foodsPosition) {
        if (x == pos.x && y == pos.y) {
            this->_score += 1;
            this->_shapeNibblerScore.message = TEXT_SCORE_NIBBLER + std::to_string(this->_score);
            this->_libGraphic->addShape(this->_shapeNibblerScore);
            this->_snake.size += 1;
            this->_saveSnakeSpeed = this->_snakeSpeed = this->_snakeSpeed <= SPEED_MIN ? SPEED_MIN : this->_snakeSpeed - FOOD_WIN_SPEED;
            this->_snake.snakePositions.push_back(this->_snake.snakePositions.back());
            this->_foodsPosition[i] = getNewFoodPositions();
            return (true);
        }
        i++;
    }
    return (false);
}

void Nibbler::checkBody(int x, int y)
{
    for (Position &pos : this->_snake.snakePositions)
        if (x == pos.x && y == pos.y)
            this->_gameStatus = LOSE;
}

bool Nibbler::checkObstacles(int x, int y)
{
    if (checkFoods(x, y))
        return (true);
    checkWalls(x, y);
    checkBody(x, y);
    return (true);
}

/************************************************************************************/
/*                                 HANDLE EVENTS                                    */
/************************************************************************************/

void Nibbler::handleEventGame(int input, loadGraph &loaderGraphic)
{
        (void)(loaderGraphic);

    switch (input) {
        case IGraphics::UP:
            if (this->_snake.direction != DIR_DOWN)
                checkObstacles(this->_snake.snakePositions[0].x, this->_snake.snakePositions[0].y - SNAKE_SIZE) ? switchHeadDirection(PATH_TO_UP_HEAD, DIR_UP) : (void)0;
            break;
        case IGraphics::DOWN:
            if (this->_snake.direction != DIR_UP)
                checkObstacles(this->_snake.snakePositions[0].x, this->_snake.snakePositions[0].y + SNAKE_SIZE) ? switchHeadDirection(PATH_TO_DOWN_HEAD, DIR_DOWN) : (void)0;
            break;
        case IGraphics::LEFT:
            if (this->_snake.direction != DIR_RIGHT)
                checkObstacles(this->_snake.snakePositions[0].x - SNAKE_SIZE, this->_snake.snakePositions[0].y) ? switchHeadDirection(PATH_TO_LEFT_HEAD, DIR_LEFT) : (void)0;
            break;
        case IGraphics::RIGHT:
            if (this->_snake.direction != DIR_LEFT)
                checkObstacles(this->_snake.snakePositions[0].x + SNAKE_SIZE, this->_snake.snakePositions[0].y) ? switchHeadDirection(PATH_TO_RIGHT_HEAD, DIR_RIGHT) : (void)0;
            break;
        case IGraphics::ACTION:
            this->_saveSnakeSpeed = this->_snakeSpeed;
            this->_snakeSpeed = SPEED_MIN;
            break;
        case IGraphics::PAUSE:
            this->_inNibbler = startPause();
            break;
        case IGraphics::PREV_GAME:
            this->_inNibbler = false;
            this->_changeGame = 1;
            break;
        case IGraphics::NEXT_GAME:
            this->_inNibbler = false;
            this->_changeGame = 2;
            break;
        case IGraphics::PREV_LIB:
            loaderGraphic.graphicLibUsed = loaderGraphic.graphicLibUsed - 1 >= 0 ? loaderGraphic.graphicLibUsed - 1 : (int)loaderGraphic.graphicsPaths.size() - 1;
            this->_libGraphic = loaderGraphic.loaderGraphic.loadLib(loaderGraphic.graphicsPaths[loaderGraphic.graphicLibUsed]);
            initGameShapes(false);
            break;
        case IGraphics::NEXT_LIB:
            loaderGraphic.graphicLibUsed = loaderGraphic.graphicLibUsed + 1 <= (int)loaderGraphic.graphicsPaths.size() - 1 ? loaderGraphic.graphicLibUsed + 1 : 0;
            this->_libGraphic = loaderGraphic.loaderGraphic.loadLib(loaderGraphic.graphicsPaths[loaderGraphic.graphicLibUsed]);
            initGameShapes(false);
            break;
        case IGraphics::RESTART_GAME:
            initGame();
            break;
        case IGraphics::MENU:
            this->_inNibbler = false;
            break;
        default:
            this->_snakeSpeed = this->_saveSnakeSpeed;
    }
}

/************************************************************************************/
/*                                 MOVE SNAKE                                       */
/************************************************************************************/

void Nibbler::moveHead(void)
{
    switch (this->_snake.direction) {
    case DIR_RIGHT:
        if (checkObstacles(this->_snake.snakePositions[0].x + SNAKE_SIZE, this->_snake.snakePositions[0].y))
            this->_snake.snakePositions[0].x += SNAKE_SIZE;
        break;
    case DIR_LEFT:
        if (checkObstacles(this->_snake.snakePositions[0].x - SNAKE_SIZE, this->_snake.snakePositions[0].y))
            this->_snake.snakePositions[0].x -= SNAKE_SIZE;
        break;
    case DIR_UP:
        if (checkObstacles(this->_snake.snakePositions[0].x, this->_snake.snakePositions[0].y - SNAKE_SIZE))
            this->_snake.snakePositions[0].y -= SNAKE_SIZE;
        break;
    case DIR_DOWN:
        if (checkObstacles(this->_snake.snakePositions[0].x, this->_snake.snakePositions[0].y + SNAKE_SIZE))
            this->_snake.snakePositions[0].y += SNAKE_SIZE;
        break;
    }
}

void Nibbler::moveBody(void)
{
    if (this->_snake.snakePositions[0].x != this->_savePos.x || this->_snake.snakePositions[0].y != this->_savePos.y) {
        for (int i = 1; i < this->_snake.size; i++) {
            this->_tmpPos = this->_snake.snakePositions[i];
            this->_snake.snakePositions[i] = this->_savePos;
            this->_savePos = this->_tmpPos;
        }
    }
}

void Nibbler::moveForwardSnake(void)
{
    this->_savePos = this->_snake.snakePositions[0];
    moveHead();
    moveBody();
    changeTailDirection();
}

/************************************************************************************/
/*                                  GAME CORE                                       */
/************************************************************************************/

void Nibbler::refresh(void)
{
    this->_instantTime = std::chrono::steady_clock::now();
    this->_timePasted = std::chrono::duration_cast<std::chrono::duration<double>>(this->_instantTime - this->_clockGame);
    if (this->_timePasted.count() >= this->_snakeSpeed) {
        this->_libGraphic->clearScreen();
        moveForwardSnake();
        printGame();
        this->_libGraphic->drawScreen();
        this->_clockGame = this->_instantTime;
    }
}

void Nibbler::runGame(IGraphics *libGraphic, loadGraph &loaderGraph, std::string userName)
{
    this->_libGraphic = libGraphic;
    this->_userName = userName;
    initGame();
    while (this->_libGraphic->isRunning() && this->_inNibbler && this->_gameStatus == GAMING) {
        handleEventGame(this->_libGraphic->getInput(), loaderGraph);
        refresh();
        if (this->_gameStatus != GAMING)
            endMenu();
    }
}
