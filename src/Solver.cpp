#include "Solver.hpp"

#include "Window.hpp"

Solver::Solver(cv::Mat & screen) {
    const int startX = GAME_RIGHT_PADDING;
    int y = GAME_TOP_PADDING;

    for (int i = 0; i < 8; ++i) {
        int x = startX;

        for (int j = 0; j < 8; ++j) {
            const cv::Vec4b color = screen.at<cv::Vec4b>(y + GAME_TILE_PADDING, x + GAME_TILE_PADDING);

            m_board[i][j] = detect_gem(color);

            if (m_board[i][j] == 'R') {
                rectangle(screen, cv::Point(x, y), cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE), cv::Scalar(0.0f, 0.0f, 255.0f), -1);
            } else if (m_board[i][j] == 'G') {
                rectangle(screen, cv::Point(x, y), cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE), cv::Scalar(0.0f, 255.0f, 0.0f), -1);
            } else if (m_board[i][j] == 'B') {
                rectangle(screen, cv::Point(x, y), cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE), cv::Scalar(255.0f, 0.0f, 0.0f), -1);
            } else if (m_board[i][j] == 'O') {
                rectangle(screen, cv::Point(x, y), cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE), cv::Scalar(0.0f, 100.0f, 255.0f), -1);
            } else if (m_board[i][j] == 'Y') {
                rectangle(screen, cv::Point(x, y), cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE), cv::Scalar(0.0f, 255.0f, 255.0f), -1);
            } else if (m_board[i][j] == 'P') {
                rectangle(screen, cv::Point(x, y), cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE), cv::Scalar(255.0f, 0.0f, 255.0f), -1);
            } else if (m_board[i][j] == 'W') {
                rectangle(screen, cv::Point(x, y), cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE), cv::Scalar(255.0f, 255.0f, 255.0f), -1);
            }

            x += GAME_TILE_SIZE;
        }

        y += GAME_TILE_SIZE;
    }
}

bool Solver::solve(const Patterns & patterns) {
    std::vector<Solution> solutions;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const char gem = m_board[i][j];

            for (const Pattern & pattern : patterns.m_patterns) {
                if (match(i, j, pattern)) {
                    const cv::Point2i & C_point = pattern.points.back();

                    solutions.emplace_back(Solution{
                        cv::Point2i(C_point.x + j, C_point.y + i),
                        pattern.solution_dir,
                        pattern.value
                    });
                }
            }
        }
    }

    if (solutions.empty()) {
        return false;
    }

    std::sort(
      solutions.begin(),
      solutions.end(),
      [](const Solution & a, const Solution & b) {
          if (a.value == b.value) {
              return a.C_point.y < b.C_point.y;
          }

          return a.value > b.value;
      });

    m_solution = solutions.at(0);
    return true;
}

bool Solver::point_inside(const cv::Point2i & point) {
    return (point.x >= 0 && point.x <= 7 &&
            point.y >= 0 && point.y <= 7);
}

bool Solver::match(const int i, const int j, const Pattern & pattern) {
    if (pattern.points.empty()) {
        return false;
    }

    const cv::Point2i A_point(pattern.points[0].x + j, pattern.points[0].y + i);
    const char A_gem = m_board[A_point.y][A_point.x];

    for (auto & point : pattern.points) {
        const cv::Point2i real_point(point.x + j, point.y + i);
        if (!point_inside(real_point)) {
            return false;
        }

        const char gem = m_board[real_point.y][real_point.x];
        if (gem != A_gem) {
            return false;
        }
    }

    return true;
}

char Solver::detect_gem(const cv::Vec4b & inColor) {
    const double & blue = inColor[0];
    const double & green = inColor[1];
    const double & red = inColor[2];

    // White
    if (blue > 233.0f && red > 235.0f && green > 233.0f) {
        return 'W';
    }

    // Red x
    if (blue > 55.0f && blue < 58.0f && green > 23.0f && green < 28.0f && red > 247.0f) {
        return 'R';
    }

    // Green x
    if (blue > 127.0f && blue < 135.0f && green > 245.0f && red > 79.0f && red < 92.0f) {
        return 'G';
    }

    // Blue x
    if (blue > 247.0f && green > 127.0f && green < 135.0f && red > 15.0f && red < 20.0f) {
        return 'B';
    }

    // Purple x
    if (blue > 239.0f && blue < 245.0f && green > 15.0f && green < 19.0f && red > 239.0f && red < 245.0f) {
        return 'P';
    }

    // Yellow
    if (blue > 31.0f && blue < 37.0f && green > 247.0f && green < 250.0f && red > 247.0f && red < 255.0f) {
        return 'Y';
    }

    // Orange x
    if (blue > 119.0f && blue < 130.0f && green > 243.0f && green < 248.0f && red > 247.0f) {
        return 'O';
    }

    return '-';
}