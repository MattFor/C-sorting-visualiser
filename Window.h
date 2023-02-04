#define STRICT

#ifndef C_WINDOW_H_INCLUDED
#define C_WINDOW_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#include "Version.h"
#include "Settings.h"
#include "Graphic.h"


typedef struct {
    Settings settings;

    char keyDown;
    char keyUp;

    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit;
} Window;


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

// Creator
bool initWindow(Window *window, HINSTANCE *hInstance, HINSTANCE *hPrevInstance, LPSTR *lpCmdLine, int *nCmdShow);


#endif // C_WINDOW_H_INCLUDED
