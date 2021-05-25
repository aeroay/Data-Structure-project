#ifndef _LINKED_SORTED_LIST 
#define _LINKED_SORTED_LIST 
#include "Node.h" 
template< class ItemType>
class LinkedSortedList 
{
private:
	Node<ItemType>* headPtr; // Pointer to first node in the chain 
	int itemCount; // Current count of list items
	Node<ItemType>* getNodeBefore(const ItemType& anEntry) const;
public:
	LinkedSortedList();
	virtual ~LinkedSortedList();
	void insertSorted(const ItemType& newEntry);
	bool isEmpty() const;
	int getLength() const;
	Node<ItemType>* getHead();
}; 
#endif