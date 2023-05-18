#pragma once

#include "opencv2/core/core.hpp"

enum PatternType {
    VerticalThreeI,
    HorizontalThreeI,
    VerticalThreeJ,
    HorizontalThreeJ,
    HorizontalThreeV,
    VerticalThreeV,
    VerticalFour,
    HorizontalFour,
    VerticalFive,
    HorizontalFive,
    CornerFive,
};

struct Pattern {
    std::vector<cv::Point2i> points;
    PatternType type;
    int id;
    int value;
    cv::Point2i solution_dir;
};

class Patterns {
  public:
    Patterns();

    std::vector<Pattern> m_patterns;
};
