#include "LL.h"

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator++(int)
{
	iterator current(position);
	position = position->next;

	return current;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator++()
{
	position = position->next;

	return *this;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator--(int)
{
	iterator current(position);
	position = position->prev;

	return current;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator--()
{
	position = position->prev;

	return *this;
}

template <class type>
LL<type>::LL()
{
	dummy = new node; // create a node for dummy
	dummy->next = dummy; // setting dummy to point to itself
	dummy->prev = dummy;
}

template <class type>
LL<type>::LL(const LL<type>& copy)
{
	dummy = new node; // allocate node
	dummy->next = dummy; // setting dummy to point to itself
	dummy->prev = dummy;
	copyList(copy); // calling copyList
}

template <class type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs)
{
	if (this != &rhs)
	{
		//Your code goes here
		clearList(); // calls clearList()
		copyList(rhs); // calls copyList()
	}

	return *this;
}

template <class type>
LL<type>::~LL()
{
	clearList(); // clearList
	delete dummy; // delete the dummy node
	dummy = nullptr; // set it to point to null
}

template <class type>
void LL<type>::headInsert(const type& item)
{
	node* n; // create temp n
	n = new node; // give a new node
	n->item = item; // give it the item
	if(dummy->next == dummy) // if it is pointing to itself
	{
		dummy->next = n; // set that n to be both the tail and head
		dummy->prev = n;
		n->next = dummy;
		n->prev = dummy;
	}
	else
	{
		node* head; // else create a temp head
		head = dummy->next; // define head
		head->prev = n; // set original head to point to head
		n->next = head; // set new node to point to original head
		n->prev = dummy; // assign new head
		dummy->next = n;

	}
}

template <class type>
void LL<type>::tailInsert(const type& item)
{
	node* n; // create a n node
	n = new node; // create a new node
	n->item = item; // give this node the item
	if(dummy->next == dummy) // if it's the only node in the LL
	{
		dummy->next = n; // assign taht node both the head and tail
		dummy->prev = n;
		n->next = dummy;
		n->prev = dummy;
	}
	else
	{
		node* tail; // create tail
		tail = dummy->prev;
		tail->next = n; // set tail->next to pont to new node
		n->prev = tail; // set the new node previous to point to original tail
		n->next = dummy; // assign the new tail
		dummy->prev = n;
	}
}

template <class type>
void LL<type>::headRemove()
{
	if(dummy->next != dummy) // as long as there is a node
	{
		node* head; // create a head
		head = dummy->next; // set the head
		if(head->next == dummy) // if the head is the only node
		{
			dummy->next = dummy; // set dummy to point to itself
			dummy->prev = dummy;
		}
		else
		{
			dummy->next = head->next; // else have dummy->next point to head->next
			head->next->prev = dummy; // and have next->head->prev point to dummy
		}
		delete head; // remove the head
	}
}

template <class type>
void LL<type>::tailRemove()
{
	if(dummy->next != dummy) // as long as there is a node
	{
		node* tail; // create a tail
		tail = dummy->prev; // set the tail
		if(tail->prev == dummy) // if the tail is the only node
		{
			dummy->next = dummy; // set dummy to point to itself
			dummy->prev = dummy;
		}
		else
		{
			dummy->prev = tail->prev; // dummy-> prev to point to tail->prev
			tail->prev->next = dummy; // set the tail->prev next to dummy
		}
		delete tail; // delete the tail
	}
}

template <class type>
void LL<type>::removeAtPosition(LL<type>::iterator & it)
{
	node* current;
	current = it.position; // give current the position of the iterator
	if(current != dummy)
	{
		it.position = current->next; // set the position to point to next
		if(current->next == dummy && current->prev == dummy) // if theres only one
		{
			it.position = current->next; // reset it position so it doesn't point to dangling
			dummy->next = dummy; // set dummy to point to itself
			dummy->prev = dummy;
		}
		else if(current == dummy->next) // if the current is the head
		{
			it.position = current->next; // reset it position so it doesn't point to dangling
			dummy->next = current->next; // set dummy->next to next node
			current->next->prev = dummy; // set next node's previous to dummy
		}
		else if(current == dummy->prev) // if the current is the tail
		{
			it.position = current->prev; // reset it position so it doesn't point to dangling
			dummy->prev = current->prev; // set the dummy->prev to previous node
			current->prev->next = dummy; // set the current previous' next to dummy
		}
		else // else if it's in the middle
		{
			it.position = current->next; // reset it position so it doesn't point to dangling
			current->prev->next = current->next;
			current->next->prev = current->prev;
		}
		delete current; // delete the current
	}
}


template <class type>
void LL<type>::clearList()
{
	while(dummy->next != dummy)
	{
		headRemove(); // call headRemove until the only node left is the dummy node
	}
}

template <class type>
void LL<type>::copyList(const LL<type>& copyThisList)
{
	clearList(); // clear the list first
	for(auto it = copyThisList.begin(); it != copyThisList.end(); it++) // as long as the iterator is not at the end
	{
		tailInsert(*it); // call tail insert multiple times and dereference what iterator is pointing at
	}
}