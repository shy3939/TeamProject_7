#include "UIHelper.h"
#include "Player.h"
#include <Windows.h>
#include <iostream>
#include "utf.h"
// #include "Player.h" // Player 멤버 함수 사용을 위해 실제 헤더 포함 필요

namespace UIHelper {
    // 익명 네임스페이스: 이 .cpp 파일 외부에서는 접근 불가
    namespace {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        const int width = 80;
        const int TOP_Y = 0;
        const int MID_Y = 15;
        const int BOT_Y = 22;

        void SetCursor(int x, int y) {
            SetConsoleCursorPosition(hConsole, { (SHORT)x, (SHORT)y });
        }

        void ClearLine(int y) {
            SetCursor(0, y);
            std::cout << std::string(width, ' ');
        }

        void HideCursor() {
            CONSOLE_CURSOR_INFO info;
            GetConsoleCursorInfo(hConsole, &info);
            info.bVisible = FALSE;
            SetConsoleCursorInfo(hConsole, &info);
        }

        void ShowCursor() {
            CONSOLE_CURSOR_INFO info;
            GetConsoleCursorInfo(hConsole, &info);
            info.bVisible = TRUE;
            SetConsoleCursorInfo(hConsole, &info);
        }

        void ClearScreen() {
            system("cls");
        }

        void DrawAt(int x, int y, const std::string& text) {
            SetCursor(x, y);
            std::cout << text;
        }
    }

    // --- 공개 함수 구현 ---

    void Init() {
        ClearScreen();
        HideCursor();
        SetCursor(0, MID_Y - 1);
        std::cout << std::string(width, '=');
        SetCursor(0, BOT_Y - 1);
        std::cout << std::string(width, '=');
    }

    void UpdateTop(const std::string& art, const float sleepSec) {
        HideCursor();
        for (int i = TOP_Y; i < MID_Y - 1; i++) {
            ClearLine(i);
        }
        SetCursor(0, TOP_Y);
        std::cout << art;

        if (sleepSec > 0) {
            Sleep(static_cast<DWORD>(sleepSec * 1000));
        }
    }

    void UpdateTopList(const std::vector<std::string>& lines, const std::string& title) {
        HideCursor();
        // Top 영역 클리어
        for (int i = TOP_Y; i < MID_Y - 1; i++) {
            ClearLine(i);
        }

        int currentLine = TOP_Y;
        const int maxLines = MID_Y - 1 - TOP_Y; // 사용 가능한 최대 라인 수

        // 타이틀 출력 (있는 경우)
        if (!title.empty()) {
            SetCursor(0, currentLine);
            std::cout << " ====== " << title << " ======";
            currentLine++;
        }

        // 리스트 항목 출력
        for (size_t i = 0; i < lines.size() && currentLine < MID_Y - 1; i++) {
            SetCursor(0, currentLine);
            std::cout << " " << lines[i];
            currentLine++;
        }
    }

    void UpdateStatus(Player* player) {
        for (int i = MID_Y; i < BOT_Y - 1; i++) {
            ClearLine(i);
        }
        SetCursor(0, MID_Y);
        // Player 클래스의 Getter 함수들이 public이어야 함
        std::cout << " [ " << player->GetName() << " ]";
        SetCursor(0, MID_Y + 1);
        std::cout << " HP: " << player->GetHP() << " / " << player->GetMaxHP();
        SetCursor(0, MID_Y + 2);
        std::cout << "  LV: " << player->GetLevel() << " ATK: " << player->GetATK()  << "  Gold: " << player->GetGold();
        SetCursor(0, MID_Y + 3);
        std::cout << " STR: " << player->GetSTR() << " AGI: " << player->GetAGI() << " VIT: " << player->GetVIT() << " INT: " << player->GetINT() << " LUK: " << player->GetLUK();
    }

    void UpdateBot(const std::string& message, const float sleepSec) {
        for (int i = BOT_Y; i < BOT_Y + 5; i++) {
            ClearLine(i);
        }
        SetCursor(0, BOT_Y); 
        std::cout << " " << message;
        if (sleepSec > 0) {
            Sleep(static_cast<DWORD>(sleepSec * 1000));
        }
    }

    void UpdateBot(const std::vector<std::string>& messages, const float sleepSec) {
        for (int i = BOT_Y; i < BOT_Y + 5; i++) {
            ClearLine(i);
        }
        for (size_t i = 0; i < messages.size() && i < 5; i++) {
            SetCursor(0, BOT_Y + (int)i);
            std::cout << " " << messages[i];
        }

        if (sleepSec > 0) {
            Sleep(static_cast<DWORD>(sleepSec * 1000));
        }
    }

    std::string UpdateBotInput(const std::string& prompt) {
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

    void PlaySlashEffect(const float delaySec) {
        DrawAt(26, 4, "\\\\");
        DrawAt(28, 5, "\\\\");
        DrawAt(28, 6, "//"); 
        DrawAt(26, 7, "//");
        Sleep(static_cast<DWORD>(delaySec * 1000));

        DrawAt(26, 4, "      \\\\"); 
        DrawAt(28, 5, "      \\\\");
        DrawAt(28, 6, "      //"); 
        DrawAt(26, 7, "      //");
        Sleep(static_cast<DWORD>(delaySec * 1000));

        DrawAt(26, 4, "            \\\\"); 
        DrawAt(28, 5, "            \\\\");
        DrawAt(28, 6, "            //"); 
        DrawAt(26, 7, "            //");
        Sleep(static_cast<DWORD>(delaySec * 1000));
    }

    void PlaySlashEffectReverse(const float delaySec) {
        DrawAt(36, 4, "//"); 
        DrawAt(35, 5, "//");
        DrawAt(35, 6, "\\\\"); 
        DrawAt(36, 7, "\\\\");
        Sleep(static_cast<DWORD>(delaySec * 1000));

        DrawAt(32, 4, "//    "); 
        DrawAt(31, 5, "//    ");
        DrawAt(31, 6, "\\\\    "); 
        DrawAt(32, 7, "\\\\    ");
        Sleep(static_cast<DWORD>(delaySec * 1000));

        DrawAt(28, 4, "//    "); 
        DrawAt(27, 5, "//    ");
        DrawAt(27, 6, "\\\\    "); 
        DrawAt(28, 7, "\\\\    ");
        Sleep(static_cast<DWORD>(delaySec * 1000));
    }

    void PlayFireEffect(const float delaySec) {
        DrawAt(36, 4, "@@"); 
        DrawAt(35, 5, "@@@@");
        DrawAt(35, 6, "@@@@"); 
        DrawAt(36, 7, "@@");
        Sleep(static_cast<DWORD>(delaySec * 1000));

        DrawAt(32, 4, "@@    "); 
        DrawAt(31, 5, "@@@@    ");
        DrawAt(31, 6, "@@@@    "); 
        DrawAt(32, 7, "@@    ");
        Sleep(static_cast<DWORD>(delaySec * 1000));

        DrawAt(28, 4, "@@    "); 
        DrawAt(27, 5, "@@@@    ");
        DrawAt(27, 6, "@@@@    "); 
        DrawAt(28, 7, "@@    ");
        Sleep(static_cast<DWORD>(delaySec * 1000));
    }

    void PlayHeroDeathEffect(const float delaySec) {
        HideCursor();
        for (int i = TOP_Y; i < MID_Y - 1; i += 2) {
            DrawAt(0, i, std::string(40, ' '));
            DrawAt(0, i + 1, std::string(40, ' '));
            if (delaySec > 0) Sleep(static_cast<DWORD>(delaySec * 1000));
        }
    }

    void PlayMonsterDeathEffect(const float delaySec) {
        HideCursor();
        for (int i = TOP_Y; i < MID_Y - 1; i += 2) {
            DrawAt(40, i, std::string(40, ' '));
            DrawAt(40, i + 1, std::string(40, ' '));
            if (delaySec > 0) Sleep(static_cast<DWORD>(delaySec * 1000));
        }
    }

    void AddToShopList(const std::string& message, const std::string& price , int shopslot) {
        HideCursor();
        int x, y;

        switch (shopslot) {
        case 0: x = 4;  y = 4; break;   // 예시
        case 1: x = 29; y = 4; break;   // 
        case 2: x = 54; y = 4; break;   // 
        case 3: x = 4; y = 8; break;   // 
        case 4: x = 29; y = 8; break;   // 
        case 5: x = 54;  y = 8; break;  // 
        default: return;  
        }

        DrawAt(x, y, message);
        DrawAt(x, y + 1, price + " G");

        if(price == "품절") DrawAt(x, y + 1, price + "  ");
        else DrawAt(x, y + 1, price + " G");
       
    }
}