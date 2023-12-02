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

    food->generateFood(*(myPlayer->getPlayerPos()));
}

void GetInput(void)
{
    char userInput = gameMechs->getInput();
    gameMechs->setInput(userInput);
}

void RunLogic(void)
{

    char userInput = gameMechs->getInput();
    objPos currentFood;
    food->getFoodPos(currentFood);

    if (userInput == char(27))
    {
        gameMechs->setExitTrue();
    }
    else if (userInput == 'k')
    {
        food->generateFood(*(myPlayer->getPlayerPos()));
    }

    else if (myPlayer->checkFoodConsumption(currentFood))
    {
        myPlayer->increasePlayerLength();
        food->generateFood(*(myPlayer->getPlayerPos()));
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
    const char *directionString;

    MacUILib_printf("use 'w' 'a' 's' 'd' to move. Press esc to quit\n\n");

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
                    directionString = myPlayer->getDirectionString();
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
    MacUILib_printf("\nScore = %d\nBoard Size: <%d,%d>\nPlayer Direction: %s\nPlayer position: <%d,%d>\nFood Coordinates: <%d,%d>\n", gameMechs->getScore(), gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY(), directionString, tempBody.x, tempBody.y, current_food.x, current_food.y);
}
void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    if (gameMechs->getLoseFlagStatus())
        MacUILib_printf("%s %d", "You Died! Final score:", gameMechs->getScore());

    else if (gameMechs->getExitFlagStatus())
        MacUILib_printf("You Quit!"); // print a successful quit message if the exit flag is true

    delete gameMechs;
    delete myPlayer;
    delete food;

    MacUILib_uninit();
}
