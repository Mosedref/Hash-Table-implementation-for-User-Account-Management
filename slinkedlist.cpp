#ifdef _SLINKEDLIST_H_

#include <cstdlib>
#include <string>
#include <vector>


// helper function for deep copy
// Used by copy constructor and operator=
template <class T>
void SLinkedList <T> ::CopyList(const SLinkedList& ll)
{
	
		if(ll.IsEmpty() == true)
		{
			return;
		}

		 Node<T>* cursor = ll.front;

		 while(cursor != NULL)
		 {
			 InsertBack(cursor->data);
			 cursor = cursor->next;
		 }
}

// helper function for deep delete
// Used by destructor and copy/assignment
template <class T>
void SLinkedList <T>::DeleteList()
{
	RemoveAll();
}

//--------------------------------------------Constructors-------------------------------------------------   

// default constructor
//Initialize Template Class of Link List
template <class T>
SLinkedList<T>::SLinkedList()
{
	size = 0;
	front = NULL;
	back = NULL;
}

// copy constructor, performs deep copy of list elements
template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList& ll)
{
	
		front = NULL;
		back = NULL;
		size = 0;
		CopyList(ll);
}

// destructor
template <class T>
SLinkedList <T>::~SLinkedList()
{
	if(IsEmpty() == false)
	{
		DeleteList();
	}
}

//------------------------------------------------MUTATORS---------------------------------------------   

// Inserts an item at the front of the list
// POST:  List contains item at front
// PARAM: item = item to be inserted
template <class T>
void SLinkedList <T>::InsertFront(T item)
{
	Node<T>* temp = new Node<T>(item);

	if(front == NULL)
	{
		front = temp;
		back = front;
	}
	else
	{
		temp->next = front;
		front = temp;
	}
	size++;
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <class T>
void SLinkedList <T>::InsertBack(T item)
{
	Node<T>* temp = new Node<T>(item);

	if(front == NULL)
	{
		front = temp;
		back = front;
	}
	else
	{
		back->next = temp;
		back = temp;
	}
	size++;

}

// Removes the first occurrence of the supplied parameter
// Removes and returns true if found, otherwise returns false if parameter is not found or list is empty
template <class T>
bool SLinkedList <T>::Remove(T item)
{
	if(Contains(item) == false)
	{
		return false;
	}

	Node<T>* delPtr = NULL; 
	Node<T>*prev = front; 
	Node<T>*curr = front;

	while(curr != NULL && curr->data != item)
	{ 
		prev=curr; 
		curr=curr->next;
	}
	
	//empty list or no item in list
	if(curr == NULL)
	{ 
		return false; 
	}

	//item in front
	else if(curr == front)
	{
		front = front->next;
		delete curr;

	}
	//last item in list
	else if(curr->next == NULL)
	{
	  back = prev;	
	  delete curr;
	  back->next = NULL;
		
	} 
	
	else
	{ 
		delPtr=curr; 
		curr=curr->next;
		prev->next=curr;
		delPtr->next = NULL;
		delete delPtr;
	} 
	
	size--;
	return true;

}

// Removes all items in the list
template <class T>
void SLinkedList <T>::RemoveAll()
{
	Node<T>* cursor = front;

	while(front != NULL)
	{
		front = front->next;
		cursor->next = NULL;
		delete cursor;
		cursor = front;

	}

	size = 0;
	front = NULL;
	back = NULL;

}


// Returns size of list
template <class T>
int SLinkedList <T>::Size() const
{
	return size;
}

// Returns whether the list is empty
template <class T>
bool SLinkedList <T>::IsEmpty() const
{
	if(front== NULL)
	{
		return true;
	}
	return false;
}


// Returns existence of item
template <class T>
bool SLinkedList <T>::Contains(T item) const
{
	Node<T>* cursor = front;

	while(cursor!= NULL)
	{
		if(cursor->data == item)
		{
			return true;
		}
		cursor = cursor->next;

	}

	return false;

}

// Returns a pointer to the in-place list item or NULL if item not found
template <class T>
T* SLinkedList <T>::Retrieve(T item)
{
	Node<T>* cursor = front;
	T* found = NULL;

	while(cursor!= NULL)
	{
		if(cursor->data == item)
		{
			found = &(cursor->data);
			return found;
		}
		cursor = cursor->next;

	}

	return found;
}

// Returns a vector containing the list contents using push_back
template <class T>
vector<T> SLinkedList <T>::Dump() const
{
	vector<T> contents;
	Node<T>* cursor = front;

	while(cursor!= NULL)
	{
		contents.push_back(cursor->data);
		cursor = cursor->next;
	}

	return contents;

}
// overloaded operator
template <class T>
SLinkedList<T>& SLinkedList <T>::operator=(const SLinkedList& ll)
{
	if(this != &ll)
	{
		DeleteList();
		CopyList(ll);
	}

	return *this;
}

#endif


