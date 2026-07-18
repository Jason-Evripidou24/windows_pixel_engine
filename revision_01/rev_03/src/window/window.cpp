// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
#include <windows.h>
#include <windowsx.h>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "window.hpp"

#include "../backbuffer/backbuffer.hpp"
#include "../input/input.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch(msg)
    {
        case WM_CLOSE:

        case WM_DESTROY:
        {
            if(window)
            {
                window->m_running = false;
            }
            PostQuitMessage(0);
            return 0;
        }

        case WM_SIZE:
        {
            if(window)
            {
                int width  = LOWORD(l_param);
                int height = HIWORD(l_param);

                if(width > 0 && height > 0)
                {
                    window->onResize(width, height);
                }
            }
            return 0;
        }

        case WM_KEYDOWN:
        {
            if(window)
            {
                window->m_input.setKey((int)w_param, true);
            }
            return 0;
        }

        case WM_KEYUP:
        {
            if(window)
            {
                window->m_input.setKey((int)w_param, false);
            }
            return 0;
        }

        case WM_MOUSEMOVE:
        {
            if(window)
            {
                int x = GET_X_LPARAM(l_param);
                int y = GET_Y_LPARAM(l_param);
                window->m_input.setMousePos(x, y);
            }
            return 0;
        }

        case WM_LBUTTONDOWN:
        {
            if(window)
            {
                window->m_input.setMouseButton(0, true);
            }
            return 0;
        }

        case WM_LBUTTONUP:
        {
            if(window)
            {
                window->m_input.setMouseButton(0, false);
            }
            return 0;
        }

        case WM_RBUTTONDOWN:
        {
            if(window)
            {
                window->m_input.setMouseButton(1, true);
            }
            return 0;
        }

        case WM_RBUTTONUP:
        {
            if(window)
            {
                window->m_input.setMouseButton(1, false);
            }
            return 0;
        }
    }

    return DefWindowProc(hwnd, msg, w_param, l_param);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Window::Window()
{
    m_width  = 0;
    m_height = 0;

    m_backbuffer_pixel_size = 0;

    m_hwnd = nullptr;
    m_dc   = nullptr;

    m_running = false;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Window::~Window()
{
    this->destroy();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Window::onResize(int width, int height)
{
    if(width == m_width && height == m_height) { return; }

    m_width  = width;
    m_height = height;

    m_backbuffer.resize(m_width / m_backbuffer_pixel_size, m_height / m_backbuffer_pixel_size);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Window::create(const wchar_t* title, int width, int height, int backbuffer_pixel_size, HINSTANCE h_instance)
{
    m_width = width;
    m_height = height;

    m_backbuffer_pixel_size = backbuffer_pixel_size;
    if(m_backbuffer_pixel_size < 1) { m_backbuffer_pixel_size = 1; }

    WNDCLASS wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = h_instance;
    wc.lpszClassName = L"PixelEngineWindow";

    RegisterClass(&wc);

    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    m_hwnd = CreateWindowEx
    (
        0,
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        h_instance,
        nullptr
    );

    if(m_hwnd == nullptr) { return false; }

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);

    ShowWindow(m_hwnd, SW_SHOW);

    m_dc = GetDC(m_hwnd);

    m_backbuffer.resize(m_width / m_backbuffer_pixel_size, m_height / m_backbuffer_pixel_size);
    m_input = Input();

    m_running = true;

    return true;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Window::destroy()
{
    m_width  = 0;
    m_height = 0;

    m_backbuffer_pixel_size = 0;

    if(m_dc != nullptr)
    {
        ReleaseDC(m_hwnd, m_dc);
        m_dc = nullptr;
    }

    if(m_hwnd != nullptr)
    {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }

    m_backbuffer.freeBuffers();

    m_running = false;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Window::processMessages()
{
    MSG msg;

    while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        if(msg.message == WM_QUIT)
        {
            m_running = false;
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return m_running;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Window::present()
{
    if(m_dc == nullptr) { return; }

    m_backbuffer.present
    (
        m_dc,
        m_width,
        m_height
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //