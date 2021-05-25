#include "LLNode.h"

LLNode::LLNode()
{
	next = NULL;
}  

LLNode::LLNode(Enemy* newItem)
{
	item = newItem;
	next = NULL;

}

void LLNode::setItem(Enemy* newItem)
{
	item = newItem;
} 

void LLNode::setNext(LLNode* nextNodePtr)
{
	next = nextNodePtr;
} 

Enemy* LLNode::getItem() const
{
	return item;
} 

LLNode* LLNode::getNext() const
{
	return next;
} 