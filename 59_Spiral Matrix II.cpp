//Given a positive integer n, generate an n x n matrix filled with elements from
// 1 to n2 in spiral order. 
//
// 
// Example 1: 
//
// 
//Input: n = 3
//Output: [[1,2,3],[8,9,4],[7,6,5]]
// 
//
// Example 2: 
//
// 
//Input: n = 1
//Output: [[1]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 20 
// 
// Related Topics 数组 
// 👍 316 👎 0


#include<iostream>
#include <vector>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        /**
         * 一圈一圈填，外圈填完了就填内圈
         * 那么在一圈内如何填呢，我将一圈划分为4个区域，每个区域最大包含n-1个位置，
         * 这样一个区域填充完了之后的row或者col就是下一个区域的起始位置。
         * 这种方式需要处理n为奇数或偶数的情况，
         * 因为n为奇数的时候最中心的位置是单独的一个元素，无法形成环，那么就直接将最大值填充到这个位置即可。
         */

        vector<vector<int>> v;
        v.resize(n);
        for (auto &e : v) e.resize(n);
        int i = 1;
        auto row = 0, col = 0;
        auto circle = n / 2;
        if (n % 2) v[n / 2][n / 2] = n * n;
        while (circle) {
            for (int j = 0; j < 4; ++j)
                for (int k = 0; k < n - 1; ++k) {
                    switch (j) {
                        case 0:
                            v[row][col++] = i++;
                            break;
                        case 1:
                            v[row++][col] = i++;
                            break;
                        case 2:
                            v[row][col--] = i++;
                            break;
                        case 3:
                            v[row--][col] = i++;
                            break;
                    }
                }
            n -= 2;
            --circle;
            ++row, ++col;
        }
        return v;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    return 0;
}