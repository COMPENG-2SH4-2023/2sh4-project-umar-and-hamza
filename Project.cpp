#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gameMechs;        // create a GameMechanics object on the heap.
Player *myPlayer;            // create a Player object on the heap.
Food *food;                  // create a Food object on the heap.
objPosArrayList *PlayerBody; // create an ObjPosArrayList on the heap.

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (!gameMechs->getExitFlagStatus()) // Game will continue as long as exit flag is false.
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
    gameMechs = new GameMechs(30, 15);               // initializes a Gameboard with dimensions 30x15.
    myPlayer = new Player(gameMechs);                // initializes myPlayer and passes the gameMechs object as an argument so myPlayer can access it's features.
    PlayerBody = myPlayer->getPlayerPos();           // Stores the position of the player.
    food = new Food();                               // initializes the food object.
    food->generateFood(*(myPlayer->getPlayerPos())); // Generates food position that will be drawn to the gameboard.
}

void GetInput(void)
{
    // Reads user input and stores it.
    char userInput = gameMechs->getInput();
    gameMechs->setInput(userInput);
}

void RunLogic(void)
{

    char userInput = gameMechs->getInput(); // Accesses user input from the Game Mechanics class.
    objPos currentFood;
    food->getFoodPos(currentFood); // Accesses food position from Food class.

    if (userInput == char(27)) // If user input is "esc" key. ExitFlag is set to true and Game quits.
    {
        gameMechs->setExitTrue();
    }

    else if (myPlayer->checkFoodConsumption(currentFood)) // if player eats food, player length is increased and new food is generated on the gameboard.
    {
        myPlayer->increasePlayerLength();
        food->generateFood(*(myPlayer->getPlayerPos()));
    }
    // Player position and direction is updated
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    gameMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i, j, k;
    objPos tempBody;                // object created to store body position temporarily
    objPos current_food;            // object created to store current food.
    food->getFoodPos(current_food); // Accesses the position of current food.
    bool drawn;                     // Flag variable
    const char *directionString;    // stores player direction

    MacUILib_printf("use 'w' 'a' 's' 'd' to move. Press esc to quit.\n\n");

    // Initialize Gameboard with boundaries
    for (i = 0; i < gameMechs->getBoardSizeY(); i++)
    {
        for (j = 0; j < gameMechs->getBoardSizeX(); j++)
        {
            drawn = false; // Snake body is not drawn yet

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

            if (drawn) // if snake body is drawn, continue
                continue;

            if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0 || j == gameMechs->getBoardSizeX() - 1) // draw boundary
            {
                MacUILib_printf("%c", '#');
            }
            else if (i == current_food.y && j == current_food.x) // draw food symbol at appropriate positon
            {
                MacUILib_printf("%c", current_food.getSymbol());
            }
            else
            {
                MacUILib_printf("%c", ' '); // draw empty spaces on the gameboard
            }
        }
        MacUILib_printf("\n");
    }

    // outputs score, board size, Player direction, player coordinates and food coordinates.
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
        MacUILib_printf("%s %d", "You Died! Final score:", gameMechs->getScore()); // prints "You died" and Final score when the Lose flag is set to true.

    else if (gameMechs->getExitFlagStatus())
        MacUILib_printf("You Quit! Final score: %d", gameMechs->getScore()); // prints a successful quit message and final score when the exit flag is true

    // deallocates memory occupied by the objects on the heap.
    delete gameMechs;
    delete myPlayer;
    delete food;

    MacUILib_uninit();
}
