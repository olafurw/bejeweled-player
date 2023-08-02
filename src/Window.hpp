#pragma once

#define NOMINMAX
#include <Windows.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/types_c.h"

#include "Pattern.hpp"

constexpr int GAME_RIGHT_PADDING = 261;
constexpr int WINDOW_RIGHT_PADDING = 269;

constexpr int GAME_TOP_PADDING = 37;
constexpr int WINDOW_TOP_PADDING = 67;

constexpr int GAME_TILE_SIZE = 64;
constexpr int GAME_TILE_PADDING = 31;

class Window {
  public:
    Window();
    void start();
    int m_threshold;

  private:
    HWND m_window;
    cv::Mat m_mat;
    cv::Mat m_purple;
    cv::Mat m_yellow;
    cv::Mat m_yellow_fire;
    cv::Mat m_red;
    cv::Mat m_red_fire;
    cv::Mat m_red_shiny;
    Patterns m_patterns;

    int m_width;
    int m_height;

    bool m_stop;

    void update();
    void draw();

    void window_to_mat();
};
