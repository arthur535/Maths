#include "Matrixes/Matrix.h"
#include <iostream>
#include <vector>
// #include "Matrixes/gaussian.cpp"
#include "Permutations/permutations.h"
int main(int argc, char* argv[]) {
    std::vector<std::vector<double>> matrix = {
        {0, -5,-2},
        {5, 6, -2},
        {2, 2, 0}
    };
    
    // int n = 3;
    // solve(matrix, n);
    // for(int i = 0; i < n; ++i) {
    //     std::cout << i << " row: ";
    //     for(int j = 0; j < n; ++j) {
    //         std::cout << matrix[i][j] << " ";
    //     }
    //     std::cout << "= " << matrix[i][n];
    //     std::cout << std::endl;
    // }

    // int n = 4;
    // auto all = Permutations::permute(n);
    // for(int i = 0; i < all.size(); ++i) {
    //     for(int j = 0; j < n; ++j){
    //         cout << all[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    std::vector<std::vector<int>> permut = {{0,1,2,3}, {0,3,1,2}};
    Permutations per(4, {2,1,3,0});
    auto mul = per * permut;
    for(int j = 0; j < mul[0].size(); ++j) {
        std::cout << mul[0][j] << " ";
    }
    std::cout << std::endl;
    for(int j = 0; j < mul[1].size(); ++j) {
        std::cout << mul[1][j] << " ";
    }
}
