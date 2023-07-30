#include "Mouse.hpp"

void get_mouse_position(HWND window, const int x, const int y, int & outX, int & outY) {
    RECT rect;
    GetWindowRect(window, &rect);

    POINT cursor;
    GetCursorPos(&cursor);

    const float screenX = 65535.0f / GetSystemMetrics(SM_CXSCREEN);
    const float screenY = 65535.0f / GetSystemMetrics(SM_CYSCREEN);

    outX = static_cast<int>((rect.left + x) * screenX);
    outY = static_cast<int>((rect.top + y) * screenY);
}

// Heavily modified function from
// http://stackoverflow.com/questions/11276233/how-to-move-mouse-with-c
// author: http://stackoverflow.com/users/783014/jerkan
void mouse_click_drag(HWND window, const int start_x, const int start_y, const int distance_x, const int distance_y) {
    int screen_start_x = 0;
    int screen_start_y = 0;
    get_mouse_position(window, start_x, start_y, screen_start_x, screen_start_y);

    INPUT move = { 0 };
    move.type = INPUT_MOUSE;
    move.mi.dx = screen_start_x;
    move.mi.dy = screen_start_y;
    move.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    SendInput(1, &move, sizeof(INPUT));

    INPUT click = { 0 };
    click.type = INPUT_MOUSE;
    click.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &click, sizeof(INPUT));

    int screen_end_x = 0;
    int screen_end_y = 0;
    get_mouse_position(window, start_x + distance_x, start_y + distance_y, screen_end_x, screen_end_y);

    INPUT swipe = { 0 };
    swipe.type = INPUT_MOUSE;
    swipe.mi.dx = screen_end_x;
    swipe.mi.dy = screen_end_y;
    swipe.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &swipe, sizeof(INPUT));

    INPUT release = { 0 };
    release.type = INPUT_MOUSE;
    release.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &release, sizeof(INPUT));
}