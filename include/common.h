//
// Created by KK on 2021/2/19.
//

#ifndef LEETCODE_COMMON_H
#define LEETCODE_COMMON_H

#include <chrono>
#include <random>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <unordered_set>
#include <type_traits>
#include <functional>
#include <thread>
#include <algorithm>

namespace common {
    using namespace std::chrono;
#define START_TIMESTAMP(tag_) auto tag_##_start = std::chrono::steady_clock::now()
#define END_TIMESTAMP(tag_) auto tag_##_end = std::chrono::steady_clock::now()
#define DURATION_TIME(tag_, time_type_) std::chrono::duration_cast<time_type_>(tag_##_end - tag_##_start).count()

    class Randoms {
    public:
        template<typename T_>
        std::vector<T_> operator()(std::size_t counts, T_ min, T_ max) {
            std::vector<T_> vec;
            vec.reserve(counts);
            for (int i = 0; i < counts; ++i) {
                vec.push_back(generate_(min, max));
            }
            return std::move(vec);
        }

    private:
        std::default_random_engine e;

        template<typename t_>
        std::enable_if_t<std::is_integral<t_>::value, t_>
        generate_(t_ min, t_ max) {
            std::uniform_int_distribution<t_> u(min, max);
            return u(e);
        }

        template<typename t_>
        std::enable_if_t<std::is_floating_point<t_>::value, t_>
        generate_(t_ min, t_ max) {
            std::uniform_real_distribution<t_> u_real(min, max);
            return u_real(e);
        }
    };
}

#endif //LEETCODE_COMMON_H
