#include "Window.h"
#include <iostream>
#define ID_BTN_YES 0
#define ID_BTN_NO 1

using namespace std;

HWND buttonYes, buttonNo, mainText;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return (0);
		case WM_CREATE: {
			mainText = CreateWindowA("STATIC", "Are U Dumb?", WS_VISIBLE | WS_CHILD | SS_LEFT, 290, 150, 100, 30, hWnd, NULL, GetModuleHandle(NULL), NULL);
			buttonYes = CreateWindowA("BUTTON", "Yes", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 250, 100, 30, hWnd, (HMENU)ID_BTN_YES, GetModuleHandle(NULL), NULL);
			buttonNo = CreateWindowA("BUTTON", "No", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 400, 250, 100, 30, hWnd, (HMENU)ID_BTN_NO, GetModuleHandle(NULL), NULL);
			break;
		}
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_BTN_YES:
					::MessageBoxA(hWnd, "I knew it!", ":)", MB_OK);
					break;
				case ID_BTN_NO:
					::MessageBoxA(hWnd, "Try again, I was not listening :/", ":/", MB_OK);
					break;
			}
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window() : m_hInstance(GetModuleHandle(nullptr)) {
	const wchar_t* CLASS_NAME = L"Sik Window Class";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int width = 640;
	int height = 480;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"HELLO",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window() {
	const wchar_t* CLASS_NAME = L"Sik Window Class";

	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessage() {
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}
