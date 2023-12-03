#include "GameMechs.h"
#include "MacUILib.h"
GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 20;
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY) // generating game mechanics (gameboard size, score, etc)
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

char GameMechs::getInput() 
{
    if (MacUILib_hasChar()) // check to see if input has been pressed
    {
        input = MacUILib_getChar(); // ccapturing input pressed
    }
    return input;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}
