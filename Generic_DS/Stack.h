#ifndef _STACK_H 
#define _STACK_H 
#include "Node.h"

template< class T>
class Stack
{
private:
	Node<T>* topPtr;
public:
	Stack();
	virtual ~Stack();
	bool isEmpty() const;
	bool push(const T& newEntry);
	bool pop();
	T peek() const;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Stack()
The constructor of the Stack class.

*/
template <class T>
Stack<T>::Stack() : topPtr(nullptr)
{
}
////////////////////////////////////////////////////////////////////////////////////////

/*
Function: ~Stack()
The destructor of the Stack class.

*/
template <class T>
Stack<T>::~Stack()
{
	while (!isEmpty())
		pop();
}
////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
checking whether the stack is empty or not.

Input: None.
Output: True if the Stack is empty; otherwise false.
*/
template< class T>
bool Stack<T>::isEmpty() const
{
	if (topPtr == nullptr;)
		return true;
	else
		return false;
}
////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Push
adding new item @ the top of the stack

Input: newEntry with type T.
Output: True if the newEntry is added; otherwise false.
*/
template< class T>
bool Stack<T>::push(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////

/*
Function: pop
Removes the top of this stack. That is, it removes the item that was added
most recently.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <class T>
bool Stack<T>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		Node<T>* nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext();
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		result = true;
	}
	return result;
}
////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
Returns the top of this stack.That is, it gets the item that was added most recently.
The operation does not change the stack.

Input : None.
Output : The top of the stack.
*/
template <class T>
T Stack<T>::peek() const
{
	if (!isEmpty())
		return topPtr->getItem();
}

