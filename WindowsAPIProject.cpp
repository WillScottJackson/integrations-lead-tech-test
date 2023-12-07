// WindowsAPIProject.cpp : Defines the entry point for the application.
//
#include "WindowsAPIProject.h"
#include "Logging.h"

auto windowWidth = MIN_WINDOW_WIDTH;
auto windowHeight = MIN_WINDOW_HEIGHT;
auto windowX = 0;
auto windowY = 0;

int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	// TODO: Place code here.
	const std::string logFilename = "Log.txt";
	Logging logFile = Logging(logFilename);

	logFile.Log(Logging::LoggingLevel::info, __func__, "Application Starting");

	// Attempt to open a .ini file containing the width, height, x and y coordinates of the window 
	constexpr auto configFile		= _T("C://Users//willi//integrations-lead-tech-test//config.ini");
	constexpr auto settingsSection	= _T("Settings");
	constexpr auto windowWidthTag	= _T("WindowWidth");
	constexpr auto windowHeightTag	= _T("WindowHeight");
	constexpr auto windowXTag		= _T("WindowX");
	constexpr auto windowYTag		= _T("WindowY");

	// Had to retarget to C++17 minimum for this feature
	if (!std::filesystem::exists(configFile))
	{
		std::fstream config(configFile, std::ios::out | std::ios::in);
		config.close();
	}
		
	windowWidth = GetPrivateProfileInt(settingsSection, windowWidthTag, MIN_WINDOW_WIDTH, configFile);
	windowHeight = GetPrivateProfileInt(settingsSection, windowHeightTag, MIN_WINDOW_HEIGHT, configFile);
	windowX = GetPrivateProfileInt(settingsSection, windowXTag, MIN_WINDOW_HEIGHT, configFile);
	windowY = GetPrivateProfileInt(settingsSection, windowYTag, MIN_WINDOW_HEIGHT, configFile);

	// Initialize global strings
	LoadStringW( hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING );
	LoadStringW( hInstance, IDC_WINDOWSAPIPROJECT, szWindowClass, MAX_LOADSTRING );
	MyRegisterClass( hInstance );

	// Perform application initialization:
	if ( !InitInstance( hInstance, nCmdShow ) )
	{
		return static_cast<int>(FALSE);
	}

	auto hAccelTable = LoadAccelerators( hInstance, MAKEINTRESOURCE( IDC_WINDOWSAPIPROJECT ) );

	MSG msg;

	// Main message loop:
	while ( GetMessage( &msg, nullptr, 0, 0 ) )
	{
		if ( !TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	auto str = std::to_wstring(windowWidth);
	LPCWSTR w = str.c_str();
	WritePrivateProfileString(settingsSection, windowWidthTag, w, configFile);
	str = std::to_wstring(windowHeight);
	w = str.c_str();
	WritePrivateProfileString(settingsSection, windowHeightTag, w, configFile);
	str = std::to_wstring(windowX);
	w = str.c_str();
	WritePrivateProfileString(settingsSection, windowXTag, w, configFile);
	str = std::to_wstring(windowY);
	w = str.c_str();
	WritePrivateProfileString(settingsSection, windowYTag, w, configFile);

	return static_cast<int>(msg.wParam);
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass( HINSTANCE hInstance )
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_WINDOWSAPIPROJECT ) );
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW( IDC_WINDOWSAPIPROJECT );
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	return RegisterClassExW( &wcex );
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
	hInst = hInstance; // Store instance handle in our global variable

	auto hWnd = CreateWindowW( szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		windowX, windowY, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr );

	if ( !hWnd )
	{
		return FALSE;
	}

	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD( wParam );
		// Parse the menu selections:
		switch ( wmId )
		{
		case IDM_ABOUT:
			DialogBox( hInst, MAKEINTRESOURCE( IDD_ABOUTBOX ), hWnd, About );
			break;
		case IDM_EXIT:
			DestroyWindow( hWnd );
			break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint( hWnd, &ps );
		// Some drawing code that uses hdc here...
		EndPaint( hWnd, &ps );
	}
	break;
	case WM_DESTROY:
		RECT rect;
		// Get the current dimensions and positions of the windows before it closes to write out to the config file
		GetWindowRect(hWnd, &rect);
		windowWidth = rect.right - rect.left;
		windowHeight = rect.bottom - rect.top;
		windowX = rect.left;
		windowY = rect.top;
		PostQuitMessage( WM_QUIT );
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return IDOK;
}

// Message handler for about box.
INT_PTR CALLBACK About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	UNREFERENCED_PARAMETER( lParam );
	switch ( message )
	{
	case WM_INITDIALOG:
		return static_cast<INT_PTR>(TRUE);

	case WM_COMMAND:
		if ( LOWORD( wParam ) == IDOK || LOWORD( wParam ) == IDCANCEL )
		{
			EndDialog( hDlg, LOWORD( wParam ) );
			return static_cast<INT_PTR>(TRUE);
		}
		break;
	}
	return static_cast<INT_PTR>(FALSE);
}
