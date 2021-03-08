//Given an array nums and a value val, remove all instances of that value in-pla
//ce and return the new length. 
//
// Do not allocate extra space for another array, you must do this by modifying 
//the input array in-place with O(1) extra memory. 
//
// The order of elements can be changed. It doesn't matter what you leave beyond
// the new length. 
//
// Clarification: 
//
// Confused why the returned value is an integer but your answer is an array? 
//
// Note that the input array is passed in by reference, which means a modificati
//on to the input array will be known to the caller as well. 
//
// Internally you can think of this: 
//
// 
//// nums is passed in by reference. (i.e., without making a copy)
//int len = removeElement(nums, val);
//
//// any modification to nums in your function would be known by the caller.
//// using the length returned by your function, it prints the first len element
//s.
//for (int i = 0; i < len; i++) {
//    print(nums[i]);
//} 
//
// 
// Example 1: 
//
// 
//Input: nums = [3,2,2,3], val = 3
//Output: 2, nums = [2,2]
//Explanation: Your function should return length = 2, with the first two elemen
//ts of nums being 2.
//It doesn't matter what you leave beyond the returned length. For example if yo
//u return 2 with nums = [2,2,3,3] or nums = [2,2,0,0], your answer will be accept
//ed.
// 
//
// Example 2: 
//
// 
//Input: nums = [0,1,2,2,3,0,4,2], val = 2
//Output: 5, nums = [0,1,4,0,3]
//Explanation: Your function should return length = 5, with the first five eleme
//nts of nums containing 0, 1, 3, 0, and 4. Note that the order of those five elem
//ents can be arbitrary. It doesn't matter what values are set beyond the returned
// length.
// 
//
// 
// Constraints: 
//
// 
// 0 <= nums.length <= 100 
// 0 <= nums[i] <= 50 
// 0 <= val <= 100 
// 
// Related Topics 数组 双指针 
// 👍 790 👎 0


#include<iostream>
#include <vector>

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int removeElement(vector<int> &nums, int val) {

#ifdef SOLUTION_1
        // 暴力操作，直接删
        if (nums.empty()) return 0;
        for (auto begin = nums.begin(); begin != nums.end();) {
            if (*begin == val) {
                begin = nums.erase(begin);
                continue;
            }
            ++begin;
        }

        return nums.size();
#elif defined(SOLUTION_2)
        // 双指针，快指针会一直前进，
        // 当快指针的值与要删除的值不相同的时候将快指针的值复制到慢指针处，随后慢指针往后移动

        if (nums.empty()) return 0;
        auto fast = nums.begin(), slow = fast, end = nums.end();
        while (fast != end) {
            if (*fast != val) *slow++ = *fast;
            ++fast;
        }
        return distance(nums.begin(), slow);
#else
        // 双指针，一个指针在前，一个指针在后，先对后面的指针判断，
        // 如果后指针指向的值与要删除的值相同，后指针往前移动一个，
        // 如果不相同，接着判断前面的指针，
        // 如果前面的指针指向的值与要删除的值相同，那么就交换前后指针指向的值
        // 前指针越过后指针就停止遍历，计算前指针距离开始有多少个元素

        if (nums.empty()) return 0;
        auto begin = nums.begin(), end = --nums.end();
        while (begin <= end) {
            if (*end == val) {
                --end;
                continue;
            }
            if (*begin == val) swap(*begin, *end);
            else ++begin;
        }
        return distance(nums.begin(), begin);
#endif
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    vector<int> v{3, 2, 2, 3};
    Solution solution;
    std::cout << solution.removeElement(v, 3);
    return 0;
}