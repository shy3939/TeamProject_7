#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "utf.h"

namespace UIHelper {
    namespace {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        const int width = 80;
        const int TOP_Y = 0;
        const int MID_Y = 15;
        const int BOT_Y = 22;
    }

    static void SetCursor(int x, int y) {
        SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)y });
    }

    static void ClearLine(int y) {
        SetCursor(0, y);
        std::cout << std::string(width, ' ');
    }

    static void HideCursor() {
        CONSOLE_CURSOR_INFO info;
        GetConsoleCursorInfo(hConsole, &info);
        info.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &info);
    }

    static void ShowCursor() {
        CONSOLE_CURSOR_INFO info;
        GetConsoleCursorInfo(hConsole, &info);
        info.bVisible = TRUE;
        SetConsoleCursorInfo(hConsole, &info);
    }

    static void ClearScreen() {
        system("cls");
    }

    inline void Init() {
        ClearScreen();
        HideCursor();
        SetCursor(0, MID_Y - 1);
        std::cout << std::string(width, '=');
        SetCursor(0, BOT_Y - 1);
        std::cout << std::string(width, '=');
    }

    inline void UpdateTop(const std::string& art) {
        for (int i = TOP_Y; i < MID_Y - 1; i++) {
            ClearLine(i);
        }
        SetCursor(0, TOP_Y);
        std::cout << art;
    }

    inline void UpdateStatus(Player* player) {
        for (int i = MID_Y; i < BOT_Y - 1; i++) {
            ClearLine(i);
        }
        SetCursor(0, MID_Y);
        std::cout << " [ " << player->GetName() << " ]";
        SetCursor(0, MID_Y + 1);
        std::cout << " HP: " << player->GetHP() << " / " << player->GetMaxHP();
        SetCursor(0, MID_Y + 2);
        std::cout << " ATK: " << player->GetATK() << "  LV: " << player->GetLevel() << "  Gold: " << player->GetGold();
    }

    inline void UpdateBot(const std::string& message, float sleepSec = 0) {
        for (int i = BOT_Y; i < BOT_Y + 5; i++) {
            ClearLine(i);
        }
        SetCursor(0, BOT_Y);
        std::cout << " " << message;
        if (sleepSec > 0) {
            Sleep(static_cast<int>(sleepSec * 1000));
        }
    }

    inline void UpdateBot(const std::vector<std::string>& messages, float sleepSec = 0) {
        for (int i = BOT_Y; i < BOT_Y + 5; i++) {
            ClearLine(i);
        }
        for (size_t i = 0; i < messages.size() && i < 5; i++) {
            SetCursor(0, BOT_Y + (int)i);
            std::cout << " " << messages[i];
        }

        if (sleepSec > 0) {
            Sleep(static_cast<int>(sleepSec * 1000));
        }
    }

    inline std::string UpdateBotInput(const std::string& prompt) {
        for (int i = BOT_Y; i < BOT_Y + 5; i++) {
            ClearLine(i);
        }
        SetCursor(0, BOT_Y);
        std::cout << " " << prompt;
        SetCursor(0, BOT_Y + 1);
        std::cout << " > ";
        ShowCursor();
        std::string input = GetUTFInput();
        HideCursor();
        return input;
    }
}