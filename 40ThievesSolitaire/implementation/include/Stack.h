/**
 * \file CardStack.h
 * \author Bill Nguyen
 * \brief making a stack that will be used in the GameBoard
 */

#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>

//using namespace std;

/**
 * \brief Class that represents a stack
 * \details like a normal stack can push, pop, get the size, get the top value and convert stack to vector
 */
template <class T>
class Stack
{
	private:
		std::vector<T> S;
	public:

		Stack();
		/**
 		 * \brief Constructs a new stack
 		 * \param S is a vector of type T
 		 */
		Stack(std::vector<T> S);
		/**
 		 * \brief pushes given value to top of the stack
 		 * \param e is value of type T that is pushed onto the stack
 		 * \return returns a new stack that includes the parameter e
 		 */
		Stack push(T e);
		/**
 		 * \brief removes the top value of the stack
 		 * \return a new stack that excludes the top value of the stack
 		 */
		Stack pop();
		/**
 		 * \brief gets the top value of the stack
 		 * \return the top value of the stack and is type T
 		 */
		T top();
		/**
 		 * \brief gets the size/length of the stack
 		 * \return returns the size of stack as a natural number
 		 */
		unsigned int size();
		/**
 		 * \brief converts stack into a vector
 		 * \return returns the vector version of the stack
 		 */
        std::vector<T> toSeq();

};

#endif
