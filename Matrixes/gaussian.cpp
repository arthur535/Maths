#include <iostream>
#include <vector>
using namespace std;

void print(vector<vector<double>> matrix, int n) {
    for(int i = 0; i < n; ++i) {
        std::cout << i << " row: ";
        for(int j = 0; j < n; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "= " << matrix[i][n];
        std::cout << std::endl;
    }
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

vector<vector<double>> solve(vector<vector<double>>& matrix, int n) {
    std::vector<double> solution(n);
    int i = 0;
    for(int j = 0; j < n-1; ++j) {
        for(int i = n-1; i > j; i--) {
            std::cout << "before multipling" << endl;
            print(matrix, n);
            if(matrix[i][j] != matrix[i-1][j]){
                int coef1 = matrix[i-1][j];
                int coef2 = matrix[i][j];
                double lcm_coef = lcm(coef1, coef2);
                cout << lcm_coef << "  " << coef1 << "  " << coef2 <<endl;
                std::vector<double> sub(n+1);
                for(int k = j; k <= n; ++k) {
                    matrix[i][k] *= (lcm_coef / coef2);
                    matrix[i-1][k] *= (lcm_coef / coef1);
                    sub[k] = matrix[i-1][k] - matrix[i][k];
                }
                std::cout << "after multipling" << endl;
                print(matrix, n);
                matrix[i] = sub;
                std::cout << "after sub" << endl;
                print(matrix,n);
                cout << endl;
            }
        }
        cout << "lalalala" << endl;;
        int coef = matrix[i][j];
        for(int j = 0; j < n+1; ++j){
            matrix[i][j] /= coef;
        }
        ++i;
    }
    int coef = matrix[n-1][n-1];
    for(int i = 0; i < n+1; ++i){
        matrix[n-1][i] /= coef;
    }

    return matrix;
}

int main() {
    int n = 4;
//    std::cout << "define size of the matrix of linear equations: ";
//    std::cin >> n;
//    vector<vector<double>> matrix(n, vector<double>(n + 1));
//    for(int i = 0; i < n; ++i) {
//        std::cout << "input " << i << " row: " << std::endl;
//        for(int j = 0; j < n; ++j) {
//            std::cin >> matrix[i][j];
//        }
//        std::cout << "input " << i <<  " row value : ";
//        std::cin >> matrix[i][n];
//    }
    vector<vector<double>> matrix{
        {3,2,-4,1,3},
        {3,3,-3,1,15},
        {6,-3,1,1,14},
        {4,3,8,1,8}
    };
    solve(matrix, n);
    for(int i = 0; i < n; ++i) {
        std::cout << i << " row: ";
        for(int j = 0; j < n; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "= " << matrix[i][n];
        std::cout << std::endl;
    }
}
