#include "Food.h"
#include <cstdlib> // provides srand
#include <time.h>   // provides time

Food::Food()
{
    foodPos.setObjPos(-1,-1,'o');
}

Food::~Food()
{
    
}

void Food::generateFood(objPosArrayList& playerPosList) // generating position for food on board
{
    int xfood;
    int yfood;
    srand(time(NULL));

    // Keep generating new positions until a valid position is found
    while (true)
    {
        xfood = rand() % (30 - 2) + 1;
        yfood = rand() % (15 - 2) + 1;
        foodPos.setObjPos(xfood, yfood, 'o');

        bool overlap = false;
        //looping through player to continuously check if food is generated on top of player
        for (int i = 0; i < playerPosList.getSize(); i++)
        {
            objPos playerPos;
            playerPosList.getElement(playerPos, i);
            if (foodPos.x == playerPos.x && foodPos.y == playerPos.y)
            {
                overlap = true;
                break;
            }
        }

        // If no overlap, break out of the loop
        if (!overlap)
        {
            break;
        }
    }

    
}


void Food::getFoodPos(objPos &returnPos) // returning food position so it can be used in collision with head logic
{
    returnPos = foodPos;
}