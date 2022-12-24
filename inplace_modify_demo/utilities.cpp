#include "utilities.h"
#include <codecvt>
#include <memory>

#if Inplace_Modify_Demo_WIN32_ENVIRONMENT
#include <Windows.h>
#endif

using namespace std;

std::string convertToUtf8(const std::wstring& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
    std::string conv = utf8_conv.to_bytes(str);
    return conv;
}

std::wstring convertToWide(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8conv;
    std::wstring conv = utf8conv.from_bytes(str);
    return conv;
}

#if Inplace_Modify_Demo_WIN32_ENVIRONMENT
CommandlineArgsWindowsHelper::CommandlineArgsWindowsHelper()
{
    int number_arguments;
    const unique_ptr<LPWSTR, decltype(LocalFree)*> wide_argv
    {
        CommandLineToArgvW(GetCommandLineW(), &number_arguments),
        &LocalFree
    };

    this->pointers_to_arguments_.reserve(number_arguments);
    this->arguments_.reserve(number_arguments);

    for (int i = 0; i < number_arguments; ++i)
    {
        this->arguments_.emplace_back(convertToUtf8(wide_argv.get()[i]));
    }

    for (int i = 0; i < number_arguments; ++i)
    {
        this->pointers_to_arguments_.emplace_back(
            this->arguments_[i].data());
    }
}

char** CommandlineArgsWindowsHelper::GetArgv()
{
    return this->pointers_to_arguments_.data();
}

int CommandlineArgsWindowsHelper::GetArgc()
{
    return static_cast<int>(this->pointers_to_arguments_.size());
}
#endif
