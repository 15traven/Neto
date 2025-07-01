#include "tray_icon.h"
#include "helpers.h"
#include <iostream>
#include <thread>
#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg{};

	std::thread verify_connection_thread(Helpers::verify_connection);
	TrayIcon::start();
	
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	verify_connection_thread.detach();
	TrayIcon::stop();

	return 0;
}