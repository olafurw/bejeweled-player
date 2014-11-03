#ifndef BEJEWELED_PATTERN
#define BEJEWELED_PATTERN

#include "opencv2/core/core.hpp"

using namespace cv;

enum PatternType
{
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

struct Pattern
{
    std::vector<Point2i> points;
    PatternType type;
    int id;
    int value;
    Point2i solution_dir;
};

class Patterns
{
public:
    Patterns();

    std::vector<Pattern> m_patterns;
};

#endif