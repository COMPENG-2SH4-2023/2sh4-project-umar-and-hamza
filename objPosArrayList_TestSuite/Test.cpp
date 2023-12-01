#include "./cute/cute.h"
#include "./cute/ide_listener.h"
#include "./cute/xml_listener.h"
#include "./cute/cute_runner.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include <iostream>

// WARNING!!  This test suite does not contain any test cases for accessing elements out-of-bound.
//
// You must deploy exception throwing for all out-of-bound accesses.

// Test Case 1 - Constructor Tester
// - Will require you to implement getSize() and getElement() methods.
void testConstructor()
{
	objPos zeroPos, currentPos;
	objPosArrayList thisList;
	int expectedSize = 0;
	int actualSize = thisList.getSize();

	// First check the list size
	ASSERT_EQUAL(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then check all elements in the array are zero-initialized via objPos() default constructor
	for (int i = 0; i < ARRAY_MAX_CAP; i++)
	{
		thisList.getElement(currentPos, i);
		actualCheck = zeroPos.isPosEqual(&currentPos);

		ASSERT_EQUAL(expectedCheck, actualCheck);
	}

	// The destructor will be called automatically for stack-allocated objects
}

// Test Case 2a - insertHead 1 Element
// - Will require you to implement getHeadElement(), getTailElement(), and getElement() methods.
void testInsertHead_1Element()
{
	objPos currentPos;
	objPos samplePos{2, 5, 'a'};

	// Insert 1 sample element
	objPosArrayList thisList;
	thisList.insertHead(samplePos);

	int expectedSize = 1;
	int actualSize = thisList.getSize();

	// First check the list size is 1
	ASSERT_EQUAL(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then check whether the head element is what we have inserted.
	thisList.getHeadElement(currentPos);
	actualCheck = samplePos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// Next, check whether the tail element is also the head element in a list of 1 element.
	thisList.getTailElement(currentPos);
	actualCheck = samplePos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// Finally, chech whether the element at index = 0 is also the head element in a list of 1 element
	// Then check whether the head element is what we have inserted.
	thisList.getElement(currentPos, 0);
	actualCheck = samplePos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// The destructor will be called automatically for stack-allocated objects
}

// Test Case 2b - insertHead 5 Element
// - Will require you to implement getHeadElement() and getTailElement() method.
void testInsertHead_5Element()
{
	objPos currentPos;
	objPos bodyPos{2, 5, 'a'};
	objPos headPos{3, 3, 'm'};

	// Insert 4 body elements, then 1 unique head element
	objPosArrayList thisList;
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(headPos);

	int expectedSize = 5;
	int actualSize = thisList.getSize();

	// Confirm the list size is now 5
	ASSERT_EQUAL(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then, check the head element is the unique element
	thisList.getHeadElement(currentPos);
	actualCheck = headPos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// Next, chech the body elements at index 1, 2, and 3.
	for (int i = 1; i < actualSize - 1; i++)
	{
		thisList.getElement(currentPos, i);
		actualCheck = bodyPos.isPosEqual(&currentPos);

		ASSERT_EQUAL(expectedCheck, actualCheck);
	}

	// Finally, check the tail element is the body element
	thisList.getTailElement(currentPos);
	actualCheck = bodyPos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// The destructor will be called automatically for stack-allocated objects
}

// Test Case 3a - insertTail 1 Element
void testInsertTail_1Element()
{
	objPos currentPos;
	objPos samplePos{2, 5, 'a'};

	// Insert 1 sample element
	objPosArrayList thisList;
	thisList.insertTail(samplePos);

	int expectedSize = 1;
	int actualSize = thisList.getSize();

	// First check the list size is 1
	ASSERT_EQUAL(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then check whether the head element is what we have inserted.
	thisList.getHeadElement(currentPos);
	actualCheck = samplePos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// Next, check whether the tail element is also the head element in a list of 1 element.
	thisList.getTailElement(currentPos);
	actualCheck = samplePos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// Finally, chech whether the element at index = 0 is also the head element in a list of 1 element
	// Then check whether the head element is what we have inserted.
	thisList.getElement(currentPos, 0);
	actualCheck = samplePos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// The destructor will be called automatically for stack-allocated objects
}

// Test Case 3b - insertTail 5 Element
void testInsertTail_5Element()
{
	objPos currentPos;
	objPos bodyPos{2, 5, 'a'};
	objPos tailPos{3, 3, 'm'};

	// Insert 4 body elements, then 1 unique head element
	objPosArrayList thisList;
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(tailPos);

	int expectedSize = 5;
	int actualSize = thisList.getSize();

	// Confirm the list size is now 5
	ASSERT_EQUAL(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then, check the head element is the common body element
	thisList.getHeadElement(currentPos);
	actualCheck = bodyPos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// Next, chech the body elements at index 1, 2, and 3.
	for (int i = 1; i < actualSize - 1; i++)
	{
		thisList.getElement(currentPos, i);
		actualCheck = bodyPos.isPosEqual(&currentPos);

		ASSERT_EQUAL(expectedCheck, actualCheck);
	}

	// Finally, check the tail element is the body element
	thisList.getTailElement(currentPos);
	actualCheck = tailPos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// The destructor will be called automatically for stack-allocated objects
}

// Test Case 4a - removeHead from 1 Element List
void testRemoveHead_1Element()
{
	objPos currentPos;
	objPos samplePos{2, 5, 'a'};

	// Insert 1 sample element
	objPosArrayList thisList;
	thisList.insertHead(samplePos);

	thisList.removeHead();

	int expectedSize = 0;
	int actualSize = thisList.getSize();

	// The destructor will be called automatically for stack-allocated objects
}

// Test Case 4b - removeHead from 5 Element list
void testRemoveHead_5Element()
{
	objPos currentPos;
	objPos bodyPos{2, 5, 'a'};
	objPos headPos{3, 3, 'm'};

	// Insert 4 body elements, then 1 unique head element
	objPosArrayList thisList;
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(bodyPos);
	thisList.insertHead(headPos);

	thisList.removeHead();

	int expectedSize = 4;
	int actualSize = thisList.getSize();

	// Confirm the list size is now 4
	ASSERT_EQUAL(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then, check the unique element has been removed
	thisList.getHeadElement(currentPos);
	actualCheck = bodyPos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// Next, the rest of the elements are still common elements
	for (int i = 1; i < actualSize; i++)
	{
		thisList.getElement(currentPos, i);
		actualCheck = bodyPos.isPosEqual(&currentPos);

		ASSERT_EQUAL(expectedCheck, actualCheck);
	}

	// The destructor will be called automatically for stack-allocated objects
}

// Test Case 5a - removeTail 1 Element
void testRemoveTail_1Element()
{
	objPos currentPos;
	objPos samplePos{2, 5, 'a'};

	// Insert 1 sample element
	objPosArrayList thisList;
	thisList.insertTail(samplePos);

	thisList.removeTail();

	int expectedSize = 0;
	int actualSize = thisList.getSize();

	// First check the list size is 1
	ASSERT_EQUAL(expectedSize, actualSize);

	// The destructor will be called automatically for stack-allocated objects
}

// Test Case 5b - removeTail 5 Element
void testRemoveTail_5Element()
{
	objPos currentPos;
	objPos bodyPos{2, 5, 'a'};
	objPos tailPos{3, 3, 'm'};

	// Insert 4 body elements, then 1 unique head element
	objPosArrayList thisList;
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(bodyPos);
	thisList.insertTail(tailPos);

	thisList.removeTail();

	int expectedSize = 4;
	int actualSize = thisList.getSize();

	// Confirm the list size is now 4
	ASSERT_EQUAL(expectedSize, actualSize);

	bool expectedCheck = true;
	bool actualCheck;

	// Then, check the tail element removed
	thisList.getTailElement(currentPos);
	actualCheck = bodyPos.isPosEqual(&currentPos);

	ASSERT_EQUAL(expectedCheck, actualCheck);

	// Next, chech the body elements at index 1, 2, and 3.
	for (int i = 0; i < actualSize - 1; i++)
	{
		thisList.getElement(currentPos, i);
		actualCheck = bodyPos.isPosEqual(&currentPos);

		ASSERT_EQUAL(expectedCheck, actualCheck);
	}

	// The destructor will be called automatically for stack-allocated objects
}
// Test case 6 - Attempt to access elements outside of bounds.
void testAccessOutOfBounds()
{
	objPosArrayList thisList;
	objPos currentPos;

	// Attempting to access elements from an empty list should throw an exception
	ASSERT_THROWS(thisList.getElement(currentPos, 0), std::out_of_range);

	// Insert a sample element
	objPos samplePos{2, 5, 'a'};
	thisList.insertHead(samplePos);

	// Attempting to access an element beyond the list size should throw an exception
	ASSERT_THROWS(thisList.getElement(currentPos, 1), std::out_of_range);
}
// Test Case 6b - Attempt to Insert Beyond Capacity
void testInsertBeyondMaxCapacity()
{
	objPosArrayList thisList;

	// Insert elements up to max capacity
	for (int i = 0; i < ARRAY_MAX_CAP; ++i)
	{
		objPos pos{i, i + 1, 'a'};
		thisList.insertTail(pos);
	}

	// Attempt to insert one more element
	objPos extraPos{100, 101, 'b'};

	// Check if attempting to insert beyond max capacity throws an exception
	ASSERT_THROWS(thisList.insertTail(extraPos), std::out_of_range);
}

bool runAllTests(int argc, char const *argv[])
{
	cute::suite s;

	s.push_back(CUTE(testConstructor));
	s.push_back(CUTE(testInsertHead_1Element));
	s.push_back(CUTE(testInsertHead_5Element));
	s.push_back(CUTE(testInsertTail_1Element));
	s.push_back(CUTE(testInsertTail_5Element));
	s.push_back(CUTE(testRemoveHead_1Element));
	s.push_back(CUTE(testRemoveHead_5Element));
	s.push_back(CUTE(testRemoveTail_1Element));
	s.push_back(CUTE(testRemoveTail_5Element));

	// TODO add your test here

	s.push_back(CUTE(testAccessOutOfBounds));
	s.push_back(CUTE(testInsertBeyondMaxCapacity));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[])
{
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}