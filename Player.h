#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state

    Player(GameMechs *thisGMRef);
    ~Player();

    objPosArrayList *getPlayerPos();
    void updatePlayerDir();
    void movePlayer();
    const char *getDirectionString() const;
    bool checkSelfCollision(const objPos &bodypart);
    bool checkFoodConsumption(const objPos &currentFood);
    void increasePlayerLength();

private:
    objPosArrayList *playerPosList;

    Food *food;
    enum Dir myDir;

    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;
};

#endif