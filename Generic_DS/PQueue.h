#pragma once
#ifndef _PRIORITY_QUEUE 
#define _PRIORITY_QUEUE 

#include "LinkedSortedList.h" 
template< class ItemType>
class PQueue 
{
private:
	LinkedSortedList<ItemType>* slistPtr; // Pointer to sorted list of
	// items in the priority queue
public:
	PQueue();
	~PQueue();
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove();

}; // end SL_PriorityQueue 
#endif

