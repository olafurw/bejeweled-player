#include "Solver.hpp"

#include "Window.hpp"

#include <opencv2/imgproc.hpp>
#include <iostream>

using board_t = std::array<std::array<char, 8>, 8>;

bool point_inside(const cv::Point2i & point) {
    return (point.x >= 0 && point.x <= 7 &&
            point.y >= 0 && point.y <= 7);
}

char detect_gem(const cv::Vec4b & inColor) {
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

board_t screen_to_board(const cv::Mat & screen) {
    board_t board;

    const int startX = GAME_RIGHT_PADDING;
    int y = GAME_TOP_PADDING;

    for (int i = 0; i < 8; ++i) {
        int x = startX;

        for (int j = 0; j < 8; ++j) {
            const cv::Vec4b color = screen.at<cv::Vec4b>(y + GAME_TILE_PADDING, x + GAME_TILE_PADDING);

            board[i][j] = detect_gem(color);
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

cv::Scalar scalarBGR2HSV(uchar B, uchar G, uchar R) {
    cv::Mat rgb;
    cv::Mat hsv(1, 1, CV_8UC3, cv::Scalar(B, G, R));
    cv::cvtColor(hsv, rgb, CV_BGR2HSV);
    return cv::Scalar(rgb.data[0], rgb.data[1], rgb.data[2]);
}

std::optional<Solution> solve(const Patterns & patterns, cv::Mat & screen) {
    const board_t board = screen_to_board(screen);

    // visualization
    std::array<std::array<cv::Scalar, 8>, 8> colors;
    std::array<std::array<cv::Scalar, 8>, 8> hsvColors;

    std::vector<Solution> solutions;

    {
        const int startX = GAME_RIGHT_PADDING;
        int y = GAME_TOP_PADDING;

        for (int i = 0; i < 8; ++i) {
            int x = startX;

            for (int j = 0; j < 8; ++j) {
                const char gem = board[i][j];

                const cv::Point rectStart = cv::Point(x, y);
                const cv::Point rectEnd = cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE);

                cv::Mat gemMat;
                screen(cv::Rect(
                    rectStart.x + CENTER_GAME_TILE_OFFSET,
                    rectStart.y + CENTER_GAME_TILE_OFFSET,
                    CENTER_GAME_TILE_SIZE,
                    CENTER_GAME_TILE_SIZE)
                ).copyTo(gemMat);

                colors[i][j] = cv::mean(gemMat);
                hsvColors[i][j] = scalarBGR2HSV(colors[i][j][0], colors[i][j][1], colors[i][j][2]);
                //std::cout << s[0] << ' ' << s[1] << ' ' << s[2] << std::endl;
                //std::cout << s2[0] << ' ' << s2[1] << ' ' << s2[2] << std::endl;

                x += GAME_TILE_SIZE;
            }
            y += GAME_TILE_SIZE;
        }
    }

    {
        const int startX = GAME_RIGHT_PADDING;
        int y = GAME_TOP_PADDING;

        for (int i = 0; i < 8; ++i) {
            int x = startX;

            for (int j = 0; j < 8; ++j) {
                const char gem = board[i][j];

                const cv::Point rectStart = cv::Point(x, y);
                const cv::Point rectEnd = cv::Point(x + GAME_TILE_SIZE, y + GAME_TILE_SIZE);

                if (hsvColors[i][j][0] > 0.0) {
                    rectangle(screen, rectStart, rectEnd, colors[i][j], -1);
                }

                x += GAME_TILE_SIZE;

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
            }

            y += GAME_TILE_SIZE;
        }
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
