#include "helpers.h"
#include "tray_icon.h"
#include "history.h"
#include <chrono>
#include <format>
#include <iostream>
#include <filesystem>
#include <ShlObj_core.h>
#include <Windows.h>
#include <winrt/base.h>
#include <curl/curl.h>

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
		bool previous_status = true;

		while (true)
		{
			bool status = check_url("https://google.com")
				? true
				: (check_url("https://github.com") ? true : false);

			if (previous_status != status)
			{
				previous_status = status;

				TrayIcon::change_icon(status);

				const auto now = std::chrono::system_clock::now();
				const auto local = std::chrono::zoned_time{ std::chrono::current_zone(), now };

				HistoryManager::Record record;
				record.date = std::format(L"{:%Y-%m-%d}", local);
				record.time = std::format(L"{:%H:%M}", local);
				record.status = status;
				HistoryManager::new_record(record);
			}
			Sleep(10000);
		}
	}

	std::wstring get_root_save_folder()
	{
		PWSTR local_app_path;
		winrt::check_hresult(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &local_app_path));
		std::wstring result{ local_app_path };
		CoTaskMemFree(local_app_path);

		result += L"\\Neto";
		std::filesystem::path save_path(result);
		if (!std::filesystem::exists(save_path))
		{
			std::filesystem::create_directories(save_path);
		}

		return result;
	}
}