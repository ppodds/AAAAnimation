#pragma once
#include <Windows.h>

class ConsoleController
{
public:
	ConsoleController();
	void clear_screen();
	void top();
	void set_console_mode();
	void set_console_font();
	void set_console_screen_buffer(short width, short height);
private:
	HANDLE stdout_handle;
};