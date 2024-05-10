#include <iostream>
#include <vector>
using namespace std;
void permute(vector<int>& nums, vector<vector<int>>& allPermutations, int l, int r) {
    if (l == r) {
        allPermutations.push_back(nums);
    } else {
        for (int i = l; i <= r; i++) {
            swap(nums[l], nums[i]);
            permute(nums, allPermutations, l + 1, r);
            swap(nums[l], nums[i]); // Backtrack
        }
    }
}

vector<vector<int>> generatePermutations(int n) {
    vector<int> initial(n);
    vector<vector<int>> allPermutations;
    for(int i = 0; i < n; ++i){
        initial[i] = i;
    }
    permute(initial, allPermutations, 0, n - 1);
    return allPermutations;
}

int determinant(vector<vector<int>>& matrix, int n) {
    int determinant = 0;
    vector<vector<int>> permutations = generatePermutations(n);
    for(int i = 0; i < permutations.size(); ++i) {
        int temp = 1;
        for(int j = 0; j < n; ++j) {
            temp *= matrix[j][permutations[i][j]];
        }
        int sign = 1;
        for(int j = 0; j < n; ++j) {
            for(int k = j + 1; k < n; ++k) {
                if (permutations[i][j] > permutations[i][k]) {
                    sign = -sign;
                }
            }
        }
        determinant += sign * temp;
    }
    return determinant;
}

int main() {
    int n = 5; // Change the numbers here
    vector<vector<int>> matrix = {
        {0,6,-2,-1,5},
        {0,0,0,-9,-7},
        {0,15,35,0,0},
        {0,-1,-11,-2, 1},
        {-2,-2,3,0,-2}
    };
    cout << determinant(matrix, n);
    return 0;
}

