#ifndef _LLNode
#define _LLNode

#include "..\Enemies\Enemy.h"

class LLNode
{
private:
	Enemy* item;	// A data item (can be any complex sturcture)
	LLNode* next;	// Pointer to next LLNode
public:
	LLNode();
	LLNode(Enemy* newItem);
	void setItem(Enemy* newItem);
	void setNext(LLNode* nextNodePtr);
	Enemy* getItem() const;
	LLNode* getNext() const;
}; // end LLNode

#endif	
