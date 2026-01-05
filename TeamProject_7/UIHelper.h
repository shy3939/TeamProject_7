#pragma once
#include <string>
#include <vector>

// Player 클래스 전방 선언 (헤더 포함 최소화)
class Player;

namespace UIHelper {
    // 공개 인터페이스 함수들
    void Init();
    void UpdateTop(const std::string& art, const float sleepSec = 0);
    void UpdateStatus(Player* player);
    void UpdateBot(const std::string& message, const float sleepSec = 0);
    void UpdateBot(const std::vector<std::string>& messages, const float sleepSec = 0);
    std::string UpdateBotInput(const std::string& prompt);

    // 효과 관련 함수들
    void PlaySlashEffect(const float delaySec = 0.5f);
    void PlaySlashEffectReverse(const float delaySec = 0.5f);
    void PlayFireEffect(const float delaySec = 0.5f);
    void PlayHeroDeathEffect(const float delaySec = 0.15f);
    void PlayMonsterDeathEffect(const float delaySec = 0.15f);
}