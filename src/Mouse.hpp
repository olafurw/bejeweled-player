#pragma once

#define NOMINMAX
#include <Windows.h>

void get_mouse_position(HWND window, const int x, const int y, int & outX, int & outY);
void mouse_click_drag(HWND window, const int start_x, const int start_y, const int distance_x, const int distance_y);