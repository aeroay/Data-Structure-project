#include "LinkedList.h"
using namespace std;


LinkedList::LinkedList()
{
	count = 0;
	Head = NULL;
}

//List is being desturcted ==> delete all items in the list
LinkedList::~LinkedList()
{
	DeleteAll();
}

/*
* Function: InsertBeg.
* Creates a new node and adds it to the beginning of a linked list.
*
* Parameters:
*	- data : The value to be stored in the new node.
*/
void LinkedList::InsertBeg(Enemy* data)
{
	LLNode* R = new LLNode(data);
	R->setNext(Head);
	Head = R;
	count++;

}
////////////////////////////////////////////////////////////////////////
/*
* Function: DeleteAll.
* Deletes all nodes of the list.
*/
void LinkedList::DeleteAll()
{
	LLNode* P = Head;
	while (Head != NULL)
	{
		P = Head->getNext();
		delete Head;
		Head = P;
	}
	count = 0;
}

////////////////////////////////////////////////////////////////////////
/*
* Function: DeleteNode.
* Deletes specific nodes in the list.
*/
bool LinkedList::DeleteNode(Enemy* value)
{
	LLNode* P = Head;
	if (P->getItem() == value) {
		Head = P->getNext();
		delete P;
		P = NULL;
		count--;
		return true;
	}
	while (P != NULL) {
		if (P->getNext() != NULL && (P->getNext())->getItem() == value) {
			LLNode* temp = P->getNext();
			LLNode* nxt = temp->getNext();
			delete temp;
			temp = NULL;
			P->setNext(nxt);
			count--;
			return true;
		}

		P = P->getNext();
	}
	return false;
}
