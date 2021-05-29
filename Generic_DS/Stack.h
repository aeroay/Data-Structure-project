#pragma once
#include "Node.h"

template < typename T>
class Stack
{
	Node<T>* Top;
public:
	Stack();
	bool isEmpty()const;
	bool push(T it);
	bool pop(T& it);
	T peek()const;
	const T* toArray(int& size);
};

template < typename T>
Stack<T> ::Stack()
{
	Top = NULL;
}

template < typename T>
bool Stack<T> ::isEmpty()const
{
	if (Top)
		return false;
	return true;
}

template < typename T>
T Stack<T> ::peek()const
{
	if (!isEmpty())
		return Top->getItem();
}

template < typename T>
bool Stack<T> ::pop(T& it)
{
	if (isEmpty())return false;
	Node<T>* Temp = Top;
	Top = Top->getNext();
	it = Temp->getItem();
	delete Temp;
	return true;
}

template < typename T>
bool Stack<T> ::push(T it)
{
	Node<T>* Added = new Node<T>(it);
	if (!Added)return false;
	Added->setNext(Top);
	Top = Added;
	return true;
}

template <typename T>
const T* Stack<T>::toArray(int& count)
{
	count = 0;

	if (!Top)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = Top;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = Top;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}
