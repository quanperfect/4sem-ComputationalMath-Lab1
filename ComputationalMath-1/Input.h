#pragma once
#include "ExtendedMatrix.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>

class Input {
	public:
		int inputType = 0;
		ExtendedMatrix takeInput();
		ExtendedMatrix takeCmdInput();
		ExtendedMatrix takeFileInput();
		ExtendedMatrix takeRandomInput();
		int takeMatrixSizeCmdInput();
		int takeMatrixSizeFileInput(std::string);
		int takeMethodIdInput();
	private:
		std::vector<double> validateStringRow(std::string, int);
};

ExtendedMatrix Input::takeInput() {
	ExtendedMatrix matrix;
	std::cout << "There are 3 input methods available: 1 - cmd input, 2 - file input, 3 - random generation." << std::endl;
	inputType = takeMethodIdInput();

	switch (inputType) {
		case 1:
			matrix = takeCmdInput();
			break;
		case 2:
			matrix = takeFileInput();
			break;
		case 3:
			matrix = takeRandomInput();
			break;
		default: 
			std::cout << "Wrong input type in input class. EXIT" << std::endl;
			exit(1);
			break;
	}

	return matrix;
}

ExtendedMatrix Input::takeCmdInput() {
	ExtendedMatrix matrix;

	matrix.rowsAmount = takeMatrixSizeCmdInput();
	matrix.columnsAmount = matrix.rowsAmount + 1;

	std::cout << "Enter matrix (extended): " << std::endl;
	for (int i = 0; i < matrix.rowsAmount; i++) {
		//matrix.table.push_back(std::vector<double>());
		bool rowValid = true;
		
		std::string inputString;
		std::getline(std::cin, inputString);
		std::vector<double> inputtedRow = validateStringRow(inputString, matrix.columnsAmount);
		if (inputtedRow.size() == matrix.columnsAmount) {
			matrix.table.push_back(inputtedRow);
		}
		else {
			std::cout << "The row input was invalid. Please repeat your input." << std::endl;
			i--;
		}

	}

	return matrix;
}

ExtendedMatrix Input::takeFileInput() {
	ExtendedMatrix matrix;
	std::ifstream infile("input.txt");
	int matrixSize = 0;
	std::string matrixSizeString;
	std::getline(infile, matrixSizeString);
	matrixSize = takeMatrixSizeFileInput(matrixSizeString);

	matrix.rowsAmount = matrixSize;
	matrix.columnsAmount = matrixSize +1;
	//std::cout << "file matrix size: " << matrixSize << std::endl;

	bool eofReachedPreviously = false;

	for (int i = 0; i < matrix.rowsAmount; i++) {
		//matrix.table.push_back(std::vector<double>());
		bool rowValid = true;

		std::string inputString;

		if (!infile.eof() && !eofReachedPreviously) {
			std::getline(infile, inputString);
			//std::cout << "inputString: " << inputString << std::endl;
			std::vector<double> inputtedRow = validateStringRow(inputString, matrix.columnsAmount);
			if (inputtedRow.size() == matrix.columnsAmount) {
				matrix.table.push_back(inputtedRow);
			}
			else {
				std::cout << "This row from input file is invalid: " << inputString << std::endl;
				i--;
			}
		}
		else {
			std::cout << "Not all rows were filled by file input. Please enter " << matrix.rowsAmount - i << " more rows manually." << std::endl;
			std::getline(std::cin, inputString);
			//std::cout << "inputString: " << inputString << std::endl;
			std::vector<double> inputtedRow = validateStringRow(inputString, matrix.columnsAmount);
			if (inputtedRow.size() == matrix.columnsAmount) {
				matrix.table.push_back(inputtedRow);
			}
			else {
				std::cout << "The row input was invalid. Please repeat your input." << std::endl;
				i--;
			}
		}
	}

	return matrix;
}

ExtendedMatrix Input::takeRandomInput() {
	ExtendedMatrix matrix;

	int matrixSize = takeMatrixSizeCmdInput();
	matrix.rowsAmount = matrixSize;
	matrix.columnsAmount = matrixSize + 1;


	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(-100, 100);

	for (int i = 0; i < matrix.rowsAmount; i++) {
		matrix.table.push_back(std::vector<double>());
		for (int j = 0; j < matrix.columnsAmount; j++) {
			matrix.table.at(i).push_back(distribution(generator));
		}
	}


	return matrix;
}	

int Input::takeMethodIdInput() {
	int methodId;
	while (true) {
		std::cout << "Input method number: ";
		std::string methodIdString;
		std::getline(std::cin, methodIdString);
		//std::cout << "Method Number String Input: " << methodIdString << std::endl;
		bool firstsymbolisspace = true;
		while (firstsymbolisspace) {
			firstsymbolisspace = false;
			if (!methodIdString.empty() && std::isspace(methodIdString[0])) {
				methodIdString.erase(0, 1);
				firstsymbolisspace = true;
			}
		}
		bool lastsymbolisspace = true;
		while (lastsymbolisspace) {
			lastsymbolisspace = false;
			if (!methodIdString.empty() && std::isspace(methodIdString[methodIdString.size() - 1])) {
				methodIdString.erase(methodIdString.size() - 1, 1);
				lastsymbolisspace = true;
			}
		}

		if (methodIdString.empty()) {
			std::cout << "Empty method number, repeat your input. Method number is 1 integer number from 1 to 3. " << std::endl;
			continue;
		}

		for (int i = 1; i < methodIdString.size(); i++) {
			switch (methodIdString[i]) {
			case '0':
				break;
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case '6':
				break;
			case '7':
				break;
			case '8':
				break;
			case '9':
				break;
			default:
				std::cout << "Bad characters in method number, repeat your input. Matrix size is 1 integer number from 1 to 3." << std::endl;
				return takeMethodIdInput();

			}
		}

		try {
			methodId = stoi(methodIdString);
			//std::cout << "MethodIdInput was taken: " << methodId << std::endl;
			break;
		}
		catch (std::exception const& e) {
			std::cout << "Bad method number input, repeat your input. Method number is 1 integer number from 1 to 3." << std::endl;
		}
	}

	return methodId;
}

int Input::takeMatrixSizeFileInput(std::string matrixSizeString) {
	int matrixSize;

	bool firstsymbolisspace = true;
	while (firstsymbolisspace) {
		firstsymbolisspace = false;
		if (!matrixSizeString.empty() && std::isspace(matrixSizeString[0])) {
			matrixSizeString.erase(0, 1);
			firstsymbolisspace = true;
		}
	}
	bool lastsymbolisspace = true;
	while (lastsymbolisspace) {
		lastsymbolisspace = false;
		if (!matrixSizeString.empty() && std::isspace(matrixSizeString[matrixSizeString.size() - 1])) {
			matrixSizeString.erase(matrixSizeString.size() - 1, 1);
			lastsymbolisspace = true;
		}
	}

	if (matrixSizeString.empty()) {
		std::cout << "Empty matrix size, repeat your input. Matrix size is 1 integer number. " << std::endl;
		return takeMatrixSizeCmdInput();
	}

	for (int i = 1; i < matrixSizeString.size(); i++) {
		switch (matrixSizeString[i]) {
		case '0':
			break;
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			break;
		case '8':
			break;
		case '9':
			break;
		case '-':
			break;
		case '.':
			break;
		default:
			std::cout << "Bad characters in matrixSize, repeat your input. Matrix size is 1 integer number." << std::endl;
			return takeMatrixSizeCmdInput();

		}
	}

	try {
		matrixSize = stoi(matrixSizeString);
		//std::cout << "MatrixSizeInput was taken: " << matrixSize << std::endl;
	}
	catch (std::exception const& e) {
		std::cout << "Bad matrixSize input, repeat your input. Matrix size is 1 integer number." << std::endl;
		return takeMatrixSizeCmdInput();
	}

	return matrixSize;
}

int Input::takeMatrixSizeCmdInput() {
	int matrixSize;
	while (true) {
		std::cout << "Matrix size: ";
		std::string matrixSizeString;
		std::getline(std::cin, matrixSizeString);
		//std::cout << "Matrix Size String Input: " << matrixSizeString << std::endl;
		bool firstsymbolisspace = true;
		while (firstsymbolisspace) {
			firstsymbolisspace = false;
			if (!matrixSizeString.empty() && std::isspace(matrixSizeString[0])) {
				matrixSizeString.erase(0, 1);
				firstsymbolisspace = true;
			}
		}
		bool lastsymbolisspace = true;
		while (lastsymbolisspace) {
			lastsymbolisspace = false;
			if (!matrixSizeString.empty() && std::isspace(matrixSizeString[matrixSizeString.size() - 1])) {
				matrixSizeString.erase(matrixSizeString.size() - 1, 1);
				lastsymbolisspace = true;
			}
		}

		if (matrixSizeString.empty()) {
			std::cout << "Empty matrix size, repeat your input. Matrix size is 1 integer number. " << std::endl;
			continue;
		}

		for (int i = 1; i < matrixSizeString.size(); i++) {
			switch (matrixSizeString[i]) {
				case '0':
					break;
				case '1':
					break;
				case '2':
					break;
				case '3':
					break;
				case '4':
					break;
				case '5':
					break;
				case '6':
					break;
				case '7':
					break;
				case '8':
					break;
				case '9':
					break;
				case '-':
					break;
				case '.':
					break;
				default:
					std::cout << "Bad characters in matrixSize, repeat your input. Matrix size is 1 integer number." << std::endl;
					return takeMatrixSizeCmdInput();

			}
		}

		try {
			matrixSize = stoi(matrixSizeString);
			//std::cout << "MatrixSizeInput was taken: " << matrixSize << std::endl;

			if (matrixSize <= 0) {
				std::cout << "Bad matrixSize input, repeat your input. Matrix size is 1 integer number bigger than zero." << std::endl;
				continue;
			}
			break;
		}
		catch (std::exception const& e) {
			std::cout << "Bad matrixSize input, repeat your input. Matrix size is 1 integer number." << std::endl;
		}

	}

	return matrixSize;
}

std::vector<double> Input::validateStringRow(std::string inputString, int size) {
	//std::cout << "validateStringRow got string: " << inputString << std::endl;
	std::vector<double> result;
	bool nospacesfound = false;
	bool correctInput = true;

	bool firstsymbolisspace = true;
	while (firstsymbolisspace) {
		firstsymbolisspace = false;
		if (!inputString.empty() && std::isspace(inputString[0])) {
			inputString.erase(0,1);
			firstsymbolisspace = true;
		}
	}
	bool lastsymbolisspace = true;
	while (lastsymbolisspace) {
		lastsymbolisspace = false;
		if (!inputString.empty() && std::isspace(inputString[inputString.size()-1])) {
			inputString.erase(inputString.size()-1,1);
			lastsymbolisspace = true;
		}
	}

	if (inputString.size() < size * 2 - 1) {
		std::cout << "Incorrect row input, please repeat your input." << std::endl;
		return std::vector<double>();
	}

	std::vector<int> spacesIndexes;
	spacesIndexes.push_back(-1);
	for (int i = 1; i < inputString.size(); i++) {
		if (std::isspace(inputString[i])) {
			nospacesfound = false;
			if (i < inputString.size()-1 && std::isspace(inputString[i+1])) {
				inputString.erase(i + 1,1);
				i--;
				continue;
			}
			else {
				spacesIndexes.push_back(i);
			}
		}
		else {
			switch (inputString[i]) {
				case '0':
					break;
				case '1':
					break;
				case '2':
					break;
				case '3':
					break;
				case '4':
					break;
				case '5': 
					break;
				case '6':
					break;
				case '7':
					break;
				case '8':
					break;
				case '9':
					break;
				case '.':
					break;
				case '-':
					break;
				default:
					std::cout << "Bad characters in row. All elements should be divided by space. Please repeat your input." << std::endl;
					return std::vector<double>();
			}
		}
	}
	//std::cout << "inputString: \"" << inputString << "\"" << std::endl;
	//std::cout << "parsing space indexes to doubles" << std::endl;
	for (int i = 0; i < spacesIndexes.size(); i++) {
		double value;
		int length = 1;
		if (i == spacesIndexes.size() - 1) {
			length = inputString.size() - (spacesIndexes.at(i) + 1);
		}
		else {
			length = spacesIndexes.at(i + 1) - (spacesIndexes.at(i) + 1);
		}
		//std::cout << "spaceIndex: " << spacesIndexes.at(i) << " ; length: " << length << std::endl;
		std::string valueString = inputString.substr(spacesIndexes.at(i) + 1, length);

		try {
			//std::cout << "trying to parse string: \"" << valueString << "\"" << std::endl;
			value = stod(valueString);
			result.push_back(value);
		} 
		catch (std::exception const& e) {
			std::cout << "Row input exception. Please repeat your row input." << std::endl;
			return std::vector<double>();
		}
	}

	return result;
}