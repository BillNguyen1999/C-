// Implementation here
#include "Stack.h"
#include "CardTypes.h"
#include <vector>
#include <iostream>
#include <stdexcept>

//using namespace std;

template <class T>
Stack<T>::Stack(){

}

template <class T>
Stack<T>::Stack(std::vector<T> S){
	this->S = S;
}

template<class T>
Stack<T> Stack<T>::push(T e){
	std::vector<T> temp(this->S);
	temp.push_back(e);
	return Stack(temp);
}

template<class T>
Stack<T> Stack<T>::pop(){
	if(this->S.empty()) throw std::out_of_range("Stack is empty");
	std::vector<T> temp(this->S);
	temp.erase(temp.end()-1);
	return Stack(temp);
}

template<class T>
T Stack<T>::top(){
	if(this->S.empty()) throw std::out_of_range("Stack is empty");
	return this->S.back();
}

template<class T>
unsigned int Stack<T>::size(){
	return this->S.size();
}

template<class T>
std::vector<T> Stack<T>::toSeq(){
	return this->S;
}


// Keep this at bottom
template class Stack<CardT>;
