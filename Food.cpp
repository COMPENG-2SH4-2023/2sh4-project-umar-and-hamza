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

void Food::generateFood(objPos blockOff)
{
    int xfood;
    int yfood;
    srand(time(NULL));
    while(true)
    {
        xfood = rand() % (30 -2) +1;
        yfood = rand() % (15 -2) +1;
        foodPos.setObjPos(xfood,yfood,'o');
        if (!foodPos.isPosEqual(&blockOff))
        {
            break;
        }
    }

    
}


void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}