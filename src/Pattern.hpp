#pragma once

#include <vector>

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
    std::vector<std::pair<int, int>> points;
    PatternType type;
    int id;
    int value;
    std::pair<int, int> solution_dir;
};

class Patterns {
  public:
    Patterns();

    std::vector<Pattern> m_patterns;
};
