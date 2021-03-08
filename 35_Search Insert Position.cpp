//Given a sorted array of distinct integers and a target value, return the index
// if the target is found. If not, return the index where it would be if it were i
//nserted in order. 
//
// 
// Example 1: 
// Input: nums = [1,3,5,6], target = 5
//Output: 2
// Example 2: 
// Input: nums = [1,3,5,6], target = 2
//Output: 1
// Example 3: 
// Input: nums = [1,3,5,6], target = 7
//Output: 4
// Example 4: 
// Input: nums = [1,3,5,6], target = 0
//Output: 0
// Example 5: 
// Input: nums = [1], target = 0
//Output: 0
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 104 
// -104 <= nums[i] <= 104 
// nums contains distinct values sorted in ascending order. 
// -104 <= target <= 104 
// 
// Related Topics 数组 二分查找 
// 👍 839 👎 0


#include<iostream>
#include <vector>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
#define SOLUTION_2
        /**
         * 二分搜搜:二分搜索是不停的更新区间的上限和下限，但是每次只更新上限或者下限
         * 如果采取双侧闭区间，那么最终区间的下限是允许等于上限的，因此当下限超过上限的时候就应该停止更新上限或者下限
         * 如果采取左闭右开区间，那么最终区间的下限不允许等于上限，当下限与上限相等的时候就应该停止更新上限或下限
         * 无论采用什么区间，只要退出了循环，说明下限处于刚违背条件的状态，这时候的下限就是我们要的结果
         */
#ifdef SOLUTION_1
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            // 从left开始找位置，而不是 (left + right) / 2直接定位位置,这样可以防止加法溢出
            auto mid = left + (right - left) / 2;
            if (nums[mid] > target) right = mid - 1;
            else if (nums[mid] == target) return mid;
            else left = mid + 1;
        }
        return left;
#elif defined(SOLUTION_2)
        int left = 0, right = nums.size();
        while (left < right) {
            auto mid = left + (right - left) / 2;
            // 由于右侧是开区间，因此应该是mid,而不是mid -1
            if (nums[mid] > target) right = mid;
            else if (nums[mid] == target) return mid;
            else left = mid + 1;
        }
        return left;
#else
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] >= target) return i;
        }
        return nums.size();
#endif
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    return 0;
}