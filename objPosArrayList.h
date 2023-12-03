#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
private:
    objPos *aList;     // creates a object that is used to create an arrayList.
    int listSize;      // Size of objectArrayList (snake)
    int arrayCapacity; // Maximum capacity that the objectArrayList (snake) can reach.
    void checkIndexValidity();

public:
    objPosArrayList();
    ~objPosArrayList();

    // Getter methods
    int getSize();
    void getHeadElement(objPos &returnPos);
    void getTailElement(objPos &returnPos);
    void getElement(objPos &returnPos, int index);

    // Setter methods
    void insertHead(objPos thisPos);
    void insertTail(objPos thisPos);
    void removeHead();
    void removeTail();
};

#endif