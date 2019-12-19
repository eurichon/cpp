#pragma once
#include <iostream>

enum Direction { Before, After };

template <class Xtype>
class list;

template<class Xtype>
void swap(Xtype* a, Xtype* b);

template <class Xtype>
void quickSort(Xtype arr[], int low, int high, int comp(Xtype &, Xtype &));

template<class Xtype>
int partition(Xtype arr[], int low, int high, int comp(Xtype &, Xtype &));


template <class Xtype>
class list
{
private:
	typedef struct Node {
		Xtype data;
		Node *next;
		Node *pre;
	}Node;

	Node *front_element;
	Node *rear_element;
	int num_of_elements;
	bool isFront(Node *n);
	bool isBack(Node *n);

	friend void quickSort(Xtype arr[], int low, int high, int comp(Xtype &, Xtype &));
	void initList();
public:
	list();
	list(Xtype *arr, int size);
	inline int size(); //done
	inline bool empty(); //done
	Xtype& back(); //done
	Xtype& front(); //done
	bool push_back(Xtype item); //done
	bool push_front(Xtype item); //done
	bool pop_back(); //done
	bool pop_front(); //done
	void swap(list &x); //done
	void sort(int comp(Xtype &, Xtype &));
	void clear(); //done
	~list();

	class Iterator;

	Iterator begin() {
		return Iterator(front_element->next);
	}

	Iterator end() {
		return  Iterator(rear_element);
	}

	bool erase(Iterator &it) {
		if (!isFront(it.curr) && !isBack(it.curr)) {
			Node *n = it.curr->next;
			it.curr->pre->next = it.curr->next;
			it.curr->next->pre = it.curr->pre;
			delete it.curr;
			it.curr = n;
			num_of_elements--;
			return true;
		}
		else {
			return false;
		}
	}

	bool erase(Iterator &first, Iterator &last) {
		Node *n = last.curr->next;
		while ((first.curr != last.curr)) {
			if (isFront(last.curr) || isBack(last.curr))
				return false;
			last.curr = last.curr->pre;
			delete last.curr->next;
			num_of_elements--;
		}
		first.curr->pre->next = n;
		n->pre = first.curr->pre;
		delete first.curr;
		num_of_elements--;

		first.curr = last.curr = n;
		return true;
	}

	bool insert(Iterator &it, Xtype item, Direction dir) {
		Node *newNode;
		newNode = new (std::nothrow) Node();
		if (!newNode) {
			std::cerr << "bad_alloc caught in insert" << std::endl;
			return false;
		}

		newNode->data = item;

		if (num_of_elements) {
			if (!dir) {
				newNode->next = (it.curr);
				newNode->pre = (it.curr)->pre;
				(it.curr)->pre->next = newNode;
				(it.curr)->pre = newNode;
				it--;
			}
			else {
				newNode->next = (it.curr)->next;
				newNode->pre = (it.curr);
				(it.curr)->next->pre = newNode;
				(it.curr)->next = newNode;
				it++;
			}
		}
		else {
			newNode->next = rear_element;
			newNode->pre = front_element;
			front_element->next = newNode;
			rear_element->pre = newNode;
			it.curr = newNode;
		}

		num_of_elements++;
		return true;
	}

	class Iterator {
	private:
		friend class list;
		Node *curr;
	public:
		Iterator() {
			this->curr = nullptr;
		}
		Iterator(Node *pNode) {
			this->curr = pNode;
		}
		Iterator(const Iterator &it) {
			this->curr = it.curr;
		}
		Xtype operator*() {
			return curr->data;
		}
		Iterator& operator=(Node *pNode) {
			this->curr = pNode;
			return *this;
		}
		Iterator& operator++()
		{
			if (!(curr == curr->next)) {
				curr = curr->next;
			}
			return *this;
		}
		Iterator operator++(int) {
			Iterator iterator = *this;
			++*this;
			return iterator;
		}
		Iterator& operator--()
		{
			if (curr != curr->pre) {
				curr = curr->pre;
			}
			return *this;
		}
		Iterator operator--(int) {
			Iterator iterator = *this;
			--*this;
			return iterator;
		}
		bool operator!=(const Iterator& iterator) {
			return (curr != iterator.curr);
		}
		friend bool advance(Iterator &it, int distance) {
			if (distance >= 0) {
				for (int i = 0; i < distance; i++) {
					if (it.curr != it.curr->next) {
						it.curr = it.curr->next;
					}
					else {
						return false;
					}
				}
			}
			else {
				for (int i = distance; i != 0; i++) {
					if (it.curr != it.curr->pre) {
						it.curr = it.curr->pre;
					}
					else {
						return false;
					}
				}
			}
			return true;
		}
	};
};


template<class Xtype>
inline bool list<Xtype>::isFront(Node * n)
{
	return (n->pre == n) ? (true) : (false);
}

template<class Xtype>
inline bool list<Xtype>::isBack(Node * n)
{
	return (n->next == n) ? (true) : (false);
}

template<class Xtype>
inline void list<Xtype>::initList()
{
	num_of_elements = 0;

	front_element = new Node();
	front_element->pre = front_element;
	front_element->data = NULL;

	rear_element = new Node();
	rear_element->next = rear_element;
	rear_element->data = NULL;

	front_element->next = rear_element;
	rear_element->pre = front_element;
}

template <class XType>
list<XType>::list() {
	this->initList();
}

template<class Xtype>
inline list<Xtype>::list(Xtype *arr, int size)
{
	this->initList();
	Iterator it = this->begin();

	for (int i = 0; i < size; i++) {
		if (!insert(it, arr[i], Direction::After))
			exit(-1);
	}
}

template<class Xtype>
inline int list<Xtype>::size()
{
	return num_of_elements;
}

template<class Xtype>
inline bool list<Xtype>::empty()
{
	return (num_of_elements) ? (false) : (true);
}

template<class Xtype>
Xtype& list<Xtype>::back()
{
	try {
		if (!isFront(rear_element->pre)) {
			return (this->rear_element->pre->data);
		}
		else {
			throw;
		}
	}
	catch (...) {
		std::cerr << "bad_alloc caught in push_back" << std::endl;
		exit(-1);
	}
}

template<class Xtype>
Xtype& list<Xtype>::front()
{
	try {
		if (!isBack(front_element->next)) {
			return (this->front_element->next->data);
		}
		else {
			throw;
		}
	}
	catch (...) {
		std::cerr << "bad_alloc caught in push_back" << std::endl;
		exit(-1);
	}
}

template<class Xtype>
bool list<Xtype>::push_back(Xtype item)
{
	Node *newNode;
	newNode = new (std::nothrow) Node();
	if (!newNode) {
		std::cerr << "bad_alloc caught in push_back" << std::endl;
		return false;
	}
	newNode->data = item;
	newNode->next = rear_element;
	newNode->pre = rear_element->pre;
	rear_element->pre->next = newNode;
	rear_element->pre = newNode;
	num_of_elements++;

	return true;
}

template<class Xtype>
bool list<Xtype>::push_front(Xtype item)
{
	Node *newNode;
	newNode = new (std::nothrow) Node();
	if (!newNode) {
		std::cerr << "bad_alloc caught in push_front" << std::endl;
		return false;
	}
	newNode->data = item;
	newNode->next = front_element->next;
	newNode->pre = front_element;
	front_element->next->pre = newNode;
	front_element->next = newNode;
	num_of_elements++;

	return true;
}

template<class Xtype>
bool list<Xtype>::pop_back()
{
	Iterator it(rear_element->pre);
	return erase(it);
}

template<class Xtype>
bool list<Xtype>::pop_front()
{
	Iterator it(front_element->next);
	return erase(it);
}

template<class Xtype>
inline void list<Xtype>::swap(list & x)
{
	int temp = num_of_elements;
	num_of_elements = x.num_of_elements;
	x.num_of_elements = temp;

	Node *temp_front, *temp_rear;

	temp_front = front_element;
	front_element = x.front_element;
	x.front_element = temp_front;

	temp_rear = rear_element;
	rear_element = x.rear_element;
	x.rear_element = temp_rear;
}

template<class Xtype>
inline void list<Xtype>::sort(int comp(Xtype &, Xtype &))
{
	int size = num_of_elements;
	Xtype *temp = new (std::nothrow) Xtype[size];
	if (!temp) {
		exit(-1);
	}

	Iterator it = this->begin();
	for (int i = 0; i < size; i++) {
		temp[i] = (*it);
		this->erase(it);
	}

	quickSort(temp, 0, size - 1, comp);

	for (int i = 0; i < size; i++) {
		this->push_back(temp[i]);
	}
}

template<class Xtype>
inline void list<Xtype>::clear()
{
	Node *curr = rear_element->pre;
	while (!isFront(curr->pre)) {
		curr = curr->pre;
		delete curr->next;
	}
	front_element->next = rear_element;
	rear_element->pre = front_element;
}

template<class Xtype>
list<Xtype>::~list()
{
	this->clear();
	delete front_element;
	delete rear_element;
}

template<class Xtype>
void swap(Xtype* a, Xtype* b)
{
	Xtype t = *a;
	*a = *b;
	*b = t;
}

template<class Xtype>
int partition(Xtype arr[], int low, int high, int comp(Xtype &, Xtype &))
{
	Xtype pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (comp(arr[j], pivot) < 0)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
/*
template<class Xtype>
void quickSort(Xtype arr[], int low, int high, int comp(Xtype &, Xtype &))
{
	if (low < high)
	{
		int pi = partition(arr, low, high, comp);

		quickSort(arr, low, pi - 1, comp);
		quickSort(arr, pi + 1, high, comp);
	}
}
*/
template<class Xtype>
void quickSort(Xtype arr[], int l, int h, int comp(Xtype &, Xtype &))
{
	// Create an auxiliary stack 
	int *stack = new int[h - l + 1];

	// initialize top of stack 
	int top = -1;

	// push initial values of l and h to stack 
	stack[++top] = l;
	stack[++top] = h;

	// Keep popping from stack while is not empty 
	while (top >= 0) {
		// Pop h and l 
		h = stack[top--];
		l = stack[top--];

		// Set pivot element at its correct position 
		// in sorted array 
		int p = partition(arr, l, h, comp);

		// If there are elements on left side of pivot, 
		// then push left side to stack 
		if (p - 1 > l) {
			stack[++top] = l;
			stack[++top] = p - 1;
		}

		// If there are elements on right side of pivot, 
		// then push right side to stack 
		if (p + 1 < h) {
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}
}
