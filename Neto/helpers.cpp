#include "helpers.h"
#include "tray_icon.h"
#include <iostream>
#include <windows.h>
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
		while (true)
		{
			bool status = check_url("https://google.com")
				? true
				: (check_url("https://github.com") ? true : false);

			TrayIcon::change_icon(status);
			Sleep(10000);
		}
	}
}