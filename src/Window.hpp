#ifndef BEJEWELED_WINDOW
#define BEJEWELED_WINDOW

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <Windows.h>

#include "Pattern.hpp"

using namespace cv;

class Window
{
public:
    Window();

    void start();

    static const int GAME_RIGHT_PADDING;
    static const int WINDOW_RIGHT_PADDING;

    static const int GAME_TOP_PADDING;
    static const int WINDOW_TOP_PADDING;

    static const int GAME_TILE_SIZE;
    static const int GAME_TILE_PADDING;

private:
    HWND m_window;
    Mat m_mat;
    Patterns m_patterns;

    int m_width;
    int m_height;
    
    bool m_stop;

    void update();
    void draw();

    void window_to_mat();
    void get_mouse_position(const int x, const int y, int& outX, int& outY);
    void mouse_click_drag(const int start_x, const int start_y, const int distance_x, const int distance_y);
};

#endif
