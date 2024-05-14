#ifndef ART_MATH_H
#define ART_MATH_H

#include <vector>
#include <iostream>
using namespace std;

class Matrix {
public:
    typedef std::vector<std::vector<double>> MatrixVector;

    Matrix() = default;
    Matrix(const MatrixVector&);

    void setMatrix(const MatrixVector&);
    MatrixVector getMatrix() const;
    MatrixVector getTranspose() const;
    MatrixVector getInverse() const;
    void printMatrix() const;
    void printTransposed() const;
    bool isSquare() const;
    double determinant() const;

    static MatrixVector getTranspose(const MatrixVector&);
    static double determinant(const MatrixVector&);
    static MatrixVector getInverse(const MatrixVector&);
    static MatrixVector getMultiplication(const MatrixVector&, const MatrixVector&);
    static MatrixVector getAddition(const MatrixVector&, const MatrixVector&);
    
    MatrixVector operator* (const MatrixVector&);
    MatrixVector operator+ (const MatrixVector&);
    Matrix operator* (const Matrix&);
    Matrix operator+ (const Matrix&);
    ~Matrix(){};
private:
    int n; // rows
    int m; // columns
    bool _isSquare;
    MatrixVector _matrix;
    MatrixVector _transposed;
    
    static MatrixVector getCofactor(const MatrixVector&);
};
#endif