#include "Window.hpp"

#include "Mouse.hpp"
#include "Solver.hpp"

Window::Window() {
    m_window = FindWindow(NULL, "Bejeweled 3");
    m_stop = false;
    m_width = 0;
    m_height = 0;
}

void Window::start() {
    if (!m_window) {
        return;
    }

    for (int i = 0; i < 20; ++i) {
        update();
        draw();
        Sleep(200);
    }
}

void Window::update() {
    window_to_mat();

    Solver s(m_mat);
    if (!s.solve(m_patterns)) {
        return;
    }

    const Solution & solution = s.m_solution;
    const int x = WINDOW_RIGHT_PADDING + (solution.C_point.x * GAME_TILE_SIZE) + GAME_TILE_PADDING;
    const int y = WINDOW_TOP_PADDING + (solution.C_point.y * GAME_TILE_SIZE) + GAME_TILE_PADDING;
    mouse_click_drag(m_window, x, y, solution.direction.x * GAME_TILE_SIZE, solution.direction.y * GAME_TILE_SIZE);
}

void Window::draw() {
    imshow("GAME", m_mat);
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
