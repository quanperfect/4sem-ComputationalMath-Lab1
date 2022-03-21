#pragma once
#include <vector>
#include <iostream>
#include "ExtendedMatrix.h"

class GaussianElimWithPivoting {
	public:
		GaussianElimWithPivoting(ExtendedMatrix);
		bool withDebugPrints = false;
		ExtendedMatrix defaultMatrix;
		ExtendedMatrix matrix;
		double determinant;
		std::vector<double> divergences;
		std::vector<double> solution;
		std::vector<double> solveSystem();

		int triangulate();
		double calculateDeterminant(int);
		std::vector<double> calculateSolution();
		std::vector<double> calculateDivergences();
};

GaussianElimWithPivoting::GaussianElimWithPivoting(ExtendedMatrix matrix) {
	this->matrix = matrix;
	this->defaultMatrix = matrix;
}

std::vector<double> GaussianElimWithPivoting::solveSystem() {

	//std::cout << "back test: " << matrix.table.at(1).back() << std::endl;
	int permutationsNumber = triangulate();

	this->matrix.printMatrixAsTriangulated();

	double determinant = calculateDeterminant(permutationsNumber);
	this->determinant = determinant;
	std::cout << "Determinant: " << determinant << std::endl;

	if (determinant == 0) {
		return std::vector<double>();
	}
	
	this->solution = calculateSolution();
	this->divergences = calculateDivergences();

	return solution;
}

int GaussianElimWithPivoting::triangulate() {
	int permutationsCounter = 0;
	//std::cout << "rowsAmount: " << matrix.rowsAmount << std::endl;
	//std::cout << "columnsAmount: " << matrix.columnsAmount << std::endl;

	for (int i = 0; i < matrix.rowsAmount - 1; i++) {

		int maxElementRow = i;

		for (int ii = i + 1; ii < matrix.rowsAmount; ii++) {
			//std::cout << "i: " << i << " ; ii: " << ii << std::endl;
			if (withDebugPrints) std::cout << "Comparing: " << std::abs(matrix.table.at(ii).at(i)) << " AND " << std::abs(matrix.table.at(maxElementRow).at(i)) << std::endl;
			if (std::abs(matrix.table.at(ii).at(i)) > std::abs(matrix.table.at(maxElementRow).at(i))) {
				maxElementRow = ii;
				//std::cout << "maxElementRow: " << maxElementRow << std::endl;
			}
		}

		if (maxElementRow != i) {
				matrix.swapRows(i, maxElementRow);
				permutationsCounter++;
		}

		//std::cout << "i iteration: " << i << std::endl;
		//matrix.printExtendedMatrix();



		if (withDebugPrints) matrix.printExtendedMatrix();
		if (withDebugPrints) std::cout << "(pivot zero check) table.at(" << i << ").at(" << i << "): " << matrix.table.at(i).at(i) << std::endl;
		if (matrix.table.at(i).at(i) != 0) {
			for (int ii = i + 1; ii < matrix.rowsAmount; ii++) {
				double coef = -matrix.table.at(ii).at(i) / matrix.table.at(i).at(i);
				if (withDebugPrints) std::cout << "double coef = -" << matrix.table.at(ii).at(i) << " / " << matrix.table.at(i).at(i) << std::endl;

				for (int jj = i; jj < matrix.columnsAmount-1; jj++) {
					if (withDebugPrints) std::cout << "table.at(" << ii << ").at(" << jj << ") = " << matrix.table.at(ii).at(jj) << " + " << coef << " * " << matrix.table.at(i).at(jj) << std::endl;
					matrix.table.at(ii).at(jj) = matrix.table.at(ii).at(jj) + coef * matrix.table.at(i).at(jj);
				}

				matrix.table.at(ii).back() = matrix.table.at(ii).back() + coef * matrix.table.at(i).back();
				if (withDebugPrints) std::cout << "table.at(" << ii << ").back() = " << matrix.table.back().at(ii) << " + " << coef << " * " << matrix.table.back().at(i) << std::endl;

			}
		}
		if (withDebugPrints) matrix.printExtendedMatrix();

	}

	return permutationsCounter;
}

double GaussianElimWithPivoting::calculateDeterminant(int permutationsNumber) {
	double det = 1;
	for (int i = 0; i < matrix.rowsAmount; i++) {
		det *= matrix.table.at(i).at(i);
	}
	
	if (permutationsNumber % 2 == 0) {
		return det;
	}
	else {
		return -det;
	}
}

std::vector<double> GaussianElimWithPivoting::calculateSolution() {
	std::vector<double> solution;
	for (int i = 0; i < matrix.rowsAmount; i++) {
		solution.push_back(0);
	}

	for (int i = matrix.rowsAmount - 1; i >= 0; i--) {
		double alreadyKnownVarsCalculation = 0;
		double coef = 0;
		double variable = 0;

		for (int j = i + 1; j < matrix.rowsAmount; j++) {
			coef = matrix.table.at(i).at(j);
			variable = solution.at(j);
			alreadyKnownVarsCalculation += coef * variable;
		}

		double freeCoef = matrix.table.at(i).back();
		coef = matrix.table.at(i).at(i);
		solution.at(i) = (freeCoef - alreadyKnownVarsCalculation) / coef;
	}

	return solution;
}

std::vector<double> GaussianElimWithPivoting::calculateDivergences() {
	std::vector<double> divergences;

	for (int i = 0; i < solution.size(); i++) {
		double freeCoef = defaultMatrix.table.at(i).back();
		double equationLeft = 0;
		for (int j = 0; j < defaultMatrix.rowsAmount; j++) {
			equationLeft += defaultMatrix.table.at(i).at(j) * solution.at(j);
		}

		divergences.push_back(equationLeft - freeCoef);
	}

	return divergences;
}

