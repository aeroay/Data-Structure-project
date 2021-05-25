#include "LinkedSortedList.h"

template< class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::
getNodeBefore(const ItemType& anEntry) const
{
	Node<ItemType>* curPtr = headPtr;
	Node<ItemType>* prevPtr = nullptr;
	while ((curPtr != nullptr) && (anEntry > curPtr->getItem()))
	{
		prevPtr = curPtr;
		curPtr = curPtr->getNext();
	} 
	return prevPtr;
}
template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList()
{
	headPtr = nullptr;
	itemCount = 0;
}

template<class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList()
{
}



template< class ItemType>
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
	Node<ItemType>* prevPtr = getNodeBefore(newEntry);
	if (isEmpty() || (prevPtr == nullptr)) // Add at beginning 
	{
		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;
	}
	else // Add after node before 
	{
		Node<ItemType>* aftPtr = prevPtr->getNext();
		newNodePtr->setNext(aftPtr);
		prevPtr->setNext(newNodePtr);
	} // end if 
	itemCount++;
} // end insertSorted 

template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const
{
	if (headPtr = nullptr)
		return true;
}

template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getHead()
{
	return headPtr;
}
