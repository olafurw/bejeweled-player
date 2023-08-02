#pragma once

#define NOMINMAX
#include <Windows.h>

void mouse_click_drag(HWND window, const int start_x, const int start_y, const int distance_x, const int distance_y);