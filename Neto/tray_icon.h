#pragma once

namespace TrayIcon
{
	void start();
	void stop();

	const inline wchar_t* tray_icon_window_class = L"NTrayIconWindow";
}