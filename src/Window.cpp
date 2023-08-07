#include "Window.hpp"

#include "Mouse.hpp"
#include "Solver.hpp"

void onTrackbarChange(int value, void * object) {
    if (!object) {
        return;
    }

    auto w = static_cast<Window *>(object);
    w->m_threshold = value;
}

double distance(const cv::Point & p1, const cv::Point & p2) {
    const int dx = p1.x - p2.x;
    const int dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<cv::Point> filterPoints(const std::vector<cv::Point> & points, int distanceThreshold) {
    std::vector<cv::Point> filteredPoints;

    for (const auto & p1 : points) {
        bool keepPoint = true;

        for (const auto & p2 : filteredPoints) {
            if (distance(p1, p2) < distanceThreshold) {
                keepPoint = false;
                break;
            }
        }

        if (keepPoint) {
            filteredPoints.push_back(p1);
        }
    }

    return filteredPoints;
}

Window::Window() {
    m_window = FindWindow(NULL, "Bejeweled 3");
    m_stop = false;
    m_width = 0;
    m_height = 0;
    m_threshold = 50;
}

void Window::start() {
    if (!m_window) {
        return;
    }

    cv::namedWindow("game", cv::WINDOW_NORMAL);
    
    if (SetForegroundWindow(m_window) == 0) {
        return;
    }
    
    //for (int i = 0; i < 100; ++i) {
    while (true) {
        update();
        draw();
        Sleep(1);
    }
}

void Window::update() {
    window_to_mat();

    const auto solutionOpt = solve(m_patterns, m_mat);
    if (!solutionOpt) {
        return;
    }

    const Solution & solution = solutionOpt.value();
    const int x = WINDOW_RIGHT_PADDING + (solution.C_point.first * GAME_TILE_SIZE) + GAME_TILE_PADDING;
    const int y = WINDOW_TOP_PADDING + (solution.C_point.second * GAME_TILE_SIZE) + GAME_TILE_PADDING;
    //mouse_click_drag(m_window, x, y, solution.direction.first * GAME_TILE_SIZE, solution.direction.second * GAME_TILE_SIZE);
}

void Window::draw() {
    cv::imshow("game", m_mat);
    cv::waitKey(1);
}

// http://stackoverflow.com/questions/14148758/how-to-capture-the-desktop-in-opencv-ie-turn-a-bitmap-into-a-mat
// user396483 <3
void Window::window_to_mat() {
    HDC hwindowDC = GetDC(m_window);
    HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    RECT windowsize;
    GetClientRect(m_window, &windowsize);

    const int height = windowsize.bottom;
    const int width = windowsize.right;

    m_mat.release();
    m_mat.create(height, width, CV_8UC4);
    const auto x = m_mat.type();

    HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    SelectObject(hwindowCompatibleDC, hbwindow);

    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, width, height, SRCCOPY);
    GetDIBits(hwindowDC, hbwindow, 0, height, m_mat.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
}
