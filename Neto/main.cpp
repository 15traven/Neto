#include "tray_icon.h"
#include "helpers.h"
#include "logger.h"
#include "history.h"
#include <iostream>
#include <thread>
#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	Logger::init("Main");
	HistoryManager::init();

	std::thread verify_connection_thread(Helpers::verify_connection);
	TrayIcon::start();

	MSG msg{};
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	verify_connection_thread.detach();
	TrayIcon::stop();

	return 0;
}