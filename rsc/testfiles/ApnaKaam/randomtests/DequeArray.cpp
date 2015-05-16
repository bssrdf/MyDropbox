//#include "DequeArray.h"

#include "DequeADT.h"

#include <deque>
#include <iostream>
#include <stdlib.h>

using namespace std;

template <class T>
class DequeArray : public DequeADT<T> {
	private:
		//TODO add private members here
		int numentry,arraysize,firstposition,lastposition;
		T* Dequearray;

	public:
		DequeArray();

		void push_front (const T& val);
		void push_back (const T& val);	
		void clear();
		bool empty();	
		T front();	
		T back();	
		T at(int index);	
		void pop_front();	
		void pop_back();	
		int size();
		void print();

};

template <class T>
DequeArray<T>::DequeArray()
{
	//TODO
	arraysize=10;
	numentry=0;
	firstposition=-1;
	lastposition=-1;
	Dequearray=new T[10];
}

template <class T>
void DequeArray<T>::push_front (const T& val)
{
	//TODO
	if (numentry==0)
	{
		firstposition=0;
		lastposition=0;
		Dequearray[0]=val;
		numentry++;
		return;
	}
	if (numentry!=arraysize)
	{
		firstposition=((firstposition-1)+arraysize)%arraysize;
		Dequearray[firstposition]=val;
		numentry++;
	}
	else
	{
		arraysize=arraysize*2;
		T* Newarray=new T[arraysize];
		for (int i=0;i<numentry;i++)
		{
			Newarray[i]=Dequearray[(firstposition+i)%(arraysize/2)];
		}
		firstposition=arraysize-1;
		Newarray[firstposition]=val;
		lastposition=numentry-1;
		delete[] Dequearray;
		Dequearray=Newarray;
		numentry++;
	}
}


template <class T>
void DequeArray<T>::push_back (const T& val)
{
	//TODO
		if (numentry==0)
		{
			firstposition=0;
			lastposition=0;
			Dequearray[0]=val;
			numentry++;
			return;
		}
		if (numentry!=arraysize)
	{
		lastposition=(lastposition+1)%arraysize;
		Dequearray[lastposition]=val;
		numentry++;
	}
	else
	{
		arraysize=arraysize*2;
		T* Newarray=new T[arraysize];
		for (int i=0;i<numentry;i++)
		{
			Newarray[i]=Dequearray[(firstposition+i)%(arraysize/2)];
		}
		firstposition=0;
		lastposition=numentry;
		Newarray[lastposition]=val;
		delete[] Dequearray;
		Dequearray=Newarray;
		numentry++;
	}
	
}

template <class T>
void DequeArray<T>::clear()
{
	//TODO
	numentry=0;
	firstposition=-1;
	lastposition=-1;
}
	
template <class T>
bool DequeArray<T>::empty()
{
	//TODO
	return (numentry==0);
}
	
template <class T>
T DequeArray<T>::front()
{
	return Dequearray[firstposition];
}
	
template <class T>
T DequeArray<T>::back()
{
	//TODO
	return Dequearray[lastposition];
}
	
template <class T>
T DequeArray<T>::at(int index)
{
	//TODO
	return Dequearray[index];
}
	
template <class T>
void DequeArray<T>::pop_front()
{
	//TODO
	if (numentry==0)
	{
		cout<<"Error, empty Deque exception"<<endl;
		exit(0);
	}


	if (numentry!=1)
		firstposition=(firstposition+1)%arraysize;
	else
		firstposition=-1;
	
	numentry--;
}
	
template <class T>
void DequeArray<T>::pop_back()
{
	//TODO
	if (numentry==0)
	{
		cout<<"Error, empty Deque exception"<<endl;
		exit(0);
	}
	if (numentry!=1)
		lastposition=(lastposition+arraysize-1)%arraysize;
	else
		lastposition=-1;
	
	numentry--;
}
	
template <class T>
int DequeArray<T>::size()
{
	//TODO
	return numentry;
}

/*
template <typename T>
void DequeArray<T>::print()
{
	for(int i = 0; i < size(); i++)
	{
		cout << at(i) << endl;
	}
}
*/
