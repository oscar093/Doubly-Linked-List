///*
// * ListIter.h
// *
// *  Created on: Dec 5, 2018
// *      Author: Oscar Arréhn Ågren
// */
//
//#ifndef LISTITER_H_
//#define LISTITER_H_
//
//
//#include <iostream>
//#include <cstring>
//#include <cassert>
//#include "List.h"
//
////template <typename T>
////class ListIter {
////	typedef T value_type;
////	typedef T& reference;
////	typedef std::random_access_iterator_tag iterator_category; //Denna kanske ska anpassas till Lista iom den är från Vector.
////	typedef signed int difference_type;
////	typedef T* pointer;
//////	pointer ptr;
////public:
//////	ListIter(List<T>::Node<T>* p);  //Enl. uppgiftsbeskrivning: ListIter(Node<T>* p);
////	ListIter();
////	ListIter(const ListIter& other);
////	ListIter& operator=(const ListIter&
////	other);
////	T & operator*();
////	T* operator->();
////	ListIter& operator++();
////	ListIter& operator--();
////	ListIter operator++(int);
////	ListIter operator--(int);
////	template <class TT> friend bool operator==(const ListIter& 	lhs, const ListIter& rhs);
////	template <class TT> friend bool operator!=(const ListIter& 	lhs, const ListIter& rhs);
////};
//
///************************************************************************************************/
//
////	ListIter(Node<T>* p);  //Enl. uppgiftsbeskrivning: ListIter(Node<T>* p);
//template<class T>
//List<T>::ListIter<T>::ListIter() {
//
//}
//
//template<class T>
//ListIter<T>::ListIter(const ListIter& other) {
//
//}
//
//template<class T>
//ListIter<T>& ListIter<T>::operator=(const ListIter<T>& other) {
//
//}
//
//template<class T>
//T & ListIter<T>::operator*() {
//
//}
//
//template<class T>
//T* ListIter<T>::operator->() {
//
//}
//
//template<class T>
//ListIter<T>& ListIter<T>::operator++() {
//
//}
//
//template<class T>
//ListIter<T>& ListIter<T>::operator--() {
//
//}
//
//template<class T>
//ListIter<T> ListIter<T>::operator++(int) {
//
//}
//
//template<class T>
//ListIter<T> ListIter<T>::operator--(int) {
//
//}
//
//template<class T>
//bool operator==(const ListIter<T>& lhs,	const ListIter<T>& rhs) {
//
//}
//
//template<class T>
//bool operator!=(const ListIter<T>& lhs,	const ListIter<T>& rhs) {
//
//}
//
//#endif /* LISTITER_H_ */
