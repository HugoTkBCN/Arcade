/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** cpp
*/

#include "Pacman.hpp"

/************************************************************************************/
/*                                   UTILS                                          */
/************************************************************************************/

int Pacman::isGameChanged(void)
{
    return (this->_changeGame);
}

IGraphics *Pacman::getLibGraphic(void)
{
    return (this->_libGraphic);
}

void Pacman::setShape(Shape &shape, int index, int x, int y, std::string path, std::string message, Color color, int size)
{
    shape = fillGameShape(index, x, y, path, message, color, size);
    this->_libGraphic->addShape(shape);
}

Shape Pacman::fillGameShape(int id, int x, int y, std::string filePath, std::string message, Color textColor, size_t textSize)
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

bool Pacman::startPause(void)
{
    PausePacman pause;
    int ret = pause.runPausePacman(this->_libGraphic);

    if (ret == PausePacman::RESTART)
        initGame(false);
    else if (ret == PausePacman::MENU)
        return (false);
    return (true);
}

void Pacman::switchHeadDirection(std::string pathToSprite, int direction)
{
    this->_pacman.shape.filePath = pathToSprite;
    this->_libGraphic->addShape(this->_pacman.shape);
    this->_pacman.direction = direction;
}

/************************************************************************************/
/*                                   INIT                                           */
/************************************************************************************/

void Pacman::getWallFoodsPositions(std::vector<std::string> map)
{
    int y = 0, x= 0;

    this->_wallsPosition.clear();
    this->_foodsPosition.clear();
    this->_powerPosition.clear();
    for (std::string &line : map) {
        x = 0;
        for (char &character : line) {
            if (character == '#')
                this->_wallsPosition.push_back(Position{X_WALL + x * WALL_SIZE, Y_WALL + y * WALL_SIZE});
            else if (character == '*')
                this->_foodsPosition.push_back(Position{X_WALL + x * FOOD_SIZE, Y_WALL + y * FOOD_SIZE});
            else if (character == '+')
                this->_powerPosition.push_back(Position{X_WALL + x * FOOD_SIZE, Y_WALL + y * FOOD_SIZE});
            x++;
        }
        y++;
    }
}

bool Pacman::getMap(std::string filePath)
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

void Pacman::initGameShapes(bool initPacman)
{
    setShape(this->_shapePacmanTitle, INDEX_SHAPE_TITLE_PACMAN, X_TITLE, Y_TITLE, NO_PATH, TEXT_TITLE_PACMAN, COLOR_TITLE, SIZE_TITLE);
    setShape(this->_shapePacmanScore, INDEX_SHAPE_SCORE_PACMAN, X_SCORE, Y_SCORE, NO_PATH, TEXT_SCORE_PACMAN + std::to_string(this->_score), COLOR_SCORE, SIZE_SCORE);
    setShape(this->_shapeWall, INDEX_SHAPE_WALL, X_WALL, Y_WALL, PATH_TO_WALL, WALL_CHAR, Color::BLUE, WALL_SIZE);
    initPacman ? setShape(this->_pacman.shape, INDEX_SHAPE_PACMAN_HEAD, X_HEAD, Y_HEAD, PATH_TO_RIGHT_HEAD(this->_indexSpritePacman), HEAD_CHAR, Color::YELLOW, PACMAN_SIZE) : void(0);
    setShape(this->_shapeFood, INDEX_SHAPE_FOOD, X_HEAD, X_HEAD, PATH_TO_FOOD, FOOD_CHAR, Color::GREEN, FOOD_SIZE);
    setShape(this->_shapePower, INDEX_SHAPE_POWER, X_HEAD, X_HEAD, PATH_TO_POWER, POWER_CHAR, Color::RED, POWER_SIZE);
    setShape(this->_shapeGate, INDEX_SHAPE_GATE, X_GATE, Y_UP_GATE, PATH_TO_GATE, WALL_CHAR, Color::BLUE, WALL_SIZE);
    setShape(this->_shapeHeart, INDEX_SHAPE_HEART, X_HEART, Y_HEART, PATH_TO_HEART, HEART_CHAR, HEART_COLOR, HEART_SIZE);
}

void Pacman::initPerson(Person &person, int x, int y)
{
    person.direction = DIR_RIGHT;
    person.positions = (Position{x, y});
    person.isAlive = true;
}

void Pacman::initGhost(void)
{
    Person ghost;

    this->_ghost.clear();
    for (int i = 0; i < NUMBER_GHOST; i++) {
        initPerson(ghost, X_GHOST + (i * GHOST_SIZE), Y_GHOST);
        setShape(ghost.shape, INDEX_SHAPE_GHOST + i, ghost.positions.x, ghost.positions.y, PATH_TO_GHOST(i + 1, this->_indexSpriteGhost), "F", Color::RED, GHOST_SIZE);
        this->_ghost.push_back(ghost);
    }
}

void Pacman::initGame(bool win)
{
    this->_score = win ? this->_score : 0;
    this->_pacmanHearts = win ? this->_pacmanHearts : INIT_LIFE;
    this->_inPacman = true;
    this->_gameStatus = GAMING;
    this->_gameSpeed = win ? this->_gameSpeed / 2 : INIT_SPEED;
    this->_ghostSpeed = win ? this->_ghostSpeed / 2 : INIT_GHOST_SPEED;
    this->_gotPower = false;
    this->_clockPower = 0;
    this->_indexSpritePacman = 1;
    this->_indexSpriteGhost = 1;
    this->_indexSpriteDeadPacman = 1;
    this->_printGate = true;
    this->_ghostHunting = true;
    initPerson(this->_pacman, X_HEAD, Y_HEAD);
    initGhost();
    srand(time(NULL));
    if (!getMap(PATH_TO_MAPS+std::to_string(rand() % NUMBER_MAP + 1) +".txt"))
        throw Error("No such file");
    initGameShapes(true);
    srand(time(NULL));
    this->_clockGame = std::chrono::steady_clock::now();
    this->_clockGhost = std::chrono::steady_clock::now();
    this->_clockStart = std::clock();
    this->_gameStatus = GAMING;
    this->_changeGame = 0;
}

/************************************************************************************/
/*                                   PRINT                                          */
/************************************************************************************/

void Pacman::printAtPosition(Shape &shape, int x, int y)
{
    shape.x = x;
    shape.y = y;
    this->_libGraphic->addShape(shape);
    this->_libGraphic->drawShape(shape.id);
}

void Pacman::printMap(std::vector<Position> positions, Shape &shape)
{
    for (Position &pos : positions)
        printAtPosition(shape, pos.x, pos.y);
}

void Pacman::moveEyes(Person &ghost)
{
    if (ghost.positions.x != X_GHOST)
        ghost.positions.x = X_GHOST - ghost.positions.x > 0 ? ghost.positions.x + GHOST_SIZE : ghost.positions.x - GHOST_SIZE;
    else if (ghost.positions.y != Y_GHOST)
        ghost.positions.y = Y_GHOST - ghost.positions.y > 0 ? ghost.positions.y + GHOST_SIZE : ghost.positions.y - GHOST_SIZE;
    ghost.shape.x = ghost.positions.x;
    ghost.shape.y = ghost.positions.y;
    ghost.shape.filePath = PATH_TO_EYES(this->_indexSpriteGhost == 1 ? 1 : int(this->_indexSpriteGhost / 2));
    ghost.shape.textColor = Color::WHITE;
}

void Pacman::printGhost(void)
{
    if (this->_indexSpriteGhost >= NUMBER_SPRITE_GHOST)
        this->_indexSpriteGhost = 1;
    else
        this->_indexSpriteGhost++;
    for (int i = 0; i < NUMBER_GHOST; i++) {
        if (this->_ghost[i].isAlive) {
            this->_ghost[i].shape.filePath = this->_ghostHunting ?
                PATH_TO_GHOST(i + 1, this->_indexSpriteGhost) :
                PATH_TO_GHOST_HUNTED(this->_indexSpriteGhost % 2 + 1, this->_indexSpriteGhost);
            this->_ghost[i].shape.textColor = this->_ghostHunting ? Color::RED : Color::BLUE;
        } else {
            moveEyes(this->_ghost[i]);
            if ((std::clock() - this->_ghost[i].clockDead) / CLOCKS_PER_SEC >= TIME_DEAD_GHOST &&
                this->_ghost[i].positions.x == X_GHOST && this->_ghost[i].positions.y == Y_GHOST) {
                this->_ghost[i].isAlive = true;
            }
        }
        this->_libGraphic->addShape(this->_ghost[i].shape);
        this->_libGraphic->drawShape(this->_ghost[i].shape.id);
    }
}

void Pacman::printPacman(void)
{
    if (this->_indexSpritePacman >= NUMBER_SPRITE_PACMAN)
        this->_indexSpritePacman = 1;
    else
        this->_indexSpritePacman++;
    if (this->_pacman.isAlive) {
        this->_pacman.shape.filePath =
            this->_pacman.direction == DIR_UP ? PATH_TO_UP_HEAD(this->_indexSpritePacman) :
            this->_pacman.direction == DIR_DOWN ? PATH_TO_DOWN_HEAD(this->_indexSpritePacman) :
            this->_pacman.direction == DIR_LEFT ? PATH_TO_LEFT_HEAD(this->_indexSpritePacman) :
            this->_pacman.direction == DIR_RIGHT ? PATH_TO_RIGHT_HEAD(this->_indexSpritePacman) :
            this->_pacman.shape.filePath;
        this->_pacman.shape.textColor = Color::YELLOW;
    } else {
        this->_pacman.shape.filePath = PATH_TO_DEAD_PACMAN(this->_indexSpriteDeadPacman);
        this->_pacman.shape.textColor = Color::WHITE;
        this->_indexSpriteDeadPacman += this->_indexSpriteDeadPacman < NUMBER_DEAD_SPRITES ? 1 : 0;
        if ((std::clock() - this->_pacman.clockDead) / CLOCKS_PER_SEC >= TIME_DEAD_PACMAN) {
            this->_pacman.isAlive = true;
            this->_pacman.positions = Position{X_HEAD, Y_HEAD};
            this->_pacman.shape.x = X_HEAD;
            this->_pacman.shape.y = Y_HEAD;
        }
    }
    this->_libGraphic->addShape(this->_pacman.shape);
    this->_libGraphic->drawShape(this->_pacman.shape.id);
}

bool Pacman::ghostInCell(void)
{
    for (Person &ghost : this->_ghost) {
        if ((ghost.positions.x >= X_CELL_MIN && ghost.positions.x <= X_CELL_MAX) && (ghost.positions.y >= Y_CELL_MIN && ghost.positions.y <= Y_CELL_MAX))
            return (true);
    }
    return (false);
}

void Pacman::printGates(void)
{
    if (!ghostInCell() || this->_printGate) {
        printAtPosition(this->_shapeGate, this->_shapeGate.x, Y_UP_GATE);
        printAtPosition(this->_shapeGate, this->_shapeGate.x, Y_DOWN_GATE);
    }
}

void Pacman::printHearts(void)
{
    for (int i = 0; i < this->_pacmanHearts; i++)
        printAtPosition(this->_shapeHeart, X_HEART + (i * HEART_SIZE), this->_shapeHeart.y);
}

void Pacman::printGame(void)
{
    this->_libGraphic->drawShape(INDEX_SHAPE_TITLE_PACMAN);
    this->_libGraphic->drawShape(INDEX_SHAPE_SCORE_PACMAN);
    printMap(this->_wallsPosition, this->_shapeWall);
    printMap(this->_foodsPosition, this->_shapeFood);
    printMap(this->_powerPosition, this->_shapePower);
    printGhost();
    printPacman();
    printGates();
    printHearts();
}

/************************************************************************************/
/*                               SAVE TOP SCORE                                     */
/************************************************************************************/

std::vector<std::pair<std::string, int>> Pacman::getTopScores(void)
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

void Pacman::setTopScore(std::vector<std::pair<std::string, int>> topScores)
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

bool Pacman::sortBySec(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
    return (a.second > b.second);
}

bool Pacman::isTopScore(void)
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

void Pacman::switchSelectionEndMenu(Shape *toSelect, Shape *toUnselect, int indexToSelect)
{
    (*toSelect).textColor = COLOR_SELECTED;
    (*toSelect).textSize = SIZE_SELECTED;
    (*toUnselect).textColor = COLOR_NOT_SELECTED;
    (*toUnselect).textSize = SIZE_NOT_SELECTED;
    this->_libGraphic->addShape((*toSelect));
    this->_libGraphic->addShape((*toUnselect));
    this->_selectedEndGame = indexToSelect;
}

void Pacman::handleEventEndGame(int input)
{
    if (input ==IGraphics::LEFT && this->_selectedEndGame == 1)
        switchSelectionEndMenu(&this->_shapeReplay, &this->_shapeMenu, 0);
    else if (input == IGraphics::RIGHT && this->_selectedEndGame == 0)
        switchSelectionEndMenu(&this->_shapeMenu, &this->_shapeReplay, 1);
    else if (input == IGraphics::ACTION) {
        this->_selectedEndGame == 0 ? initGame(false) : (void)0;
        this->_inPacman = this->_selectedEndGame == 1 ? false : true;
        this->_inEndMenu = false;
    } else if (input == IGraphics::PAUSE) {
        this->_inEndMenu = false;
        this->_inPacman = false;
    }
}

Person &Pacman::getDeadGhost(int x, int y)
{
    for (Person &ghost : this->_ghost) {
        if (x == ghost.positions.x && y == ghost.positions.y)
            return (ghost);
    }
    return (this->_ghost[0]);
}

void Pacman::checkLose(void)
{
    if (!checkGhost(this->_pacman.positions.x, this->_pacman.positions.y) && this->_pacman.isAlive) {
        this->_pacmanHearts -= this->_gotPower ? 0 : 1;
        if (this->_gotPower) {
            Person &ghost = getDeadGhost(this->_pacman.positions.x, this->_pacman.positions.y);
            ghost.isAlive = false;
            ghost.clockDead = std::clock();
        } else {
            this->_pacman.isAlive = false;
            this->_indexSpriteDeadPacman = 1;
            this->_pacman.clockDead = std::clock();
        }
    }
    if (this->_pacmanHearts <= 0)
        this->_gameStatus = LOSE;
}

void Pacman::checkWin(void)
{
    if (this->_foodsPosition.size() == 0) {
        this->_gameStatus = WIN;
        initGame(true);
    }
}

void Pacman::initEndMenu(void)
{
    setShape(this->_shapeTitleEnd, INDEX_SHAPE_TITLE_END_PACMAN, X_TITLE_END, Y_TITLE_END, NO_PATH, TEXT_TITLE_END_PACMAN, COLOR_TITLE, SIZE_TITLE);
    setShape(this->_shapeReplay, INDEX_SHAPE_REPLAY_PACMAN, X_REPLAY, Y_REPLAY, NO_PATH, TEXT_REPLAY_PACMAN, COLOR_SELECTED, SIZE_SELECTED);
    setShape(this->_shapeMenu, INDEX_SHAPE_GO_MENU_PACMAN, X_GO_MENU, Y_GO_MENU, NO_PATH, TEXT_GO_MENU_PACMAN, COLOR_NOT_SELECTED, SIZE_NOT_SELECTED);
    setShape(this->_shapePacmanScore, INDEX_SHAPE_SCORE_PACMAN, X_SCORE, Y_SCORE, NO_PATH, TEXT_SCORE_PACMAN + std::to_string(this->_score), COLOR_SCORE, SIZE_SCORE);
    setShape(this->_shapeNewTopScore, INDEX_SHAPE_NEW_TOP_SCORE_PACMAN, X_NEW_TOP_SCORE, Y_NEW_TOP_SCORE, NO_PATH, TEXT_NEW_TOP_SCORE, COLOR_SUBTITLE, SIZE_TITLE);
    this->_inEndMenu = true;
    this->_selectedEndGame = 0;
}

void Pacman::endMenu(void)
{
    bool topScore = false;
    initEndMenu();
    if (isTopScore()) {
        topScore = true;
    }
    while (this->_libGraphic->isRunning() && this->_inEndMenu) {
        this->_libGraphic->clearScreen();
        this->_libGraphic->drawShape(this->_shapeTitleEnd.id);
        this->_libGraphic->drawShape(this->_shapeReplay.id);
        this->_libGraphic->drawShape(this->_shapeMenu.id);
        this->_libGraphic->drawShape(this->_shapePacmanScore.id);
        topScore  ? this->_libGraphic->drawShape(this->_shapeNewTopScore.id) : (void)0;
        handleEventEndGame(this->_libGraphic->getInput());
        this->_libGraphic->drawScreen();
    }
}

/************************************************************************************/
/*                                 CHECK OBSTACLES                                  */
/************************************************************************************/

void Pacman::checkWalls(Person &person, int x, int y, bool move)
{
    for (Position &pos : this->_wallsPosition)
        if (x == pos.x && y == pos.y) {
            return;
        }
    if (move) {
        x = (x <= X_WALL) ?  X_WALL + (WALL_SIZE * (WIDTH_MAP - 2)) :
            (x >= X_WALL + (WALL_SIZE * (WIDTH_MAP - 2))) ? X_WALL :
            x;
        y = (y <= Y_WALL) ? Y_WALL + (WALL_SIZE * (HEIGHT_MAP - 1)) :
            (y >= Y_WALL + (WALL_SIZE * (HEIGHT_MAP - 1))) ? Y_WALL :
            y;
        person.positions = (Position){x, y};
        person.shape.x = person.positions.x;
        person.shape.y = person.positions.y;
        this->_libGraphic->addShape(person.shape);
    }
}

void Pacman::checkFoods(int x, int y)
{
    int i = 0;
    for (Position &pos : this->_foodsPosition) {
        if (x == pos.x && y == pos.y) {
            this->_score += 1;
            this->_shapePacmanScore.message = TEXT_SCORE_PACMAN + std::to_string(this->_score);
            this->_libGraphic->addShape(this->_shapePacmanScore);
            this->_foodsPosition.erase(this->_foodsPosition.begin() + i);
            return;
        }
        i++;
    }
}

void Pacman::checkPower(int x, int y)
{
    int i = 0;
    for (Position &pos : this->_powerPosition) {
        if (x == pos.x && y == pos.y) {
            this->_gotPower = true;
            this->_clockPower = std::clock();
            this->_ghostHunting = false;
            this->_ghostSpeed *= 2;
            this->_score += 100;
            this->_powerPosition.erase(this->_powerPosition.begin() + i);
            return;
        }
        i++;
    }
}

bool Pacman::checkObstacles(int x, int y, bool move)
{
    checkFoods(x, y);
    (x != X_GATE && y != Y_UP_GATE && y != Y_DOWN_GATE) ||
    (x == X_GATE && y != Y_UP_GATE && y != Y_DOWN_GATE) ||
    (y == Y_UP_GATE && x != X_GATE) ||
    (y == Y_DOWN_GATE && x != X_GATE) ?
    checkWalls(this->_pacman, x, y, move) : void(0);
    checkPower(x, y);
    return (true);
}

/************************************************************************************/
/*                                 HANDLE EVENTS                                    */
/************************************************************************************/

void Pacman::handleEventGame(int input, loadGraph &loaderGraphic)
{
    (void)(loaderGraphic);
    switch (input) {
    case IGraphics::UP:
        this->_pacman.isAlive ? checkObstacles(this->_pacman.positions.x, this->_pacman.positions.y - PACMAN_SIZE, false) ? switchHeadDirection(PATH_TO_UP_HEAD(this->_indexSpritePacman), DIR_UP) : (void)0 : (void)0;
        break;
    case IGraphics::DOWN:
        this->_pacman.isAlive ? checkObstacles(this->_pacman.positions.x, this->_pacman.positions.y + PACMAN_SIZE,false) ? switchHeadDirection(PATH_TO_DOWN_HEAD(this->_indexSpritePacman), DIR_DOWN) : (void)0 : (void)0;
        break;
    case IGraphics::LEFT:
        this->_pacman.isAlive ? checkObstacles(this->_pacman.positions.x - PACMAN_SIZE, this->_pacman.positions.y, false) ? switchHeadDirection(PATH_TO_LEFT_HEAD(this->_indexSpritePacman), DIR_LEFT) : (void)0 : (void)0;
        break;
    case IGraphics::RIGHT:
        this->_pacman.isAlive ? checkObstacles(this->_pacman.positions.x + PACMAN_SIZE, this->_pacman.positions.y, false) ? switchHeadDirection(PATH_TO_RIGHT_HEAD(this->_indexSpritePacman), DIR_RIGHT) : (void)0 : (void)0;
        break;
    case IGraphics::PAUSE:
        this->_inPacman = startPause();
        break;
    case IGraphics::PREV_GAME:
        this->_inPacman = false;
        this->_changeGame = 1;
        break;
    case IGraphics::NEXT_GAME:
        this->_inPacman = false;
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
        initGame(false);
        break;
    case IGraphics::MENU:
        this->_inPacman = false;
        break;
    default:
        break;
    }
}

/************************************************************************************/
/*                                 MOVE GHOST                                       */
/************************************************************************************/

bool Pacman::checkGhost(int x, int y)
{
    for (Person ghost : this->_ghost) {
        if (x == ghost.positions.x && y == ghost.positions.y)
            return (false);
    }
    return (true);
}

void Pacman::moveGhost(int x, int y, Person &ghost)
{
    if (((x != X_GATE && y != Y_UP_GATE && y != Y_DOWN_GATE) ||
         (x == X_GATE && y != Y_UP_GATE && y != Y_DOWN_GATE) ||
         (y == Y_UP_GATE && x != X_GATE) ||
         (y == Y_DOWN_GATE && x != X_GATE)) || ghostInCell())
        checkWalls(ghost, x, y, true);
}

void Pacman::getDirectionGhost(Person &ghost, int direction)
{
    switch (direction) {
    case DIR_UP:
        if (checkGhost(ghost.positions.x, ghost.positions.y - GHOST_SIZE))
            moveGhost(ghost.positions.x, ghost.positions.y - GHOST_SIZE, ghost);
        break;
    case DIR_DOWN:
        if (checkGhost(ghost.positions.x, ghost.positions.y + GHOST_SIZE))
            moveGhost(ghost.positions.x, ghost.positions.y + GHOST_SIZE, ghost);
        break;
    case DIR_LEFT:
        if (checkGhost(ghost.positions.x - GHOST_SIZE, ghost.positions.y))
            moveGhost(ghost.positions.x - GHOST_SIZE, ghost.positions.y, ghost);
        break;
    case DIR_RIGHT:
        if (checkGhost(ghost.positions.x + GHOST_SIZE, ghost.positions.y))
            moveGhost(ghost.positions.x + GHOST_SIZE, ghost.positions.y, ghost);
        break;
    default:
        break;
    }
}

bool isLower(int arg1, int arg2) { return arg1 < arg2; }
bool isGreater(int arg1, int arg2) { return arg1 > arg2; }

void Pacman::moveGhosts(void)
{
    int diffX;
    int diffY;
    bool(*condition[2])(int, int);
    condition[0] = this->_ghostHunting ? &isLower : &isGreater;
    condition[1] = this->_ghostHunting ? &isGreater : &isLower;
    for (Person &ghost : this->_ghost) {
        diffX = ghost.positions.x - this->_pacman.positions.x;
        diffY = ghost.positions.y - this->_pacman.positions.y;
        for (int i = 0; (diffX == ghost.positions.x - this->_pacman.positions.x) && (diffY == ghost.positions.y - this->_pacman.positions.y) && i < 2; i++) {
            if (condition[i == 0 ? 1 : 0](diffY, 0)) //pacman en haut
                getDirectionGhost(ghost, DIR_UP);
            else if (condition[i == 0 ? 0 : 1](diffY, 0))
                getDirectionGhost(ghost, DIR_DOWN);
            if ((diffX == ghost.positions.x - this->_pacman.positions.x) && (diffY == ghost.positions.y - this->_pacman.positions.y)) {
                if (condition[i == 0 ? 1 : 0](diffX, 0)) //pacman a gauche
                    getDirectionGhost(ghost, DIR_LEFT);
                else if (condition[i == 0 ? 0 : 1](diffX, 0))
                    getDirectionGhost(ghost, DIR_RIGHT);
            }
        }
    }
}

/************************************************************************************/
/*                                  GAME CORE                                       */
/************************************************************************************/

void Pacman::refresh(void)
{
    this->_libGraphic->clearScreen();
    if (this->_gotPower)
        if ((std::clock() - this->_clockPower) / CLOCKS_PER_SEC >= 10) {
            this->_ghostHunting = true;
            this->_ghostSpeed = this->_ghostSpeed / 2;
            this->_gotPower = false;
        }
    this->_instantTime = std::chrono::steady_clock::now();
    if ((std::clock() - this->_clockStart) / CLOCKS_PER_SEC >= 10) {
        this->_timePasted = std::chrono::duration_cast<std::chrono::duration<double>>(this->_instantTime - this->_clockGhost);
        if (this->_timePasted.count() >= this->_ghostSpeed) {
            moveGhosts();
            this->_clockGhost = this->_instantTime;
        }
        this->_printGate = false;
    }
    this->_timePasted = std::chrono::duration_cast<std::chrono::duration<double>>(this->_instantTime - this->_clockGame);
    if (this->_timePasted.count() >= this->_gameSpeed) {
        int x = this->_pacman.direction == DIR_LEFT ?
            this->_pacman.positions.x - PACMAN_SIZE : this->_pacman.direction == DIR_RIGHT ?
            this->_pacman.positions.x + PACMAN_SIZE : this->_pacman.positions.x;
        int y = this->_pacman.direction == DIR_UP ?
            this->_pacman.positions.y - PACMAN_SIZE : this->_pacman.direction == DIR_DOWN ?
            this->_pacman.positions.y + PACMAN_SIZE : this->_pacman.positions.y;
        this->_pacman.isAlive ? checkObstacles(x, y, true) : (bool)(0);
        this->_clockGame = this->_instantTime;
    }
    printGame();
    this->_libGraphic->drawScreen();
}

void Pacman::runGame(IGraphics *libGraphics, loadGraph &loaderGraph, std::string userName)
{
    (void)(loaderGraph);
    this->_libGraphic = libGraphics;
    this->_userName = userName;
    initGame(false);
    while (this->_libGraphic->isRunning() && this->_inPacman && this->_gameStatus != LOSE) {
        handleEventGame(this->_libGraphic->getInput(), loaderGraph);
        refresh();
        checkWin();
        checkLose();
        if (this->_gameStatus == LOSE)
            endMenu();
    }
}
