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
#include "../window.hpp"
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
                    window->resize(width, height);
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