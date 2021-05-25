
#include "PQueue.h"

template<class ItemType>
PQueue<ItemType>::PQueue()
{
	slistPtr->getHead() = 0;
}

template<class ItemType>
PQueue<ItemType>::~PQueue()
{
}

template<class ItemType>
bool PQueue<ItemType>::isEmpty() const
{
	if(slistPtr->isEmpty())
		return true;
}

template< class ItemType>
bool PQueue<ItemType>::add(const ItemType& newEntry)
{
	slistPtr->insertSorted(newEntry);
	return true;
} 


template< class ItemType>
bool PQueue<ItemType>::remove()
{
	// The highest-priority item is at the end of the sorted list 
	return slistPtr->remove(slistPtr->getLength());
} 