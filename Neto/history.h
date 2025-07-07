#pragma once

#include <string>
#include <winrt/Windows.Data.Json.h>

using namespace winrt::Windows::Data::Json;

class HistoryManager
{
private:
	static JsonArray get_records();

public:
	struct Record
	{
		std::wstring date;
		std::wstring time;
		bool status;

	private:
		JsonObject to_json() const;
		static Record from_json(const JsonObject& obj);

		friend class HistoryManager;
	};

	static void init();
	static void new_record(Record record);
};