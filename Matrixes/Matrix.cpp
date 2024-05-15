#include "Matrix.h"
Matrix::Matrix(const MatrixVector& matrix){
    if(matrix.empty() or matrix[0].empty()) {
        std::cerr << "WARNING: given matrix is empty." << endl;
    }
    n = matrix.size();
    m = matrix[0].size();
    for(int i = 1; i < n; ++i){
        if(m != matrix[i].size()) {
            throw std::invalid_argument("Given data is not an matrix");
        }
    }
    _matrix = matrix;
    if(n == m) { _isSquare = true; }
    _transposed.reserve(m);
    for(int i = 0; i < m; ++i) {
        _transposed[i].resize(n);
    }
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            _transposed[j][i] = _matrix[i][j];
        }
    }
};
void Matrix::setMatrix(const MatrixVector& matrix){
    if(matrix.empty() or matrix[0].empty()) {
        std::cerr << "WARNING: given matrix is empty." << endl;
    }
    n = matrix.size();
    m = matrix[0].size();
    for(int i = 0; i < n; ++i){
        if(m != matrix[i].size()) {
            throw std::invalid_argument("Given data is not an matrix");
        }
    }
    _matrix = matrix;
    if(n == m) { _isSquare = true; }
    
    _transposed.clear();
    _transposed.reserve(m);
    for(int i = 0; i < m; ++i) {
        _transposed[i].resize(n);
    }
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            _transposed[j][i] = _matrix[i][j];
        }
    }
};

Matrix::MatrixVector Matrix::getMatrix() const {
    return _matrix;
}

void Matrix::printTransposed() const {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << _transposed[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void Matrix::printMatrix() const {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            std::cout << _matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}


bool Matrix::isSquare() const {
    return _isSquare;
}


Matrix::MatrixVector Matrix::getTranspose(const MatrixVector& matrix) {
    MatrixVector solution(matrix[0].size(), std::vector<double> (matrix.size()));
    for(size_t i = 0; i < matrix.size(); i++) {
        for(size_t j = 0; j < matrix[0].size(); j++) {
            solution[j][i] = matrix[i][j];
        }
    }
    return solution;
}


Matrix::MatrixVector Matrix::getTranspose() const {
    return _transposed;
}


double Matrix::determinant(const MatrixVector& matrix) {
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

        MatrixVector subVect(dimension - 1, std::vector<double> (dimension - 1));
        for(int m = 1; m < dimension; m++) {
            int z = 0;
            for(int n = 0; n < dimension; n++) {
                if(n != i) {
                    subVect[m-1][z] = matrix[m][n];
                    z++;
                }
            }
        }
        result = result + sign * matrix[0][i] * determinant(subVect);
        sign = -sign;
    }

    return result;
}

double Matrix::determinant() const {
    if(n != m) {
        throw std::runtime_error("Matrix is not quadratic");
    }
    if(n == 0) {
        return 1;
    }

    if(n == 1) {
        return _matrix[0][0];
    }
    if(n == 2) {
        return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
    }

    double result = 0;
    int sign = 1;
    for(int i = 0; i < n; i++) {
        MatrixVector subVect(n - 1, std::vector<double> (n - 1));
        for(int j = 1; j < n; j++) {
                int z = 0;
                for(int k = 0; k < n; k++) {
                    if(k != i) {
                        subVect[j-1][z] = _matrix[j][k];
                        z++;
                    }
                }
            }
        result = result + sign * _matrix[0][i] * determinant(subVect);
        sign = -sign;
    }
    return result;
}

Matrix::MatrixVector Matrix::getInverse(const MatrixVector& matrix) {
    if(determinant(matrix) == 0) {
        throw std::runtime_error("Determinant is 0");
    }
    double d = 1.0/determinant(matrix);
    MatrixVector solution(matrix.size(), std::vector<double> (matrix.size()));

    for(size_t i = 0; i < matrix.size(); i++) {
        for(size_t j = 0; j < matrix.size(); j++) {
            solution[i][j] = matrix[i][j] * d;
        }
    }
    return getTranspose(getCofactor(solution));
}


Matrix::MatrixVector Matrix::getInverse() const {
    if(determinant(_matrix) == 0) {
        throw std::runtime_error("Determinant is 0");
    }
    double d = 1.0/determinant(_matrix);
    MatrixVector solution(_matrix.size(), std::vector<double> (_matrix.size()));

    for(size_t i = 0; i < _matrix.size(); i++) {
        for(size_t j = 0; j < _matrix.size(); j++) {
            solution[i][j] = _matrix[i][j] * d;
        }
    }
    return getTranspose(getCofactor(solution));
}


Matrix::MatrixVector Matrix::getCofactor(const MatrixVector& matrix) {
    if(matrix.size() != matrix[0].size()) {
        throw std::runtime_error("Matrix is not quadratic");
    }

    MatrixVector solution(matrix.size(), std::vector<double> (matrix.size()));
    MatrixVector subVect(matrix.size() - 1, std::vector<double> (matrix.size() - 1));

    for(std::size_t i = 0; i < matrix.size(); i++) {
        for(std::size_t j = 0; j < matrix[0].size(); j++) {
            int p = 0;
            for(size_t x = 0; x < matrix.size(); x++) {
                if(x == i) { continue; }
                int q = 0;

                for(size_t y = 0; y < matrix.size(); y++) {
                    if(y == j) { continue; }
                    subVect[p][q] = matrix[x][y];
                    q++;
                }
                p++;
            }
            solution[i][j] = pow(-1, i + j) * determinant(subVect);
        }
    }
    return solution;
}

Matrix::MatrixVector Matrix::operator*(const MatrixVector& matrix) {
    long r = matrix.size();
    long c = matrix[0].size();
    if(m != r){ throw std::invalid_argument("no viable sizes");}
    MatrixVector mulVector(n, vector<double>(c));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < c; ++j) {
            mulVector[i][j]=0;
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < c; ++j){
            for(int k = 0; k < m; ++k) {
                mulVector[i][j] += _matrix[i][k] * matrix[k][j];
            }
        }
    }
    return mulVector;
}

Matrix Matrix::operator*(const Matrix& matrix) {
    MatrixVector matrixV = matrix.getMatrix();
    long r = matrixV.size();
    long c = matrixV[0].size();
    if(m != r){ throw std::invalid_argument("no viable sizes");}
    MatrixVector mulVector(n, vector<double>(c));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < c; ++j) {
            mulVector[i][j]=0;
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < c; ++j){
            for(int k = 0; k < m; ++k) {
                mulVector[i][j] += _matrix[i][k] * matrixV[k][j];
            }
        }
    }
    Matrix mulMatrix = mulVector;
    return mulMatrix;
}

Matrix::MatrixVector Matrix::getMultiplication(const MatrixVector& first, const MatrixVector& second) {
    long r1 = first.size();
    long c1 = first[0].size();
    long r2 = second.size();
    long c2 = second[0].size();
    if(c1 != r2){ throw std::invalid_argument("no viable sizes");}
    MatrixVector mulmatrix(r1, vector<double>(c2));
    for(int i = 0; i < r1; ++i) {
        for(int j = 0; j < c2; ++j) {
            mulmatrix[i][j]=0;
        }
    }
    for(int i = 0; i < r1; ++i) {
        for(int j = 0; j < c2; ++j){
            for(int k = 0; k < c1; ++k) {
                mulmatrix[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    return mulmatrix;
}

Matrix::MatrixVector Matrix::getAddition(const MatrixVector& first, const MatrixVector& second) {
    long r1 = first.size();
    long c1 = first[0].size();
    long r2 = second.size();
    long c2 = second[0].size();
    if((r1 != r2) || (c1 != c2)){ throw std::invalid_argument("no viable dimensions");}

    MatrixVector addMatrix(r1, vector<double>(c2));
    for(int i = 0; i < r1; ++i) {
        for(int j = 0; j < r2; ++j){
                addMatrix[i][j] = first[i][j] + second[i][j];
        }
    }
    return addMatrix;
}

Matrix::MatrixVector Matrix::operator+(const MatrixVector& matrix) {
    long r = matrix.size();
    long c = matrix[0].size();
    if((r != n) || (m != c)){ throw std::invalid_argument("no viable dimensions");}

    MatrixVector addMatrix(n, vector<double>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j){
                addMatrix[i][j] = _matrix[i][j] + matrix[i][j];
        }
    }
    return addMatrix;
}

Matrix Matrix::operator+(const Matrix& matrix) {
    MatrixVector matrixV = matrix.getMatrix();
    long r = matrixV.size();
    long c = matrixV[0].size();
    if((r != n) || (m != c)){ throw std::invalid_argument("no viable dimensions");}

    MatrixVector addVector(n, vector<double>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j){
                addVector[i][j] = matrixV[i][j] + _matrix[i][j];
        }
    }
    Matrix addMatrix = addVector;
    return addMatrix;
}

bool Matrix::isSymmetric() const {
    if(_isSquare == false) return false;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(_matrix[i][j] != _transposed[i][j]) return false;
        }
    }
    return true;
}

bool Matrix::isSkewSymmetric() const {
    if(_isSquare == false) return false;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(_matrix[i][j] != -_transposed[i][j]) return false;
        }
    }
    return true;
}
