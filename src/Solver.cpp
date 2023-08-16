#include "Solver.hpp"

#include "Window.hpp"

#include <opencv2/imgproc.hpp>
#include <iostream>
#include <float.h>

using board_t = std::array<std::array<char, 8>, 8>;

static double hueMax = -DBL_MAX;
static double hueMin = DBL_MAX;
static double satMax = -DBL_MAX;
static double satMin = DBL_MAX;
static double valMax = -DBL_MAX;
static double valMin = DBL_MAX;
static int counter = 0;

bool point_inside(const cv::Point2i & point) {
    return (point.x >= 0 && point.x <= 7 &&
            point.y >= 0 && point.y <= 7);
}

cv::Scalar scalarBGR2HSV(uchar B, uchar G, uchar R) {
    cv::Mat rgb;
    cv::Mat hsv(1, 1, CV_8UC3, cv::Scalar(B, G, R));
    cv::cvtColor(hsv, rgb, CV_BGR2HSV);
    return cv::Scalar(rgb.data[0], rgb.data[1], rgb.data[2]);
}

char detect_gem(const cv::Scalar & hsv, const cv::Scalar & bgr) {
    const double & hue = hsv[0];
    const double & saturation = hsv[1];
    const double & value = hsv[2];

    const double & blue = bgr[0];
    const double & green = bgr[1];
    const double & red = bgr[2];

    // White
    if (hue < 110.0) {
        // White and White Fire
        if (saturation < 10.0) {
            return 'W';
        }

        // White shiny
        if (hue > 90.0 && saturation < 30.0) {
            return 'W';
        }
        // fallthough intentional
    }

    // Testing Purple detection
    if (hue > 150.0 && blue > 100.0 && red > 100.0) {
        return 'P';
    }

    // Blue 97 - 108
    if (hue > 85.0 && hue < 115.0) {
        return 'B';
    }

    // Green 60 - 74
    if (hue > 55.0 && hue < 85.0) {
        return 'G';
    }

    // Purple 146 - 149
    // Purple shiny 121 - 144
    if (hue > 115.0 && hue < 155.0) {
        return 'P';
    }

    // Red
    // Red fire
    if (hue > 170.0) {
        return 'R';
    }

    // Orange
    if (hue < 18.0) {
        return 'O';
    }

    // Yellow
    if (hue > 18.0 && hue < 50.0) {
        return 'Y';
    }

    return '-';
}

board_t screen_to_board(const cv::Mat & screen) {
    board_t board;

    const int startX = GAME_RIGHT_PADDING;
    int y = GAME_TOP_PADDING;

    std::array<std::array<cv::Scalar, 8>, 8> colors;
    std::array<std::array<cv::Scalar, 8>, 8> hsvColors;

    for (int i = 0; i < 8; ++i) {
        int x = startX;

        for (int j = 0; j < 8; ++j) {
            const cv::Point rectStart = cv::Point(x, y);
            const cv::Point rectEnd = cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE);

            cv::Mat gemMat;
            screen(cv::Rect(
                     rectStart.x + CENTER_GAME_TILE_OFFSET,
                     rectStart.y + CENTER_GAME_TILE_OFFSET,
                     CENTER_GAME_TILE_SIZE,
                     CENTER_GAME_TILE_SIZE))
              .copyTo(gemMat);

            const cv::Scalar meanColor = cv::mean(gemMat);
            const cv::Scalar hsvColor = scalarBGR2HSV(meanColor[0], meanColor[1], meanColor[2]);
            board[i][j] = detect_gem(hsvColor, meanColor);

            x += GAME_TILE_SIZE;
        }

        y += GAME_TILE_SIZE;
    }

    return board;
}

bool match(const int i, const int j, const Pattern & pattern, const board_t & board) {
    if (pattern.points.empty()) {
        return false;
    }

    const std::pair<int, int> A_point(pattern.points[0].first + j, pattern.points[0].second + i);
    const char A_gem = board[A_point.second][A_point.first];

    for (auto & point : pattern.points) {
        const cv::Point2i real_point(point.first + j, point.second + i);
        if (!point_inside(real_point)) {
            return false;
        }

        const char gem = board[real_point.y][real_point.x];
        if (gem != A_gem) {
            return false;
        }
    }

    return true;
}

std::optional<Solution> solve(const Patterns & patterns, cv::Mat & screen) {
    const board_t board = screen_to_board(screen);

    std::vector<Solution> solutions;

    const int startX = GAME_RIGHT_PADDING;
    int y = GAME_TOP_PADDING;

    for (int i = 0; i < 8; ++i) {
        int x = startX;

        for (int j = 0; j < 8; ++j) {
            const char gem = board[i][j];

            const cv::Point rectStart = cv::Point(x, y);
            const cv::Point rectEnd = cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE);

            if (gem == 'R') {
                rectangle(screen, rectStart, rectEnd, cv::Scalar(0.0f, 0.0f, 255.0f), -1);
            } else if (gem == 'G') {
                rectangle(screen, rectStart, rectEnd, cv::Scalar(0.0f, 255.0f, 0.0f), -1);
            } else if (gem == 'B') {
                rectangle(screen, rectStart, rectEnd, cv::Scalar(255.0f, 0.0f, 0.0f), -1);
            } else if (gem == 'O') {
                rectangle(screen, rectStart, rectEnd, cv::Scalar(0.0f, 100.0f, 255.0f), -1);
            } else if (gem == 'Y') {
                rectangle(screen, rectStart, rectEnd, cv::Scalar(0.0f, 255.0f, 255.0f), -1);
            } else if (gem == 'P') {
                rectangle(screen, rectStart, rectEnd, cv::Scalar(255.0f, 0.0f, 255.0f), -1);
            } else if (gem == 'W') {
                rectangle(screen, rectStart, rectEnd, cv::Scalar(255.0f, 255.0f, 255.0f), -1);
            }

            for (const Pattern & pattern : patterns.m_patterns) {
                if (!match(i, j, pattern, board)) {
                    continue;
                }

                const auto & C_point = pattern.points.back();

                solutions.emplace_back(Solution{
                  { C_point.first + j, C_point.second + i },
                  pattern.solution_dir,
                  pattern.value });
            }

            x += GAME_TILE_SIZE;
        }
        y += GAME_TILE_SIZE;
    }

    if (solutions.empty()) {
        return {};
    }

    std::sort(
      solutions.begin(),
      solutions.end(),
      [](const Solution & a, const Solution & b) {
          if (a.value == b.value) {
              return a.C_point.second < b.C_point.second;
          }

          return a.value > b.value;
      });

    return solutions.at(0);
}
