//Given an array of positive integers nums and a positive integer target, return
// the minimal length of a contiguous subarray [numsl, numsl+1, ..., numsr-1, nums
//r] of which the sum is greater than or equal to target. If there is no such suba
//rray, return 0 instead. 
//
// 
// Example 1: 
//
// 
//Input: target = 7, nums = [2,3,1,2,4,3]
//Output: 2
//Explanation: The subarray [4,3] has the minimal length under the problem const
//raint.
// 
//
// Example 2: 
//
// 
//Input: target = 4, nums = [1,4,4]
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: target = 11, nums = [1,1,1,1,1,1,1,1]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= target <= 109 
// 1 <= nums.length <= 105 
// 1 <= nums[i] <= 105 
// 
//
// 
//Follow up: If you have figured out the O(n) solution, try coding another solut
//ion of which the time complexity is O(n log(n)). Related Topics 数组 双指针 二分查找 
// 👍 578 👎 0


#include<iostream>
#include <vector>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minSubArrayLen(int target, vector<int> &nums) {

#ifdef SOLUTION_1
        /**
         * 前缀和 + 二分搜索
         * 由于都是正整数，因此前缀和都有序递增的，通过二分搜索可以找到正确的位置
         * 对于数组的前缀和sum[i]，表示前i个元素的和,
         * 只要sum[j] - sum[i] >= target,那么 j - i的大小就是区间内元素个数
         * 由于i和j都是未知，因此上面的公式并不好实现，而target是已经知道的，
         * 因此可以将公式变换为target + sum[i] <= sum[j]，
         * i随着循环递增，通过二分搜索在前缀和数组中查找符合要求的j
         */
        vector<int> prefix_sum{0};
        int sum{0};
        prefix_sum.reserve(nums.size() + 1);
        for (const auto &cn : nums) prefix_sum.emplace_back(sum += cn);
        auto size = nums.size();
        int cnt = size + 1;
        for (auto begin = prefix_sum.begin(), end = prefix_sum.end(); begin != end; ++begin) {
            int t = *begin + target;
            // 如果t超过前缀和数组中的最后一个数值
            // 说明即使再往后遍历也找不到和为目标值的组合了，因此可以直接退出
            if (t > *(end - 1)) break;
            auto bound = binary_search_(prefix_sum, t);
            cnt = min(cnt, static_cast<int>(distance(begin, bound)));
        }
        return cnt > size ? 0 : cnt;
#else

        /**
         * 双指针，滑动窗口，核心思想是对双指针形成的窗口中的数值总和进行判断
         * 如果总和超过了目标值，就将左侧的指针向后移动,同时从总和中减去被移除掉的数值
         * 如果总和未超过目标值，就将右侧的指针向后移动，同时将新加入数值添加到总和中
         * 由于使用distance计算两个迭代器的距离，右侧为开区间，因此左侧迭代器小于右侧迭代器
         */
        auto size = nums.size();
        // cnt 是 size + 1是为了确定是否全部元素的和都小于目标值
        int cnt = size + 1;
        int sum = nums[0];
        auto left = nums.begin(), right = left + 1, end = nums.end();
        while (left < right) {
            if (sum >= target) {
                cnt = min(cnt, static_cast<int>(distance(left, right)));
                sum -= *left++;
                continue;
            }
            // 运行到此处说明总和是小于目标值的，
            // 如果右侧的迭代器已经到了尾后迭代器说明不会再存在超过目标值的情况了
            // 直接退出循环即可
            if (right == end) break;
            sum += *right++;
        }
        return cnt > size ? 0 : cnt;
#endif
    }

private:
    auto binary_search_(vector<int> &v, int target) -> decltype(v.end()) {
        auto left = v.begin(), right = v.end();
        while (left < right) {
            auto mid = left + (right - left) / 2;
            if (*mid > target) right = mid;
            else if (*mid == target) return mid;
            else left = mid + 1;
        }
        return left;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    vector<int> v{1, 2, 3, 4, 5};
    Solution solution;
    std::cout << solution.minSubArrayLen(15, v);
    return 0;
}