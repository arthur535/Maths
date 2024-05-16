#include <vector>
#include "permutations.h"
#include <iostream>
#include <unordered_set>
void Permutations::generatePermutations(std::vector<int>& nums, int start, std::vector<std::vector<int>>& result) {
    if (start == nums.size() - 1) {
        result.push_back(nums);
        return;
    }

    for (int i = start; i < nums.size(); ++i) {
        std::swap(nums[start], nums[i]);
        generatePermutations(nums, start + 1, result);
        std::swap(nums[start], nums[i]);
    }
}
std::vector<std::vector<int>> Permutations::permute(int n) {
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }

    std::vector<std::vector<int>> result;
    generatePermutations(nums, 0, result);
    return result;
}

Permutations::Permutations(size_t size) {
    n = size;
    permutation.reserve(2);
    for(int i = 0; i < n; ++i) {
        permutation[0].push_back(i+1);
        permutation[1].push_back(i+1);
    }
}

Permutations::Permutations(size_t size, const std::vector<int>& vec) {
    if(size != vec.size()) throw std::invalid_argument("given size doesn't match with vector's size");
    for(int i = 0; i < size; ++i) {
        if(vec[i] < 0 or vec[i] >= size) throw std::invalid_argument("elements of given permutation should be from 0 to size - 1");
    }
    std::unordered_set<int> visited;
    for(int i = 0; i < size; ++i) {
        if(visited.find(vec[i]) != visited.end()) throw std::invalid_argument("elements of given permutation should be unique");
        visited.insert(vec[i]);
    }
    n = size;
    permutation.reserve(2);
    for(int i = 0; i < n; ++i) {
        permutation[0].push_back(i);
        permutation[1].push_back(vec[i]);
    }
}

bool Permutations::isValid(const std::vector<std::vector<int>>& vec) {
    int n = vec.size();
    if( (n != 2) or (vec[0].size() != vec[1].size()) ) return false;
    std::vector<std::vector<int>> copy = vec;
    std::sort(copy[0].begin(), copy[0].end());
    std::sort(copy[1].begin(), copy[1].end());
    if(copy[0][0] != 0 or copy[0][n-1] != n-1 or copy[1][0] != 0 or copy[1][n-1] != n-1) return false;
    for(int i = 0; i < n-1; ++i) {
        if(copy[0][i+1] - copy[0][i] != 1) return false;
        if(copy[1][i+1] - copy[1][i] != 1) return false;
    }
    return true;
}
std::vector<std::vector<int>> Permutations::operator*(const std::vector<std::vector<int>>& vec) {
    int size = vec.size();
    if(isValid(vec) == false) throw std::invalid_argument("invalid permutation");
    if(vec[0].size() != n) throw std::invalid_argument("given permutation sizes doesn't match");
    std::vector<std::vector<int>> mulPermutation(2, std::vector<int>(vec[0].size()));
    for(int i = 0; i < n; ++i) {
        mulPermutation[0][i] = permutation[0][i];
        mulPermutation[1][i] = vec[1][i];
    }
    return mulPermutation;
}