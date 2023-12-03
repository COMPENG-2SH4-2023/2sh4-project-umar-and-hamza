#include "Player.h"
#include "MacUILib.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;

    myDir = STOP;

    // Accesses Gameboard size and stores it.
    int boardsizeX = mainGameMechsRef->getBoardSizeX();
    int boardsizeY = mainGameMechsRef->getBoardSizeY();

    objPos tempPos;
    tempPos.setObjPos(boardsizeX / 2, boardsizeY / 2, '*'); // sets player position at the centre of the gameboard.

    playerPosList = new objPosArrayList();
    food = new Food();
    playerPosList->insertHead(tempPos); // Snake head is created at the start of the game.
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
    playerPosList->getHeadElement(currentHead); // Accesses the position of the snake's head.

    // PPA3 Finite State Machine logic
    // Border Wraparound Logic
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

    // if snake eats itself. Set Exit and Lost flag to true. This Outputs a message telling user they died.
    if (checkSelfCollision(currentHead))
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
        return;
    }

    // Snake's head is inserted at the new position and tail is removed. This gives the illusion that the snake is moving smoothly across the gameboard.
    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}
bool Player::checkSelfCollision(const objPos &head)
{
    // iterate through the coordinates of every bodypart to check whether the head collides with any part.
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos snakeBody;
        playerPosList->getElement(snakeBody, i);

        if (head.x == snakeBody.x && head.y == snakeBody.y) // if head collides with another body part. return true.
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
const char *Player::getDirectionString() const
{
    const char *directionStrings[] = {"UP", "DOWN", "LEFT", "RIGHT", "STOP"};

    if (myDir >= UP && myDir <= STOP)
    {
        return directionStrings[myDir];
    }

    return "UNKNOWN";
}