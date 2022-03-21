#include <vector>
#include <iomanip>
#include <iostream>
#pragma once

class ExtendedMatrix {
	public:
		int	rowsAmount = 0;
		int	columnsAmount = 0;
		std::vector<std::vector<double>> table;
		ExtendedMatrix(int, int, std::vector<std::vector<double>>);
		ExtendedMatrix();
		void printExtendedMatrix();
		void printMatrixAsTriangulated();
		void swapRows(int, int);
};

ExtendedMatrix::ExtendedMatrix(int rowsAmount, int columnsAmount, std::vector<std::vector<double>> table) {
	this->rowsAmount = rowsAmount;
	this->columnsAmount = columnsAmount;
	this->table = table;
}

ExtendedMatrix::ExtendedMatrix() {
}

void ExtendedMatrix::printExtendedMatrix() {
	std::cout << "Matrix: " << std::endl;
	for (int i = 0; i < rowsAmount; i++) {
		for (int j = 0; j < columnsAmount; j++) {
			std::cout << std::fixed;
			std::cout << std::setprecision(3);
			if (j == columnsAmount - 1) {
				std::cout << " | ";
			}
			std::cout << table.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}
}

void ExtendedMatrix::printMatrixAsTriangulated() {
	std::cout << "Triangulated matrix: " << std::endl;
	for (int i = 0; i < rowsAmount; i++) {
		for (int j = 0; j < columnsAmount; j++) {
			std::cout << std::fixed;
			std::cout << std::setprecision(3);
			if (j == columnsAmount - 1) {
				std::cout << " | ";
			}
			std::cout << table.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}
}

void ExtendedMatrix::swapRows(int i, int j) {
	std::vector<double> temp = this->table.at(i);
	this->table.at(i) = this->table.at(j);
	this->table.at(j) = temp;
}