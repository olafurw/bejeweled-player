#pragma once

#define NOMINMAX
#include <Windows.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Pattern.hpp"

const int GAME_RIGHT_PADDING = 261;
const int WINDOW_RIGHT_PADDING = 269;

const int GAME_TOP_PADDING = 37;
const int WINDOW_TOP_PADDING = 67;

const int GAME_TILE_SIZE = 64;
const int GAME_TILE_PADDING = 31;

class Window {
  public:
    Window();
    void start();

  private:
    HWND m_window;
    cv::Mat m_mat;
    Patterns m_patterns;

    int m_width;
    int m_height;

    bool m_stop;

    void update();
    void draw();

    void window_to_mat();
};
