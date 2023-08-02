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
    cv::createTrackbar("Threshold", "game", &m_threshold, 100, onTrackbarChange, this);

    m_purple = cv::imread("../purple.png", cv::IMREAD_UNCHANGED);
    m_yellow = cv::imread("../yellow.png", cv::IMREAD_UNCHANGED);
    m_yellow_fire = cv::imread("../yellow_fire.png", cv::IMREAD_UNCHANGED);
    m_red = cv::imread("../red.png", cv::IMREAD_UNCHANGED);
    m_red_fire = cv::imread("../red_fire.png", cv::IMREAD_UNCHANGED);
    m_red_shiny = cv::imread("../red_shiny.png", cv::IMREAD_UNCHANGED);

    if (SetForegroundWindow(m_window) == 0) {
        return;
    }
    
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
    std::vector<cv::Point> matchLocations;
    {
        cv::Mat correlationMap;
        int matchMethod = CV_TM_CCOEFF_NORMED; // You can choose a different matching method if needed
        cv::matchTemplate(m_mat, m_red, correlationMap, matchMethod);

        double threshold = static_cast<double>(m_threshold / 100.0);
        cv::Mat thresholdMap;
        cv::threshold(correlationMap, thresholdMap, threshold, 1.0, cv::THRESH_TOZERO);

        std::vector<cv::Point> tmpLocations;
        cv::findNonZero(thresholdMap, tmpLocations);

        matchLocations = filterPoints(tmpLocations, 30);

        for (const auto & loc : matchLocations) {
            cv::Rect boundingBox(loc.x, loc.y, m_red.cols, m_red.rows);
            cv::rectangle(m_mat, boundingBox, cv::Scalar(0, 255, 0), 2);
        }
    }
    {
        cv::Mat correlationMap;
        int matchMethod = CV_TM_CCOEFF_NORMED; // You can choose a different matching method if needed
        cv::matchTemplate(m_mat, m_red_fire, correlationMap, matchMethod);

        double threshold = static_cast<double>(m_threshold / 100.0);
        cv::Mat thresholdMap;
        cv::threshold(correlationMap, thresholdMap, threshold, 1.0, cv::THRESH_TOZERO);

        std::vector<cv::Point> tmpLocations;
        cv::findNonZero(thresholdMap, tmpLocations);

        matchLocations.insert(matchLocations.end(), tmpLocations.begin(), tmpLocations.end());
        matchLocations = filterPoints(matchLocations, 30);

        for (const auto & loc : matchLocations) {
            cv::Rect boundingBox(loc.x, loc.y, m_red_fire.cols, m_red_fire.rows);
            cv::rectangle(m_mat, boundingBox, cv::Scalar(0, 255, 0), 2);
        }
    }
    {
        cv::Mat correlationMap;
        int matchMethod = CV_TM_CCOEFF_NORMED; // You can choose a different matching method if needed
        cv::matchTemplate(m_mat, m_red_shiny, correlationMap, matchMethod);

        double threshold = static_cast<double>(m_threshold / 100.0);
        cv::Mat thresholdMap;
        cv::threshold(correlationMap, thresholdMap, threshold, 1.0, cv::THRESH_TOZERO);

        std::vector<cv::Point> tmpLocations;
        cv::findNonZero(thresholdMap, tmpLocations);

        matchLocations.insert(matchLocations.end(), tmpLocations.begin(), tmpLocations.end());
        matchLocations = filterPoints(matchLocations, 30);

        for (const auto & loc : matchLocations) {
            cv::Rect boundingBox(loc.x, loc.y, m_red_shiny.cols, m_red_shiny.rows);
            cv::rectangle(m_mat, boundingBox, cv::Scalar(0, 255, 0), 2);
        }
    }

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
