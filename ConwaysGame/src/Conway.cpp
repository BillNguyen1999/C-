#include "Conway.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>

Conway::Conway(){

}

Conway::Conway(std::string input_file) {
	std::vector<std::vector<bool> > temp;

	std::ifstream file;
	file.open(input_file);
	if (!file) { throw std::invalid_argument("unable to open file"); }
	char word;
	for(int i = 0; i < 7; i++) {
		std::vector<bool> temp2;
		for(int j = 0; j < 7; j++) {
			file >> word;
			if(word == 'o') {
				temp2.push_back(false);
			} else if(word == 'x') {
				temp2.push_back(true);
			}
		}
		temp.push_back(temp2);
	}
	file.close();
	// for(int j = 0; j < i; j++) {
	// 	std::vector<bool> temp2;
	// 	for(int k = 0; k < i; k++) {
	// 		temp2.push_back(false);
	// 	}
	// 	temp.push_back(temp2);
	// }

	this->matrix = temp;
}



std::vector<std::vector<bool> > Conway::get_matrix() {
	if(matrix.size() != 7) { throw std::length_error("matrix has to be a 7 by 7 matrix"); }
	return matrix;
}

bool Conway::get_value(int row, int column) {
	if((row < 0 || row > 6) || (column < 0 || column > 6)) { throw std::out_of_range("out of range");}
	return matrix[row][column];
}

void Conway::set_value(int row, int column) {
	if((row < 0 || row > 6) || (column < 0 || column > 6)) { throw std::out_of_range("out of range");}
	matrix[row][column] = true;
}

void Conway::remove_value(int row, int column) {
	if((row < 0 || row > 6) || (column < 0 || column > 6)) { throw std::out_of_range("out of range");}
	matrix[row][column] = false;
}

void Conway::next() {
	if(matrix.size() != 7) { throw std::length_error("matrix has to be a 7 by 7 matrix"); }
	std::vector<std::vector<bool> > temp(matrix);
	for(int i = 0; i < matrix.size(); i++) {
		for(int j = 0; j < matrix.size(); j++) {
			int counter = 0;
			if(i == 0 && j == 0) {
				if(temp[i][matrix.size()-1] == true){ counter++; }
				if(temp[matrix.size()-1][i] == true) { counter++; }
				if(temp[matrix.size()-1][matrix.size()-1] == true) { counter++; }
				if(temp[i][j+1] == true) { counter++; }
				if(temp[i+1][j] == true) { counter++;}
				if(temp[i+1][j+1] == true) {counter++;}
				if(temp[matrix.size()-1][j+1] == true) {counter++;}
				if(temp[i+1][matrix.size()-1] == true) {counter++;}
			} else if(i == 0 && j == matrix.size() - 1) {
				if(temp[i][0] == true){ counter++; }
				if(temp[matrix.size()-1][i] == true) { counter++; }
				if(temp[matrix.size()-1][matrix.size()-1] == true) { counter++; }
				if(temp[i][j-1] == true) { counter++; }
				if(temp[i+1][j] == true) { counter++;}
				if(temp[i+1][j-1] == true) {counter++;}
				if(temp[i+1][0] == true) {counter++;}
				if(temp[matrix.size()-1][j-1] == true) {counter++;}
			} else if(i == matrix.size() - 1 && j == matrix.size() - 1) {
				if(temp[0][0] == true){ counter++; }
				if(temp[matrix.size()-1][0] == true) { counter++; }
				if(temp[0][matrix.size()-1] == true) { counter++; }
				if(temp[i][j-1] == true) { counter++; }
				if(temp[i-1][j] == true) { counter++;}
				if(temp[i-1][j-1] == true) {counter++;}
				if(temp[i-1][0] == true) {counter++;}
				if(temp[0][j-1] == true) {counter++;}
			} else if(i == matrix.size() - 1 && j == 0) {
				if(temp[0][0] == true){ counter++; }
				if(temp[matrix.size()-1][matrix.size()-1] == true) { counter++; }
				if(temp[0][matrix.size()-1] == true) { counter++; }
				if(temp[i][j+1] == true) { counter++; }
				if(temp[i-1][j] == true) { counter++;}
				if(temp[i-1][j+1] == true) {counter++;}
				if(temp[0][j+1] == true) {counter++;}
				if(temp[i-1][i] == true) {counter++;}
			} else if((j == 0) && (i > 0 && i < matrix.size() - 1)) {
				if(temp[i][matrix.size()-1] == true) {counter++;}
				if(temp[i+1][matrix.size()-1] == true) {counter++;}
				if(temp[i-1][matrix.size()-1] == true) {counter++;}
				if(temp[i-1][j] == true) { counter++; }
				if(temp[i-1][j+1] == true) { counter++; }
				if(temp[i][j+1] == true) { counter++; }
				if(temp[i+1][j] == true) { counter++; }
				if(temp[i+1][j+1] == true) { counter++; }
			} else if((i == 0) && (j > 0 && j < matrix.size() - 1)) {
				if(temp[matrix.size()-1][j] == true) {counter++;}
				if(temp[matrix.size()-1][j-1] == true) {counter++;}
				if(temp[matrix.size()-1][j+1] == true) {counter++;}
				if(temp[i][j+1] == true) { counter++; }
				if(temp[i][j-1] == true) { counter++; }
				if(temp[i+1][j] == true) { counter++; }
				if(temp[i+1][j-1] == true) { counter++; }
				if(temp[i+1][j+1] == true) { counter++; }
			} else if(i == matrix.size() - 1 && (j > 0 && j < matrix.size() - 1)) {
				if(temp[0][j] == true) {counter++;}
				if(temp[0][j-1] == true) {counter++;}
				if(temp[0][j+1] == true) {counter++;}
				if(temp[i][j+1] == true) { counter++; }
				if(temp[i][j-1] == true) { counter++; }
				if(temp[i-1][j] == true) { counter++; }
				if(temp[i-1][j-1] == true) { counter++; }
				if(temp[i-1][j+1] == true) { counter++; }
			} else if(j == matrix.size() - 1 && (i > 0 && i < matrix.size() - 1)) {
				if(temp[i][0] == true) {counter++;}
				if(temp[i+1][0] == true) {counter++;}
				if(temp[i-1][0] == true) {counter++;}
				if(temp[i-1][j] == true) { counter++; }
				if(temp[i-1][j-1] == true) { counter++; }
				if(temp[i][j-1] == true) { counter++; }
				if(temp[i+1][j-1] == true) { counter++; }
				if(temp[i+1][j] == true) { counter++; }
			} else {
				if(temp[i][j+1] == true) { counter++; }
				if(temp[i][j-1] == true) { counter++; }
				if(temp[i+1][j] == true) { counter++; }
				if(temp[i-1][j] == true) { counter++; }
				if(temp[i+1][j-1] == true) { counter++; }
				if(temp[i+1][j+1] == true) { counter++; }
				if(temp[i-1][j-1] == true) { counter++; }
				if(temp[i-1][j+1] == true) { counter++; }
				
			}

			if(temp[i][j] == true && (counter > 3 || counter < 2)) {
					matrix[i][j] = false;
			} else if(temp[i][j] == false && counter == 3) {
					matrix[i][j] = true;
			}
		

		}
			
	}
}

void Conway::output_graphic() {
	std::ofstream file;
	file.open("src/output.txt");
	if (!file) { throw std::invalid_argument("unable to create file"); }
	//char word;
	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < 7; j++) {
			if(matrix[i][j] == true) {
				file << "x ";
			} else if(matrix[i][j] == false) {
				file << "o ";
			}
		}
		file<<"\n";
	}
	file.close();
}

// int main() {
// 	Conway hello("input.txt");
// 	// hello.set_value(2, 4);
// 	// hello.set_value(3, 4);
// 	// hello.set_value(4, 4);
// 	// std::cout<<hello.get_matrix().size()<<"\n";
// 	// std::cout<<hello.get_matrix()[2][4]<<"\n";
// 	// hello.next();
// 	hello.remove_value(6, 0);
// 	hello.output_graphic();
// 	// hello.next();
// 	std::cout<<hello.get_matrix()[6][0]<<"\n";
// 	return 0;
// }
