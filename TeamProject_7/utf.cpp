#include "utf.h"

std::string GetUTFInput() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    wchar_t wbuffer[1024];

    DWORD charactersRead = 0;
    if (!ReadConsoleW(hInput, wbuffer, 1024, &charactersRead, NULL)) {
        return "";
    }

    std::wstring wstr(wbuffer, charactersRead);
    while (!wstr.empty() && (wstr.back() == L'\r' || wstr.back() == L'\n')) {
        wstr.pop_back();
    }

    if (wstr.empty()) return "";
    int size_needed = WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.c_str(),
        static_cast<int>(wstr.size()),
        NULL, 0, NULL, NULL);

    std::string utf8Str(size_needed, 0);

    WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.c_str(),
        static_cast<int>(wstr.size()),
        &utf8Str[0],
        size_needed, NULL, NULL);

    return utf8Str;
}

void GetEnterInput() {
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail() > 0) {
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
    std::cin.get();
}