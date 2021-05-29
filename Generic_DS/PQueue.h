#pragma once
#include "nodeP.h"

template <typename T>
class PQueue
{
private:

	nodeP<T>* backPtr;
	nodeP<T>* frontPtr;
public:
	PQueue();
	bool isEmpty() const;
	bool enPQueue(const T& newEntry,int);
	bool dePQueue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;

	//toArray function to be used when drawing the PQueue items
	const T* toArray(int& count);	//returns array of T (array of items)


	~PQueue();
};


template <typename T>
PQueue<T>::PQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}

template <typename T>
bool PQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}


template <typename T>
bool PQueue<T>::enPQueue(const T& newEntry, int prio)
{
	nodeP<T>* newnodePPtr = new nodeP<T>(newEntry, prio);

	// Insert the new nodeP
	if (isEmpty())
	{
		frontPtr = newnodePPtr;// The PQueue is empty
		backPtr = newnodePPtr;
		return true;
	}

	nodeP<T>* tmp1 = frontPtr;
	nodeP<T>* tmp2 = frontPtr->getNext();
	if (tmp1 && !tmp2)// special case if the queue has only one node
	{
		if (tmp1->getP() < newnodePPtr->getP())
		{
			newnodePPtr->setNext(tmp1);
			frontPtr = newnodePPtr;
			backPtr = tmp1;
		}
		else
		{
			tmp1->setNext(newnodePPtr);
			backPtr = newnodePPtr;
		}
	}
	else
	{
		if (newnodePPtr->getP() > frontPtr->getP())// if number is already bigger than all the numbers insert first
		{
			newnodePPtr->setNext(tmp1);
			frontPtr = newnodePPtr;
			return true;
		}
		while (tmp1 && tmp2 && (tmp1->getP()) >= (newnodePPtr->getP()) && (tmp2->getP()) >= (newnodePPtr->getP()))// the queue is this condition is already sorted 
		{
			tmp1 = tmp1->getNext();
			tmp2 = tmp2->getNext();
		}
		newnodePPtr->setNext(tmp2);
		tmp1->setNext(newnodePPtr);
	}
	
	return true;
}


template <typename T>
bool PQueue<T>::dePQueue(T& frntEntry)
{
	if (isEmpty())
		return false;

	nodeP<T>* nodePToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// PQueue is not empty; remove front
	if (nodePToDeletePtr == backPtr)	 // Special case: one nodeP in PQueue
		backPtr = nullptr;

	// Free memory reserved by the dePQueued nodeP
	delete nodePToDeletePtr;


	return true;

}


template <typename T>
bool PQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}


template <typename T>
PQueue<T>::~PQueue()
{

}


//count: the length of the returned array(zero if PQueue is empty)
//returns: The array of T. (nullptr if PQueue is empty)
template <typename T>
const T* PQueue<T>::toArray(int& count)
{

	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the PQueue
	nodeP<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;

}




