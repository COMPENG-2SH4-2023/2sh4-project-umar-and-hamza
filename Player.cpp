#include "Player.h"
#include "MacUILib.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    int boardsizeX = mainGameMechsRef->getBoardSizeX();
    int boardsizeY = mainGameMechsRef->getBoardSizeY();

    playerPos.setObjPos(boardsizeX / 2, boardsizeY / 2, '*');
}

Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos array list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        playerPos.y--;
        break;
    case DOWN:
        playerPos.y++;
        break;
    case LEFT:
        playerPos.x--;
        break;
    case RIGHT:
        playerPos.x++;
        break;
    }

    // Reset player's position if it goes out of bounds horizontally
    if (playerPos.x < 1)
    {
        playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (playerPos.x >= mainGameMechsRef->getBoardSizeX() - 1)
    {
        playerPos.x = 1;
    }

    // Reset player's position if it goes out of bounds vertically
    if (playerPos.y < 1)
    {
        playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (playerPos.y >= mainGameMechsRef->getBoardSizeY() - 1)
    {
        playerPos.y = 1;
    }
}