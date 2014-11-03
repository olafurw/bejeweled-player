#ifndef BEJEWELED_SOLVER
#define BEJEWELED_SOLVER

#include "opencv2/core/core.hpp"

#include "Pattern.hpp"

using namespace cv;

struct Solution
{
    Point2i C_point;
    Point2i direction;
    int value;
};

class Solver
{
public:
    Solver(Mat& screen);

    bool solve(const Patterns& patterns);
    Solution m_solution;
private:
    char m_board[8][8];
    std::vector<Solution> m_solutions;

    bool match(const int i, const int j, const Pattern& pattern);
    bool point_inside(const Point2i& point);

    char detect_gem(const Vec4b& inColor);
};

#endif