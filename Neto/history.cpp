#include "history.h"
#include "helpers.h"
#include "logger.h"
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

const wchar_t* history_filename = L"\\history.json";

JsonObject HistoryManager::Record::to_json() const
{
	JsonObject obj;

	obj.Insert(L"date", JsonValue::CreateStringValue(this->date));
	obj.Insert(L"time", JsonValue::CreateStringValue(this->time));
	obj.Insert(L"status", JsonValue::CreateBooleanValue(this->status));

	return obj;
}

HistoryManager::Record HistoryManager::Record::from_json(const JsonObject& obj)
{
	return Record{
		obj.GetNamedString(L"date").c_str(),
		obj.GetNamedString(L"time").c_str(),
		obj.GetNamedBoolean(L"status")
	};
}

void HistoryManager::init()
{
	const std::wstring save_file_location = Helpers::get_root_save_folder() + history_filename;
	if (!std::filesystem::exists(save_file_location))
	{
		HANDLE h = CreateFileW(save_file_location.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,
			0,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			0);

		if (h)
		{
			CloseHandle(h);
		}
	}
}

void HistoryManager::new_record(HistoryManager::Record record)
{
	JsonArray records = get_records();
	records.Append(record.to_json());

	const std::wstring save_file_path = Helpers::get_root_save_folder() + history_filename;
	std::wofstream file(save_file_path);
	if (file.is_open())
	{
		file << records.Stringify().c_str();
		file.close();
	}
}

JsonArray HistoryManager::get_records()
{
	const std::wstring save_file_location = Helpers::get_root_save_folder() + history_filename;
	
	std::wstring content{};
	std::wifstream file(save_file_location);
	if (file.is_open())
	{
		std::wstringstream buffer;
		buffer << file.rdbuf();
		content = buffer.str();
	}

	if (!content.empty())
	{
		return JsonArray::Parse(content);
	}
	else
	{
		return JsonArray{};
	}
}