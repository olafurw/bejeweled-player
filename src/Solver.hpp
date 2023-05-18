#pragma once

#include "opencv2/core/core.hpp"

#include "Pattern.hpp"

struct Solution {
    cv::Point2i C_point;
    cv::Point2i direction;
    int value;
};

class Solver {
  public:
    Solver(cv::Mat & screen);

    bool solve(const Patterns & patterns);
    Solution m_solution;

  private:
    char m_board[8][8];

    bool match(const int i, const int j, const Pattern & pattern);
    bool point_inside(const cv::Point2i & point);

    char detect_gem(const cv::Vec4b & inColor);
};
