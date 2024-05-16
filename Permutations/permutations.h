#include <vector>
class Permutations {
public:
    static std::vector<std::vector<int>> permute(int);
    std::vector<std::vector<int>> operator*(const std::vector<std::vector<int>>&);
    Permutations(size_t size);
    Permutations(size_t size, const std::vector<int>&);
private:
    static void generatePermutations(std::vector<int>&, int, std::vector<std::vector<int>>&);
    static bool isValid(const std::vector<std::vector<int>>&);

    int n;
    std::vector<std::vector<int>> permutation;
};