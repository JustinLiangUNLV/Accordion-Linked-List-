#include <cstdlib>
#include "myStack.h"

template <class type>
myStack<type>::myStack()
{
	size = 0; // initialize size to 0
	capacity = 5; // initialize capacity to 5
	stackElements = new type[capacity]; // initialize stackElements
}

template <class type>
myStack<type>::myStack(const myStack<type>& copy)
{
	stackElements = nullptr;
	clearStack();
	copyStack(copy); // calls copy stack
}

template <class type>
const myStack<type>& myStack<type>::operator=(const myStack<type>& rhs)
{
	if (this != & rhs)
	{
		//Your code goes here
		clearStack(); // use clearStack
		copyStack(rhs); // use copyStack
	}

	return *this;
}

template <class type>
myStack<type>::~myStack()
{
	clearStack(); // use clearStack function
}

template <class type>
void myStack<type>::push(const type& item)
{
	if(size == capacity)
	{
		capacity *= 2; // doubling capacity
		type* biggerStack = new type[capacity]; // create new stack
		for(size_t i = 0; i < size; i++)
		{
			biggerStack[i] = stackElements[i]; // deep copying
		}
		delete[] stackElements; // delete original dynamic array
		stackElements = biggerStack; // setting stackElements to biggerStack
		biggerStack = nullptr; // set biggerStack to nullptr
	}
	stackElements[size] = item; // insert item at index size
	size++; // incrementing size

}

template <class type>
type myStack<type>::peek() const
{
	if(isEmpty())
	{
		throw std::out_of_range("Stack is empty"); // if stack empty, throw an exception
	}
	return stackElements[size - 1]; // return the topmost element
}

template <class type>
std::size_t myStack<type>::getSize() const
{
	return size; // return size
}

template <class type>
type myStack<type>::pop()
{
	if(isEmpty())
	{
		throw std::out_of_range("Stack is empty"); // if stack empty, throw an exception
	}
	return stackElements[--size]; // return the topmost element
}

template <class type>
bool myStack<type>::isEmpty() const
{
	return size == 0; // return true if size is 0
}

template <class type>
void myStack<type>::clearStack()
{
	delete[] stackElements; // delete the dynamic array
	stackElements = nullptr; // set it to nullptr
	size = 0; // size and capacity to 0
	capacity = 0;
}

template <class type>
void myStack<type>::copyStack(const myStack<type>& copyThisStack)
{
	clearStack();
	this->size = copyThisStack.size; // copy over size
	this->capacity = copyThisStack.capacity; // copy over capacity
	this->stackElements = new type[capacity]; // create new dynamic array
	for(size_t i = 0; i < size; i++)
	{
		stackElements[i] = copyThisStack.stackElements[i]; // deep copy the array
	}

}

