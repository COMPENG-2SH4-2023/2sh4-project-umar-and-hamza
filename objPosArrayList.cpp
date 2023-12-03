#include "objPosArrayList.h"
#include <stdexcept>
#include <stdlib.h>

using namespace std;
// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 200 elements on the array
    listSize = 0;                      // 0 elements on startup
    arrayCapacity = ARRAY_MAX_CAP;     // Max number of elements allowed
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // deletes all instances of aList when destructor is called.
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize < arrayCapacity) // if size of objectlist (snake) hasn't reached max capacity. Keep inserting at the head.
    {
        for (int i = listSize; i > 0; i--)
        {
            aList[i].setObjPos(aList[i - 1]);
        }
        aList[0].setObjPos(thisPos);

        listSize++;
    }

    else
    {
        throw std::out_of_range("List is full. Cannot insert at Head.");
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{

    if (listSize < arrayCapacity) // if size of objectlist (snake) hasn't reached max capacity. Keep inserting at the tail.
    {
        aList[listSize++].setObjPos(thisPos);
    }
    else
    {
        throw std::out_of_range("List is full. Cannot insert at Tail.");
    }
}
void objPosArrayList::removeHead()
{
    checkIndexValidity(); // if listsize is invalid. Cannot remove head.

    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i].setObjPos(aList[i + 1]); // shifts all the elements from head towards tail by 1 position.
    }
    listSize--; // removes the tail.
}

void objPosArrayList::removeTail()
{
    checkIndexValidity(); // if listsize is invalid. Cannot remove tail.
    listSize--;           // otherwise remove tail.
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    checkIndexValidity();          // if list size is invalid. Cannot access head of objectlist (snake).
    returnPos.setObjPos(aList[0]); // otherwise, return the position  of head.
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    checkIndexValidity();                     // if list size is invalid. Cannot access tail of objectlist (snake).
    returnPos.setObjPos(aList[listSize - 1]); // otherwise, return position of tail.
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < listSize) // if index is within bounds of ObjArraylist. Return position of element at the index.
    {
        returnPos.setObjPos(aList[index]);
    }
    else
    {
        throw std::out_of_range("Invalid index. Cannot get element."); // otherwise, Cannot access position at index.
    }
}

// Checks whether the index is valid (within bounds) or invalid (outside of bounds).
void objPosArrayList::checkIndexValidity()
{
    if (listSize <= 0 || listSize > arrayCapacity)
    {
        throw std::out_of_range("Invalid list size.");
    }
}