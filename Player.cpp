#include "Player.h"
#include "MacUILib.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;

    myDir = STOP;

    // more actions to be included

    int boardsizeX = mainGameMechsRef->getBoardSizeX();
    int boardsizeY = mainGameMechsRef->getBoardSizeY();

    objPos tempPos;
    tempPos.setObjPos(boardsizeX / 2, boardsizeY / 2, '*');

    playerPosList = new objPosArrayList();
    food = new Food();
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
    delete food;
}

objPosArrayList *Player::getPlayerPos()
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    bool exitFlag = mainGameMechsRef->getExitFlagStatus();
    // PPA3 input processing logic

    if (input != 0) // if not null character
    {
        switch (input)
        {
        case ' ': // exit
            exitFlag = 1;
            break;
        case 'w': // move up
            if (myDir != DOWN)
                myDir = UP;
            break;
        case 's': // move down
            if (myDir != UP)
                myDir = DOWN;
            break;
        case 'a': // move left
            if (myDir != RIGHT)
                myDir = LEFT;
            break;
        case 'd': // move right
            if (myDir != LEFT)
                myDir = RIGHT;
            break;
        }
        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        currentHead.y--;
        if (currentHead.y <= 0)
            currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
        break;
    case DOWN:
        currentHead.y++;
        if (currentHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
            currentHead.y = 1;
        break;
    case LEFT:
        currentHead.x--;
        if (currentHead.x <= 0)
            currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
        break;
    case RIGHT:
        currentHead.x++;
        if (currentHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
            currentHead.x = 1;
        break;
    case STOP:
    default:
        break;
    }

    if (checkSelfCollision(currentHead))
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
        return;
    }



    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}
bool Player::checkSelfCollision(const objPos &head)
{

    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos snakeBody;
        playerPosList->getElement(snakeBody, i);

        if (head.x == snakeBody.x && head.y == snakeBody.y)
        {
            return true;
        }
    }
    return false;
}

bool Player::checkFoodConsumption(const objPos &currentFood)
{
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    // Get the current food position
    

    // Check if the head overlaps with the food position
    return (currentHead.x == currentFood.x && currentHead.y == currentFood.y);
}

void Player::increasePlayerLength()
{
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    playerPosList->insertHead(currentHead);

    food->generateFood(*playerPosList);

    mainGameMechsRef->incrementScore();
}