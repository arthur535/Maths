#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <stdexcept>

double getDeterminant(const std::vector<std::vector<double>> matrix) {
    if(matrix.size() != matrix[0].size()) {
        throw std::runtime_error("Matrix is not quadratic");
    }
    int dimension = matrix.size();

    if(dimension == 0) {
        return 1;
    }

    if(dimension == 1) {
        return matrix[0][0];
    }
    if(dimension == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double result = 0;
    int sign = 1;
    for(int i = 0; i < dimension; i++) {

        std::vector<std::vector<double>> subVect(dimension - 1, std::vector<double> (dimension - 1));
        for(int m = 1; m < dimension; m++) {
            int z = 0;
            for(int n = 0; n < dimension; n++) {
                if(n != i) {
                    subVect[m-1][z] = matrix[m][n];
                    z++;
                }
            }
        }

        //recursive call
        result = result + sign * matrix[0][i] * getDeterminant(subVect);
        sign = -sign;
    }

    return result;
}

std::vector<std::vector<double>> getTranspose(const std::vector<std::vector<double>> matrix1) {
    std::vector<std::vector<double>> solution(matrix1[0].size(), std::vector<double> (matrix1.size()));
    for(size_t i = 0; i < matrix1.size(); i++) {
        for(size_t j = 0; j < matrix1[0].size(); j++) {
            solution[j][i] = matrix1[i][j];
        }
    }
    return solution;
}

std::vector<std::vector<double>> getCofactor(const std::vector<std::vector<double>> matrix) {
    if(matrix.size() != matrix[0].size()) {
        throw std::runtime_error("Matrix is not quadratic");
    }

    std::vector<std::vector<double>> solution(matrix.size(), std::vector<double> (matrix.size()));
    std::vector<std::vector<double>> subVect(matrix.size() - 1, std::vector<double> (matrix.size() - 1));

    for(std::size_t i = 0; i < matrix.size(); i++) {
        for(std::size_t j = 0; j < matrix[0].size(); j++) {

            int p = 0;
            for(size_t x = 0; x < matrix.size(); x++) {
                if(x == i) {
                    continue;
                }
                int q = 0;

                for(size_t y = 0; y < matrix.size(); y++) {
                    if(y == j) {
                        continue;
                    }

                    subVect[p][q] = matrix[x][y];
                    q++;
                }
                p++;
            }
            solution[i][j] = pow(-1, i + j) * getDeterminant(subVect);
        }
    }
    return solution;
}

std::vector<std::vector<double>> getInverse(const std::vector<std::vector<double>> matrix) {
    if(getDeterminant(matrix) == 0) {
        throw std::runtime_error("Determinant is 0");
    }
    double d = 1.0/getDeterminant(matrix);
    std::vector<std::vector<double>> solution(matrix.size(), std::vector<double> (matrix.size()));

    for(size_t i = 0; i < matrix.size(); i++) {
        for(size_t j = 0; j < matrix.size(); j++) {
            solution[i][j] = matrix[i][j] * d;
        }
    }

    return getTranspose(getCofactor(solution));
}

void printMatrix(const std::vector<std::vector<double>> matrix) {
    for(std::size_t i = 0; i < matrix.size(); i++) {
        for(std::size_t j = 0; j < matrix[0].size(); j++) {
            std::cout << std::setw(8) << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}
int main() {
    std::vector<std::vector<double>> matrix(3, std::vector<double> (3));
    matrix = {
        {6,2,-3},
        {-1,5,1},
        {0,2,4}
    };

    printMatrix(getInverse(matrix));
}
