#include "Matrix.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    Matrix Artmatrix;
    std::vector<std::vector<double>> secondV = {{5},{6},{7}};
    Matrix second = secondV;
    std::vector<std::vector<double>> matrix = {
        {0, -5,-2},
        {5, 0, -2},
        {2, 2, 0}
    };
    
    Artmatrix.setMatrix(matrix);
    Artmatrix.printMatrix();
    std::cout << "Is square: " << Artmatrix.isSquare() << std::endl;
    std::cout << "Is Skew symmetric: " << Artmatrix.isSkewSymmetric() << std::endl;
    std::cout << std::endl;
    auto transposed = Artmatrix.getTranspose();
    for (const auto& row : transposed) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Determinant: " << Artmatrix.determinant() << std::endl;

    auto mul = Matrix::getMultiplication(matrix, secondV);
    for (const auto& row : mul) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}
