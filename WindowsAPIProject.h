#pragma once

#include "resource.h"
#include "framework.h"

constexpr auto MAX_LOADSTRING = 100;
constexpr auto MIN_WINDOW_WIDTH = 200;
constexpr auto MIN_WINDOW_HEIGHT = 150;

// Global Variables:
HINSTANCE hInst;                                  // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);