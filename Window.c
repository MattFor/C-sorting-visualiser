#define STRICT

#include "Window.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    // Get the device context (DC)
    *hDC = GetDC(hwnd);

    // Set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    // Create and enable the render context (RC)
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

bool initWindow(Window *window, HINSTANCE *hInstance,
                   HINSTANCE *hPrevInstance,
                   LPSTR *lpCmdLine,
                   int *nCmdShow)
{
    /// Register window class
    window->wcex.cbSize = sizeof(WNDCLASSEX);
    window->wcex.style = CS_OWNDC;
    window->wcex.lpfnWndProc = WindowProc;
    window->wcex.cbClsExtra = 0;
    window->wcex.cbWndExtra = 0;
    window->wcex.hInstance = hInstance;
    window->wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window->wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    window->wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    window->wcex.lpszMenuName = NULL;
    window->wcex.lpszClassName = "OpenGLWindow";
    window->wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&window->wcex))
        return false;

    window->bQuit = FALSE;

    // Cache settings from the ini configuration file
    getSettings(&window->settings);
    applyDefaultSettings(&window->settings);


    // Construct OpenGL window display name
    LPCSTR appName = malloc(
          sizeof("Sort visualizer v.") +
          sizeof(FULLVERSION_STRING) +
          sizeof(" by MattFor#9884")
    );

    strcpy(appName, "Sort visualizer v.");
    strcat(appName, FULLVERSION_STRING);
    strcat(appName, " by MattFor#9884");


    /// Create main window
    window->hwnd = CreateWindowEx(
        0,
        "OpenGLWindow",
        appName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        window->settings.width,
        window->settings.height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(window->hwnd, nCmdShow);

    /// Enable OpenGL for the window
    EnableOpenGL(window->hwnd, &window->hDC, &window->hRC);

    /// Start the random timer.
    srand(time(NULL));

    /// Set default keys
    window->keyDown = 0;
    window->keyUp = 0;

    /// Create a traditional coordinate grid
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, window->settings.width, 0, window->settings.height, -1.0f, 1.0f);

    return true;
}
