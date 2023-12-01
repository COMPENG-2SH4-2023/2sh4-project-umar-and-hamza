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
    if (listSize < arrayCapacity)
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

    if (listSize < arrayCapacity)
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
    checkIndexValidity();

    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i].setObjPos(aList[i + 1]);
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    checkIndexValidity();
    listSize--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    checkIndexValidity();
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    checkIndexValidity();
    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < listSize)
    {
        returnPos.setObjPos(aList[index]);
    }
    else
    {
        throw std::out_of_range("Invalid index. Cannot get element.");
    }
}

void objPosArrayList::checkIndexValidity()
{
    if (listSize <= 0 || listSize > arrayCapacity)
    {
        throw std::out_of_range("Invalid list size.");
    }
}