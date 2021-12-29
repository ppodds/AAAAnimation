#include "console_controller.h"
#include <iostream>

ConsoleController::ConsoleController()
{
	stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

// clear screen buffer until the curser position
void ConsoleController::clear_screen()
{
	std::cout << "\x1B[2J";
}

// set the cursor position to the top of the screen buffer
void ConsoleController::top()
{
	std::cout << "\x1B[H";
}

void ConsoleController::set_console_mode()
{
	DWORD mode = 0;
	GetConsoleMode(stdout_handle, &mode);
	mode = mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(stdout_handle, mode);
}

// set console font size, weight and family
void ConsoleController::set_console_font()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(stdout_handle, FALSE, &cfi);
	cfi.dwFontSize.Y = 1;
	std::mbstowcs(cfi.FaceName, "Lucida Console", 32);
	// 700 is bold
	cfi.FontWeight = 700;
	SetCurrentConsoleFontEx(stdout_handle, FALSE, &cfi);
}

void ConsoleController::set_console_screen_buffer(short width, short height)
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbi;
	csbi.cbSize = sizeof(csbi);
	GetConsoleScreenBufferInfoEx(stdout_handle, &csbi);
	csbi.dwSize.X = width;
	csbi.dwSize.Y = height;
	csbi.srWindow.Left = 0;
	csbi.srWindow.Top = 0;
	csbi.dwMaximumWindowSize.X = width;
	csbi.dwMaximumWindowSize.Y = height;
	int c = SetConsoleScreenBufferInfoEx(stdout_handle, &csbi);
	COORD screen_buffer_size = { width, height };
	int a = SetConsoleScreenBufferSize(stdout_handle, screen_buffer_size);
	SMALL_RECT console_window = {0, 0, width-1, height-1};
	int b = SetConsoleWindowInfo(stdout_handle, TRUE, &console_window);
	auto e = GetLastError();
	//ResizePseudoConsole()
}

void ConsoleController::set_window_buffer_size(short width, short height)
{
	/*WINDOW_BUFFER_SIZE_RECORD wbsr;
	wbsr.dwSize.X = width;
	wbsr.dwSize.Y = height;
	SetWindowBuffer*/
}
