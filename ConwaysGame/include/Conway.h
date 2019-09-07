/**
 * \file Conway.h
 * \author Bill Nguyen
 * \brief program of conway's game of life 
 */

#include <vector>
#include <string>


/**
 * \brief Class that represents the 7 by 7 matrix for Conway's game of life
 */
class Conway {
	private:
		std::vector<std::vector<bool> > matrix;
	public:
		
		Conway();

		/**
		 * \brief reads the input file and makes a 7 by 7 matrix
		 * \param input_file is a string that represents the name of the file you want to read and turn into a matrix
		 * \details To add on to what I said there is also an exception in the case where the file cannot be read
		 */
		Conway(std::string input_file);

		/**
		 * \brief gets the matrix which is a vector that contains 7 vectors of type bool
		 * \returns a vector that contains 7 vectors of type bool that represents a matrix and the board of the game
		 * \details the length of the vector is 7 and each vector that inside has a length of 7
		 */
		std::vector<std::vector<bool> > get_matrix();

		/**
		 * \brief gets the specific value of the indicated point in the matrix
		 * \param row is type integer and indicates the desired row the user wants in the matrix
		 * \param column is type integer and indicates the desired column the user wants in the matrix
		 * \returns a boolean value in which true means there is a value in the indicated point while false means the point is empty
		 * \details an exception is raised if the row or columns are not in the desired range
		 */
		bool get_value(int row, int column);	

		/**
		 * \brief generates the next iteration of the game and updates the matrix to this specific iteration
		 */
		void next();

		/**
		 * \brief sets the specific value of the indicated point in the matrix to true
		 * \param row is type integer and indicates the desired row the user wants in the matrix
		 * \param column is type integer and indicates the desired column the user wants in the matrix
		 * \details an exception is raised if the row or columns are not in the desired range
		 */
		void set_value(int row, int column);

		/**
		 * \brief sets the specific value of the indicated point in the matrix to false
		 * \param row is type integer and indicates the desired row the user wants in the matrix
		 * \param column is type integer and indicates the desired column the user wants in the matrix
		 * \details an exception is raised if the row or columns are not in the desired range
		 */
		void remove_value(int row, int column);

		/**
		 * \brief puts the current matrix into a textfile called output.txt and in the textfile there will be a 7 by 7 matrix that represents the board of the game
		 * \details an exception is raised if the new created file cannot be written to
		 */
		void output_graphic(); 

};

