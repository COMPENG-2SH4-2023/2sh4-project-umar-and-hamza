#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gameMechs;
Player *myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (!gameMechs->getExitFlagStatus())
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    gameMechs = new GameMechs(30, 15);
    myPlayer = new Player(gameMechs);
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        char userInput = MacUILib_getChar();
        gameMechs->setInput(userInput);
    }
}

void RunLogic(void)
{

    if (gameMechs->getInput() == ' ')
    {
        gameMechs->setExitTrue();
    }
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    gameMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i, j;
    objPos playerObjPos;
    myPlayer->getPlayerPos(playerObjPos);

    // Initialize Gameboard with boundaries
    for (i = 0; i < gameMechs->getBoardSizeY(); i++)
    {
        for (j = 0; j < gameMechs->getBoardSizeX(); j++)
        {
            if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0 || j == gameMechs->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if (i == playerObjPos.y && j == playerObjPos.x)
            {
                MacUILib_printf("%c", playerObjPos.getSymbol());
            }
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }
}
void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{

    delete gameMechs;
    delete myPlayer;
    MacUILib_clearScreen();

    MacUILib_uninit();
}
