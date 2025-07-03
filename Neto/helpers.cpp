#include "helpers.h"
#include "tray_icon.h"
#include <iostream>
#include <windows.h>
#include <curl/curl.h>

using namespace std;

namespace
{
	bool check_url(const std::string url)
	{
		CURL* curl = curl_easy_init();
		if (!curl)
		{
			return false;
		}

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		return (res == CURLE_OK);
	}
}

namespace Helpers {
	void verify_connection()
	{
		while (true)
		{
			bool status = check_url("https://google.com")
				? true
				: (check_url("https://github.com") ? true : false);

			TrayIcon::change_icon(status);
			Sleep(10000);
		}
	}

	void show_settings()
	{
		STARTUPINFO startup_info = { sizeof(startup_info) };
		PROCESS_INFORMATION process_info = { 0 };
		
		wstring executable_path = L"NetoSettings.exe";
		WCHAR command_line[MAX_PATH];
		wcscpy_s(command_line, executable_path.c_str());

		BOOL result = CreateProcessW(
			nullptr,
			command_line,
			nullptr,
			nullptr,
			FALSE,
			0,
			nullptr,
			nullptr,
			&startup_info,
			&process_info);

		if (result)
		{
			if (process_info.hProcess)
			{
				CloseHandle(process_info.hProcess);
			}
			if (process_info.hThread)
			{
				CloseHandle(process_info.hThread);
			}
		}
		else
		{
			MessageBoxW(nullptr, L"Failed to launch settings window", L"Error", MB_ICONERROR);
		}
	}
}