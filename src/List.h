/*
 * List.h
 *
 *  Created on: Dec 5, 2018
 *      Author: Oscar A. Ågren
 */

#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>

template<class T>
class List;

template <typename TT>
	class ListIter;

template<class TT>
	class Node;

template<class T>
class List {
public:
	template<class TT>
	class Node;

	template<class TT>
	class Link {
		friend class List<T> ;
		Link* _next, *_prev;
		Link()=default;
		Link<T>& operator=(const Link& other) {
			_next = other._next;
			_prev = other._prev;
			return *this;
		}

		Node<T>* Next() const {
			return static_cast<Node<T>*>(_next);
		}
		Node<T>* Prev() const{
			return static_cast<Node<T>*>(_prev);
		}

		void remove(){
			_next->_prev = _prev;
			_prev->_next = _next;
		}

		void insert(Link<T>* node){
			node->_next = this;
			node->_prev = _prev;
			_prev->_next = node;
			_prev = node;
		}

		virtual ~Link(){
		}
	};

	template<class TT>
	class Node: Link<T> {
		friend class List<T> ;
		T _data;
	public:
		Node(const T& data) :_data(data) {
		};
	};

	template <typename TT>
	class ListIter {
		typedef T value_type;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
		typedef signed int difference_type;
		typedef Link<T>* pointer;
	public:
		pointer ptr;
		ListIter(Node<T>* p){
			ptr = p;
		}

		ListIter(){
			ptr = nullptr;
		}

		ListIter(const ListIter& other){
			ptr = other.ptr;
		}

		ListIter& operator=(const ListIter& other){
			ptr = other.ptr;
			return *this;
		}

		T & operator*(){
			return static_cast<Node<T>*>(ptr)->_data;
		}

		T* operator->(){
			return &static_cast<Node<T>*>(ptr)->_data;
		}

		ListIter& operator++(){
			ptr = ptr->_next;
			return *this;
		}

		ListIter& operator--(){
			ptr = ptr->_prev;
			return *this;
		}

		ListIter operator++(int){
			ListIter<T> tmp = *this;
			ptr = ptr->_next;
			return tmp;
		}

		ListIter operator--(int){
			ListIter<T> tmp = *this;
			ptr = ptr->_prev;
			return tmp;
		}

		template <class TTT> friend bool operator==(const ListIter<TTT>& 	lhs, const ListIter<TTT>& rhs){
			return lhs.ptr == rhs.ptr;
		}

		template <class TTT> friend bool operator!=(const ListIter<TTT>& 	lhs, const ListIter<TTT>& rhs){
			return lhs.ptr != rhs.ptr;
		}
	};


	Link<T> _head;
	size_t sze;

	using iterator = ListIter<T>;

	~List();
	List();
	List(const List& other);
	List(List&& other);
	List(const char* other);
	List(const char& other);
	List& operator=(const List* other);
	List& operator=(const List& other);
	List& operator=(List&& other);
	T& front();  	//Ändrad till att vara const
	T& back();	//Ändrad till att vara const
	const T& front() const;  	//const version tillagd
	const T& back() const;	//const version tillagd
	iterator begin() const;
	iterator end() const;
	bool empty() const noexcept;
	size_t size() const noexcept;
	iterator insert(const iterator& pos, const T& value);
	iterator erase( const iterator& pos );
	void push_back(const T& value);
	void push_front(const T& value);
	void pop_back();
	void pop_front();
	template <class TT> friend bool operator==(const List<TT>& lhs, const List<TT>& other);
	template <class TT> friend std::ostream& operator<<(std::ostream& cout, const List& other);
	bool Invariant() const;
	void Check() const {
		assert(Invariant());
	}
};

/*****************************************************************************************/

template <class T>
List<T>::~List(){
	while(sze){
		pop_back();
	}
	Invariant();
}

template <class T>
List<T>::List(){
	_head._next = &_head;
	_head._prev = &_head;
	sze = 0;
	Invariant();
}

template <class T>
List<T>::List(const List& other){
	sze = 0;
	_head._next = &_head;
	_head._prev = &_head;
	for(iterator oit = other.begin(); oit != other.end(); ++oit){
		push_back(*oit);
	}
	Invariant();
}

template <class T>
List<T>::List(List&& other){
	if(other.sze > 0){
		sze = other.sze;
		_head._next = other._head._next;
		_head._prev = other._head._prev;
		_head._next->_prev = &_head;
		_head._prev->_next = &_head;

		other._head._next = &other._head;
		other._head._prev = &other._head;
		other.sze = 0;
	}else{
		sze = 0;
		_head._next = &_head;
		_head._prev = &_head;
	}
	Invariant();
}

template <class T>
List<T>::List(const char* other){
	sze = 0;
	_head._next = &_head;
	_head._prev = &_head;
	for(unsigned int i = 0; other[i] != '\0'; ++i){
		push_back(other[i]);
	}
	Invariant();
}

template <class T>
List<T>::List(const char& other){
	sze = 0;
	_head._next = &_head;
	_head._prev = &_head;
	const char* optr = &other;
	for(unsigned int i = 0; optr[i] != '\0'; ++i){
		push_back(optr[i]);
	}
}

template <class T>
List<T>& List<T>::operator=(const List* other){
	*this = *other;
	Invariant();
	return *this;
}


template <class T>
List<T>& List<T>::operator=(const List& other) {
		List<T> tmp = List<T>();
		for (iterator oit = other.begin(); oit != other.end(); ++oit) {
			tmp.push_back(*oit);
		}
		while(sze) {
			pop_back();
		}
		*this = std::move(tmp);
		Invariant();
		return *this;
}

template<class T>
List<T>& List<T>::operator=(List&& other) {
	if (this != &other) {
		while (sze) {
			pop_back();
		}

		if (other.sze > 0) {
			sze = other.sze;
			_head._next = other._head._next;
			_head._prev = other._head._prev;
			_head._next->_prev = &_head;
			_head._prev->_next = &_head;

			other._head._next = &other._head;
			other._head._prev = &other._head;
			other.sze = 0;
		} else {
			sze = 0;
			_head._next = &_head;
			_head._prev = &_head;
		}
	}
	Invariant();
	return *this;
}

template <class T>
T& List<T>::front(){
	return _head.Next()->_data;
}

template <class T>
T& List<T>::back(){
	return _head.Prev()->_data;
}

template <class T>
const T& List<T>::front() const{
	return _head.Next()->_data;
}

template <class T>
const T& List<T>::back() const{
	return _head.Prev()->_data;
}

template <class T>
typename List<T>::iterator List<T>::begin() const{
	iterator iter = List<T>::ListIter<T>(_head.Next());
	return iter;
}

template <class T>
typename List<T>::iterator List<T>::end() const{
	iterator iter = iterator(_head._next->Prev());
	return iter;
}

template <class T>
bool List<T>::empty() const noexcept{
	if(sze == 0){
		return true;
	}else{
		return false;
	}
}

template <class T>
size_t List<T>::size() const noexcept{
	return sze;
}

template <class T>
typename List<T>::iterator List<T>::insert(const iterator& pos, const T& value){
	Node<T> *node = new Node<T>(value);
	pos.ptr->insert(node);
	++sze;
	iterator it(node);
	Invariant();
	return it;
}

template <class T>
typename List<T>::iterator List<T>::erase( const iterator& pos ){
	typename List<T>::iterator it = List<T>::iterator(pos.ptr->Next());
	if(sze > 0){
		Node<T>* node = static_cast<Node<T>*>(pos.ptr);
		pos.ptr->remove();
		delete node;
		--sze;
	}
	Invariant();
	return it;
}

template <class T>
void List<T>::push_back(const T& value){
	Node<T> *node = new Node<T>(value);
	_head.insert(node);
	++sze;
	Invariant();
}

template <class T>
void List<T>::push_front(const T& value){
	Node<T> *node = new Node<T>(value);
	_head._next->insert(node);
	++sze;
	Invariant();
}

template <class T>
void List<T>::pop_back(){
	if(sze > 0){
		Node<T>* node = _head.Prev();
		_head._prev->remove();
		delete node;
		--sze;
	}
	Invariant();
}

template <class T>
void List<T>::pop_front(){
	if(sze >0){
		Node<T>* node = _head.Next();
		_head._next->remove();
		delete node;
		--sze;
	}
	Invariant();
}

template <typename TT>
bool operator==(const List<TT>& lhs, const List<TT>& other){
if(lhs.sze == other.sze){
	typename List<TT>::iterator o = other.begin();
	for(typename List<TT>::iterator l = lhs.begin(); l != lhs.end(); ++l){
		if(*l != *o){
			return false;
		}
		++o;
	}
	return true;
	}else{
		return false;
	}
}

template <typename TT>
bool operator!=(const List<TT>& lhs, const List<TT>& other){
	return !(lhs == other);
}

template <typename TT>
bool operator<(const List<TT>& lhs, const List<TT>& other){
	typename List<TT>::iterator oit = other.begin();
	typename List<TT>::iterator lit = lhs.begin();
	for(;lit != lhs.end() && oit != other.end(); ++lit){
		if(*lit != *oit){
			return *lit < *oit;
		}
		++oit;
	}
	if(!(oit == other.end()) && lit == lhs.end()){
		return true;
	}else if(oit == other.end() && !(lit == lhs.end())){
		return false;
	}
	return lhs != other;
}

template <typename TT>
bool operator>(const List<TT>& lhs, const List<TT>& other){
	return other < lhs;
}

template <typename TT>
bool operator<=(const List<TT>& lhs, const List<TT>& other){
	return lhs < other || lhs == other;
}

template <typename TT>
bool operator>=(const List<TT>& lhs, const List<TT>& other){
	return other < lhs || lhs == other;

}

template <class T>
std::ostream& operator<<(std::ostream& cout, const List<T>& other){
	for(typename List<T>::iterator it = other.begin(); it != other.end(); ++it){
		cout << *it;
	}
	cout << std::endl;
	return cout;
}

template <typename TT>
bool operator==(const List<TT>& lhs, const char* other){
	unsigned int i = 0;
	for(typename List<TT>::iterator l = lhs.begin(); l != lhs.end() && i < strlen(other); l++){
		if(*l != other[i]){
			return false;
		}
		++i;
	}
	return true;
}

template< class TT>
void swap(List<TT>& lhs, List<TT>& rhs ){
	std::swap(lhs, rhs);
	lhs.Invariant();
	rhs.Invariant();
}

template <class T>
bool List<T>::Invariant() const{
	assert(sze >= 0);
	if(sze == 0){
		assert(_head._next == &_head);
		assert(_head._prev == &_head);
	}else{
		assert(_head._next != &_head);
		assert(_head._prev != &_head);

		unsigned int i = 0;
		for(iterator it = begin(); it != end(); ++it){
			++i;
		}
		assert(sze == i);

		assert(begin().ptr->_prev == &_head);
		assert(end().ptr == &_head);
	}

	return true;
}

#endif /* LIST_H_ */
