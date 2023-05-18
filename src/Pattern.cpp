#include "Pattern.hpp"

Patterns::Patterns()
{
    // CxBA
    Pattern vertical_i_left;
    vertical_i_left.points.emplace_back(cv::Point2i(0, 0));
    vertical_i_left.points.emplace_back(cv::Point2i(-1, 0));
    vertical_i_left.points.emplace_back(cv::Point2i(-3, 0));
    vertical_i_left.type = HorizontalThreeI;
    vertical_i_left.solution_dir = cv::Point2i(1, 0);
    vertical_i_left.id = 1;
    vertical_i_left.value = 1;

    m_patterns.emplace_back(vertical_i_left);

    // ABxC
    Pattern vertical_i_right;
    vertical_i_right.points.emplace_back(cv::Point2i(0, 0));
    vertical_i_right.points.emplace_back(cv::Point2i(1, 0));
    vertical_i_right.points.emplace_back(cv::Point2i(3, 0));
    vertical_i_right.type = HorizontalThreeI;
    vertical_i_right.solution_dir = cv::Point2i(-1, 0);
    vertical_i_right.id = 2;
    vertical_i_right.value = 1;

    m_patterns.emplace_back(vertical_i_right);

    // C
    // x
    // B
    // A
    Pattern horizontal_i_top;
    horizontal_i_top.points.emplace_back(cv::Point2i(0, 0));
    horizontal_i_top.points.emplace_back(cv::Point2i(0, -1));
    horizontal_i_top.points.emplace_back(cv::Point2i(0, -3));
    horizontal_i_top.type = VerticalThreeI;
    horizontal_i_top.solution_dir = cv::Point2i(0, 1);
    horizontal_i_top.id = 3;
    horizontal_i_top.value = 1;

    m_patterns.emplace_back(horizontal_i_top);

    // A
    // B
    // x
    // C
    Pattern horizontal_i_bottom;
    horizontal_i_bottom.points.emplace_back(cv::Point2i(0, 0));
    horizontal_i_bottom.points.emplace_back(cv::Point2i(0, 1));
    horizontal_i_bottom.points.emplace_back(cv::Point2i(0, 3));
    horizontal_i_bottom.type = VerticalThreeI;
    horizontal_i_bottom.solution_dir = cv::Point2i(0, -1);
    horizontal_i_bottom.id = 4;
    horizontal_i_bottom.value = 1;

    m_patterns.emplace_back(horizontal_i_bottom);

    // ABx
    //   C
    Pattern horizontal_j_bottom_right;
    horizontal_j_bottom_right.points.emplace_back(cv::Point2i(0, 0));
    horizontal_j_bottom_right.points.emplace_back(cv::Point2i(1, 0));
    horizontal_j_bottom_right.points.emplace_back(cv::Point2i(2, 1));
    horizontal_j_bottom_right.type = HorizontalThreeJ;
    horizontal_j_bottom_right.solution_dir = cv::Point2i(0, -1);
    horizontal_j_bottom_right.id = 5;
    horizontal_j_bottom_right.value = 1;

    m_patterns.emplace_back(horizontal_j_bottom_right);

    // xBA
    // C
    Pattern horizontal_j_bottom_left;
    horizontal_j_bottom_left.points.emplace_back(cv::Point2i(0, 0));
    horizontal_j_bottom_left.points.emplace_back(cv::Point2i(-1, 0));
    horizontal_j_bottom_left.points.emplace_back(cv::Point2i(-2, 1));
    horizontal_j_bottom_left.type = HorizontalThreeJ;
    horizontal_j_bottom_left.solution_dir = cv::Point2i(0, -1);
    horizontal_j_bottom_left.id = 6;
    horizontal_j_bottom_left.value = 1;

    m_patterns.emplace_back(horizontal_j_bottom_left);

    //   C
    // ABx
    Pattern horizontal_j_top_right;
    horizontal_j_top_right.points.emplace_back(cv::Point2i(0, 0));
    horizontal_j_top_right.points.emplace_back(cv::Point2i(1, 0));
    horizontal_j_top_right.points.emplace_back(cv::Point2i(2, -1));
    horizontal_j_top_right.type = HorizontalThreeJ;
    horizontal_j_top_right.solution_dir = cv::Point2i(0, 1);
    horizontal_j_top_right.id = 7;
    horizontal_j_top_right.value = 1;

    m_patterns.emplace_back(horizontal_j_top_right);

    // C
    // xBA
    Pattern horizontal_j_top_left;
    horizontal_j_top_left.points.emplace_back(cv::Point2i(0, 0));
    horizontal_j_top_left.points.emplace_back(cv::Point2i(-1, 0));
    horizontal_j_top_left.points.emplace_back(cv::Point2i(-2, -1));
    horizontal_j_top_left.type = HorizontalThreeJ;
    horizontal_j_top_left.solution_dir = cv::Point2i(0, 1);
    horizontal_j_top_left.id = 8;
    horizontal_j_top_left.value = 1;

    m_patterns.emplace_back(horizontal_j_top_left);

    //  C
    // AxB
    Pattern horizontal_v_top;
    horizontal_v_top.points.emplace_back(cv::Point2i(0, 0));
    horizontal_v_top.points.emplace_back(cv::Point2i(2, 0));
    horizontal_v_top.points.emplace_back(cv::Point2i(1, -1));
    horizontal_v_top.type = HorizontalThreeV;
    horizontal_v_top.solution_dir = cv::Point2i(0, 1);
    horizontal_v_top.id = 9;
    horizontal_v_top.value = 1;

    m_patterns.emplace_back(horizontal_v_top);

    // AxB
    //  C
    Pattern horizontal_v_bottom;
    horizontal_v_bottom.points.emplace_back(cv::Point2i(0, 0));
    horizontal_v_bottom.points.emplace_back(cv::Point2i(2, 0));
    horizontal_v_bottom.points.emplace_back(cv::Point2i(1, 1));
    horizontal_v_bottom.type = HorizontalThreeV;
    horizontal_v_bottom.solution_dir = cv::Point2i(0, -1);
    horizontal_v_bottom.id = 10;
    horizontal_v_bottom.value = 1;

    m_patterns.emplace_back(horizontal_v_bottom);

    // A
    // xC
    // B
    Pattern vertical_v_right;
    vertical_v_right.points.emplace_back(cv::Point2i(0, 0));
    vertical_v_right.points.emplace_back(cv::Point2i(0, 2));
    vertical_v_right.points.emplace_back(cv::Point2i(1, 1));
    vertical_v_right.type = VerticalThreeV;
    vertical_v_right.solution_dir = cv::Point2i(-1, 0);
    vertical_v_right.id = 11;
    vertical_v_right.value = 1;

    m_patterns.emplace_back(vertical_v_right);

    // xC
    // B
    // A
    Pattern vertical_j_right_top;
    vertical_j_right_top.points.emplace_back(cv::Point2i(0, 0));
    vertical_j_right_top.points.emplace_back(cv::Point2i(0, -1));
    vertical_j_right_top.points.emplace_back(cv::Point2i(1, -2));
    vertical_j_right_top.type = VerticalThreeJ;
    vertical_j_right_top.solution_dir = cv::Point2i(-1, 0);
    vertical_j_right_top.id = 12;
    vertical_j_right_top.value = 1;

    m_patterns.emplace_back(vertical_j_right_top);

    // Cx
    //  B
    //  A
    Pattern vertical_j_left_top;
    vertical_j_left_top.points.emplace_back(cv::Point2i(0, 0));
    vertical_j_left_top.points.emplace_back(cv::Point2i(0, -1));
    vertical_j_left_top.points.emplace_back(cv::Point2i(-1, -2));
    vertical_j_left_top.type = VerticalThreeJ;
    vertical_j_left_top.solution_dir = cv::Point2i(1, 0);
    vertical_j_left_top.id = 13;
    vertical_j_left_top.value = 1;

    m_patterns.emplace_back(vertical_j_left_top);

    // A
    // B
    // xC
    Pattern vertical_j_right_bottom;
    vertical_j_right_bottom.points.emplace_back(cv::Point2i(0, 0));
    vertical_j_right_bottom.points.emplace_back(cv::Point2i(0, 1));
    vertical_j_right_bottom.points.emplace_back(cv::Point2i(1, 2));
    vertical_j_right_bottom.type = VerticalThreeJ;
    vertical_j_right_bottom.solution_dir = cv::Point2i(-1, 0);
    vertical_j_right_bottom.id = 14;
    vertical_j_right_bottom.value = 1;

    m_patterns.emplace_back(vertical_j_right_bottom);

    //  A
    //  B
    // Cx
    Pattern vertical_j_left_bottom;
    vertical_j_left_bottom.points.emplace_back(cv::Point2i(0, 0));
    vertical_j_left_bottom.points.emplace_back(cv::Point2i(0, 1));
    vertical_j_left_bottom.points.emplace_back(cv::Point2i(-1, 2));
    vertical_j_left_bottom.type = VerticalThreeJ;
    vertical_j_left_bottom.solution_dir = cv::Point2i(1, 0);
    vertical_j_left_bottom.id = 15;
    vertical_j_left_bottom.value = 1;

    m_patterns.emplace_back(vertical_j_left_bottom);

    //  A
    // Cx
    //  B
    Pattern vertical_v_left;
    vertical_v_left.points.emplace_back(cv::Point2i(0, 0));
    vertical_v_left.points.emplace_back(cv::Point2i(0, 2));
    vertical_v_left.points.emplace_back(cv::Point2i(-1, 1));
    vertical_v_left.type = VerticalThreeV;
    vertical_v_left.solution_dir = cv::Point2i(1, 0);
    vertical_v_left.id = 16;
    vertical_v_left.value = 1;

    m_patterns.emplace_back(vertical_v_left);

    // ABxD
    //   C
    Pattern horizontal_v_four_bottom_right;
    horizontal_v_four_bottom_right.points.emplace_back(cv::Point2i(0, 0)); // A
    horizontal_v_four_bottom_right.points.emplace_back(cv::Point2i(1, 0)); // B
    horizontal_v_four_bottom_right.points.emplace_back(cv::Point2i(3, 0)); // D
    horizontal_v_four_bottom_right.points.emplace_back(cv::Point2i(2, 1)); // C
    horizontal_v_four_bottom_right.type = HorizontalFour;
    horizontal_v_four_bottom_right.solution_dir = cv::Point2i(0, -1);
    horizontal_v_four_bottom_right.id = 17;
    horizontal_v_four_bottom_right.value = 2;

    m_patterns.emplace_back(horizontal_v_four_bottom_right);

    // AxBD
    //  C
    Pattern horizontal_v_four_bottom_left;
    horizontal_v_four_bottom_left.points.emplace_back(cv::Point2i(0, 0)); // A
    horizontal_v_four_bottom_left.points.emplace_back(cv::Point2i(2, 0)); // B
    horizontal_v_four_bottom_left.points.emplace_back(cv::Point2i(3, 0)); // D
    horizontal_v_four_bottom_left.points.emplace_back(cv::Point2i(1, 1)); // C
    horizontal_v_four_bottom_left.type = HorizontalFour;
    horizontal_v_four_bottom_left.solution_dir = cv::Point2i(0, -1);
    horizontal_v_four_bottom_left.id = 18;
    horizontal_v_four_bottom_left.value = 2;

    m_patterns.emplace_back(horizontal_v_four_bottom_left);

    //  C
    // AxBD
    Pattern horizontal_v_four_top_left;
    horizontal_v_four_top_left.points.emplace_back(cv::Point2i(0, 0)); // A
    horizontal_v_four_top_left.points.emplace_back(cv::Point2i(2, 0)); // B
    horizontal_v_four_top_left.points.emplace_back(cv::Point2i(3, 0)); // D
    horizontal_v_four_top_left.points.emplace_back(cv::Point2i(1, -1)); // C
    horizontal_v_four_top_left.type = HorizontalFour;
    horizontal_v_four_top_left.solution_dir = cv::Point2i(0, 1);
    horizontal_v_four_top_left.id = 19;
    horizontal_v_four_top_left.value = 2;

    m_patterns.emplace_back(horizontal_v_four_top_left);

    //   C
    // ABxD
    Pattern horizontal_v_four_top_right;
    horizontal_v_four_top_right.points.emplace_back(cv::Point2i(0, 0)); // A
    horizontal_v_four_top_right.points.emplace_back(cv::Point2i(1, 0)); // B
    horizontal_v_four_top_right.points.emplace_back(cv::Point2i(3, 0)); // D
    horizontal_v_four_top_right.points.emplace_back(cv::Point2i(2, -1)); // C
    horizontal_v_four_top_right.type = HorizontalFour;
    horizontal_v_four_top_right.solution_dir = cv::Point2i(0, 1);
    horizontal_v_four_top_right.id = 20;
    horizontal_v_four_top_right.value = 2;

    m_patterns.emplace_back(horizontal_v_four_top_right);

    //  A
    //  B
    // Cx
    //  D
    Pattern vertical_v_four_bottom_left;
    vertical_v_four_bottom_left.points.emplace_back(cv::Point2i(0, 0));
    vertical_v_four_bottom_left.points.emplace_back(cv::Point2i(0, 1));
    vertical_v_four_bottom_left.points.emplace_back(cv::Point2i(0, 3));
    vertical_v_four_bottom_left.points.emplace_back(cv::Point2i(-1, 2));
    vertical_v_four_bottom_left.type = VerticalFour;
    vertical_v_four_bottom_left.solution_dir = cv::Point2i(1, 0);
    vertical_v_four_bottom_left.id = 21;
    vertical_v_four_bottom_left.value = 2;

    m_patterns.emplace_back(vertical_v_four_bottom_left);

    // A
    // B
    // xC
    // D
    Pattern vertical_v_four_bottom_right;
    vertical_v_four_bottom_right.points.emplace_back(cv::Point2i(0, 0));
    vertical_v_four_bottom_right.points.emplace_back(cv::Point2i(0, 1));
    vertical_v_four_bottom_right.points.emplace_back(cv::Point2i(0, 3));
    vertical_v_four_bottom_right.points.emplace_back(cv::Point2i(1, 2));
    vertical_v_four_bottom_right.type = VerticalFour;
    vertical_v_four_bottom_right.solution_dir = cv::Point2i(-1, 0);
    vertical_v_four_bottom_right.id = 22;
    vertical_v_four_bottom_right.value = 2;

    m_patterns.emplace_back(vertical_v_four_bottom_right);

    // A
    // xC
    // B
    // D
    Pattern vertical_v_four_top_right;
    vertical_v_four_top_right.points.emplace_back(cv::Point2i(0, 0));
    vertical_v_four_top_right.points.emplace_back(cv::Point2i(0, 2));
    vertical_v_four_top_right.points.emplace_back(cv::Point2i(0, 3));
    vertical_v_four_top_right.points.emplace_back(cv::Point2i(1, 1));
    vertical_v_four_top_right.type = VerticalFour;
    vertical_v_four_top_right.solution_dir = cv::Point2i(-1, 0);
    vertical_v_four_top_right.id = 23;
    vertical_v_four_top_right.value = 2;

    m_patterns.emplace_back(vertical_v_four_top_right);

    //  A
    // Cx
    //  B
    //  D
    Pattern vertical_v_four_top_left;
    vertical_v_four_top_left.points.emplace_back(cv::Point2i(0, 0));
    vertical_v_four_top_left.points.emplace_back(cv::Point2i(0, 2));
    vertical_v_four_top_left.points.emplace_back(cv::Point2i(0, 3));
    vertical_v_four_top_left.points.emplace_back(cv::Point2i(-1, 1));
    vertical_v_four_top_left.type = VerticalFour;
    vertical_v_four_top_left.solution_dir = cv::Point2i(1, 0);
    vertical_v_four_top_left.id = 24;
    vertical_v_four_top_left.value = 2;

    m_patterns.emplace_back(vertical_v_four_top_left);

    // A
    // B
    // xC
    // D
    // E
    Pattern vertical_five_right;
    vertical_five_right.points.emplace_back(cv::Point2i(0, 0));
    vertical_five_right.points.emplace_back(cv::Point2i(0, 1));
    vertical_five_right.points.emplace_back(cv::Point2i(0, 3));
    vertical_five_right.points.emplace_back(cv::Point2i(0, 4));
    vertical_five_right.points.emplace_back(cv::Point2i(1, 2));
    vertical_five_right.type = VerticalFive;
    vertical_five_right.solution_dir = cv::Point2i(-1, 0);
    vertical_five_right.id = 25;
    vertical_five_right.value = 3;

    m_patterns.emplace_back(vertical_five_right);

    //  A
    //  B
    // Cx
    //  D
    //  E
    Pattern vertical_five_left;
    vertical_five_left.points.emplace_back(cv::Point2i(0, 0));
    vertical_five_left.points.emplace_back(cv::Point2i(0, 1));
    vertical_five_left.points.emplace_back(cv::Point2i(0, 3));
    vertical_five_left.points.emplace_back(cv::Point2i(0, 4));
    vertical_five_left.points.emplace_back(cv::Point2i(-1, 2));
    vertical_five_left.type = VerticalFive;
    vertical_five_left.solution_dir = cv::Point2i(1, 0);
    vertical_five_left.id = 26;
    vertical_five_left.value = 3;

    m_patterns.emplace_back(vertical_five_left);

    // ABxDE
    //   C
    Pattern horizontal_five_bottom;
    horizontal_five_bottom.points.emplace_back(cv::Point2i(0, 0));
    horizontal_five_bottom.points.emplace_back(cv::Point2i(1, 0));
    horizontal_five_bottom.points.emplace_back(cv::Point2i(3, 0));
    horizontal_five_bottom.points.emplace_back(cv::Point2i(4, 0));
    horizontal_five_bottom.points.emplace_back(cv::Point2i(2, 1));
    horizontal_five_bottom.type = VerticalFive;
    horizontal_five_bottom.solution_dir = cv::Point2i(0, -1);
    horizontal_five_bottom.id = 27;
    horizontal_five_bottom.value = 3;

    m_patterns.emplace_back(horizontal_five_bottom);

    //   C
    // ABxDE
    Pattern horizontal_five_top;
    horizontal_five_top.points.emplace_back(cv::Point2i(0, 0));
    horizontal_five_top.points.emplace_back(cv::Point2i(1, 0));
    horizontal_five_top.points.emplace_back(cv::Point2i(3, 0));
    horizontal_five_top.points.emplace_back(cv::Point2i(4, 0));
    horizontal_five_top.points.emplace_back(cv::Point2i(2, -1));
    horizontal_five_top.type = VerticalFive;
    horizontal_five_top.solution_dir = cv::Point2i(0, 1);
    horizontal_five_top.id = 28;
    horizontal_five_top.value = 3;

    m_patterns.emplace_back(horizontal_five_top);

    //  A
    //  B
    // CxDE
    Pattern corner_bottom_left;
    corner_bottom_left.points.emplace_back(cv::Point2i(0, 0));
    corner_bottom_left.points.emplace_back(cv::Point2i(0, 1));
    corner_bottom_left.points.emplace_back(cv::Point2i(1, 2));
    corner_bottom_left.points.emplace_back(cv::Point2i(2, 2));
    corner_bottom_left.points.emplace_back(cv::Point2i(-1, 2));
    corner_bottom_left.type = CornerFive;
    corner_bottom_left.solution_dir = cv::Point2i(1, 0);
    corner_bottom_left.id = 29;
    corner_bottom_left.value = 3;

    m_patterns.emplace_back(corner_bottom_left);

    //   A
    //   B
    // EDxC
    Pattern corner_bottom_right;
    corner_bottom_right.points.emplace_back(cv::Point2i(0, 0));
    corner_bottom_right.points.emplace_back(cv::Point2i(0, 1));
    corner_bottom_right.points.emplace_back(cv::Point2i(-1, 2));
    corner_bottom_right.points.emplace_back(cv::Point2i(-2, 2));
    corner_bottom_right.points.emplace_back(cv::Point2i(1, 2));
    corner_bottom_right.type = CornerFive;
    corner_bottom_right.solution_dir = cv::Point2i(-1, 0);
    corner_bottom_right.id = 30;
    corner_bottom_right.value = 3;

    m_patterns.emplace_back(corner_bottom_right);

    // ABxC
    //   D
    //   E
    Pattern corner_top_right;
    corner_top_right.points.emplace_back(cv::Point2i(0, 0));
    corner_top_right.points.emplace_back(cv::Point2i(1, 0));
    corner_top_right.points.emplace_back(cv::Point2i(2, 1));
    corner_top_right.points.emplace_back(cv::Point2i(2, 2));
    corner_top_right.points.emplace_back(cv::Point2i(3, 0));
    corner_top_right.type = CornerFive;
    corner_top_right.solution_dir = cv::Point2i(-1, 0);
    corner_top_right.id = 31;
    corner_top_right.value = 3;

    m_patterns.emplace_back(corner_top_right);

    // CxBA
    //  D
    //  E
    Pattern corner_top_left;
    corner_top_left.points.emplace_back(cv::Point2i(0, 0));
    corner_top_left.points.emplace_back(cv::Point2i(-1, 0));
    corner_top_left.points.emplace_back(cv::Point2i(-2, 1));
    corner_top_left.points.emplace_back(cv::Point2i(-2, 2));
    corner_top_left.points.emplace_back(cv::Point2i(-3, 0));
    corner_top_left.type = CornerFive;
    corner_top_left.solution_dir = cv::Point2i(1, 0);
    corner_top_left.id = 32;
    corner_top_left.value = 3;

    m_patterns.emplace_back(corner_top_left);
}