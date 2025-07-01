#pragma once

namespace TrayIcon
{
	void start();
	void stop();
	void change_icon(bool isConnected);

	const inline wchar_t* tray_icon_window_class = L"NTrayIconWindow";
}