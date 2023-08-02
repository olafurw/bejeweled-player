#pragma once

#include "opencv2/core/core.hpp"

#include "Pattern.hpp"
#include <optional>

struct Solution {
    std::pair<int, int> C_point;
    std::pair<int, int> direction;
    int value;
};

std::optional<Solution> solve(const Patterns & patterns, const cv::Mat & screen);
