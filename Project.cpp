#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gameMechs;
Player *myPlayer;
Food *food;
objPos current_player_loc;

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
    food = new Food();

    
    food-> generateFood(current_player_loc);
}

void GetInput(void)
{
    char userInput = gameMechs->getInput();
    gameMechs->setInput(userInput);

    
}

void RunLogic(void)
{

    char userInput = gameMechs->getInput();
   

    if (userInput == ' ')
    {
        gameMechs->setExitTrue();
    }
    else if(userInput == 'k')
    {
        food->generateFood(current_player_loc);
    }
   
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    gameMechs->clearInput();
    

}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i, j, k;
    objPosArrayList *PlayerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    objPos current_food;
    food->getFoodPos(current_food);
    bool drawn;

    // Initialize Gameboard with boundaries
    for (i = 0; i < gameMechs->getBoardSizeY(); i++)
    {
        for (j = 0; j < gameMechs->getBoardSizeX(); j++)
        {
            drawn = false;

            for (k = 0; k < PlayerBody->getSize(); k++)
            {
                PlayerBody->getElement(tempBody, k);
                if (tempBody.y == i && tempBody.x == j)
                {
                    MacUILib_printf("%c", tempBody.getSymbol());
                    drawn = true;
                    break;
                }
            }

            if (drawn)
                continue;

            if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0 || j == gameMechs->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if (i == current_food.y && j == current_food.x)
            {
                MacUILib_printf("%c", current_food.getSymbol());
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
