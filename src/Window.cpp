#include "Window.hpp"

#include "Solver.hpp"

const int Window::GAME_RIGHT_PADDING = 261;
const int Window::WINDOW_RIGHT_PADDING = 269;

const int Window::GAME_TOP_PADDING = 37;
const int Window::WINDOW_TOP_PADDING = 67;

const int Window::GAME_TILE_SIZE = 64;
const int Window::GAME_TILE_PADDING = 31;

Window::Window()
{
    m_window = FindWindow(NULL, "Bejeweled 3");
    m_stop = false;
}

void Window::start()
{
    for(int i = 0; i < 2000; ++i)
    {
        update();
        draw();
    }
}

void Window::update()
{
    window_to_mat();

    Solver s(m_mat);
    if(s.solve(m_patterns))
    {
        const Solution& solution = s.m_solution;
        
        const int x = Window::WINDOW_RIGHT_PADDING + (solution.C_point.x * Window::GAME_TILE_SIZE) + Window::GAME_TILE_PADDING;
        const int y = Window::WINDOW_TOP_PADDING + (solution.C_point.y * Window::GAME_TILE_SIZE) + Window::GAME_TILE_PADDING;

        mouse_click_drag(x, y, solution.direction.x * Window::GAME_TILE_SIZE, solution.direction.y * Window::GAME_TILE_SIZE);
    }
}

void Window::draw()
{
    imshow("GAME", m_mat);
    if(cvWaitKey(1) == 27)
    {
        m_stop = true;
    }
}

// http://stackoverflow.com/questions/14148758/how-to-capture-the-desktop-in-opencv-ie-turn-a-bitmap-into-a-mat
// user396483 <3
void Window::window_to_mat()
{
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

void Window::get_mouse_position(const int x, const int y, int& outX, int& outY)
{
    RECT rect;
    GetWindowRect(m_window, &rect);

    POINT cursor;
    GetCursorPos(&cursor);

    outX = (rect.left + x) * static_cast<float>(65535.0f / GetSystemMetrics(SM_CXSCREEN));
    outY = (rect.top + y) * static_cast<float>(65535.0f / GetSystemMetrics(SM_CYSCREEN));
}

// Heavily modified function from
// http://stackoverflow.com/questions/11276233/how-to-move-mouse-with-c
// author: http://stackoverflow.com/users/783014/jerkan
void Window::mouse_click_drag(const int start_x, const int start_y, const int distance_x, const int distance_y)
{ 
    int screen_start_x = 0;
    int screen_start_y = 0;
    get_mouse_position(start_x, start_y, screen_start_x, screen_start_y);

    INPUT move = {0};
    move.type = INPUT_MOUSE;

    move.mi.dx = screen_start_x;
    move.mi.dy = screen_start_y;

    move.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

    SendInput(1, &move, sizeof(INPUT));

    INPUT click = {0};
    click.type = INPUT_MOUSE;

    // set move cursor directly and left click
    click.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    SendInput(1, &click, sizeof(INPUT));

    int screen_end_x = 0;
    int screen_end_y = 0;
    get_mouse_position(start_x + distance_x, start_y + distance_y, screen_end_x, screen_end_y);

    INPUT swipe = {0};
    swipe.type = INPUT_MOUSE;

    swipe.mi.dx = screen_end_x;
    swipe.mi.dy = screen_end_y;

    // set move cursor directly and left click
    swipe.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &swipe, sizeof(INPUT));

    INPUT release = {0};
    release.type = INPUT_MOUSE;

    // set move cursor directly and left click
    release.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, &release, sizeof(INPUT));
}