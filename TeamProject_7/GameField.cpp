// GameField.cpp
#include <cstdlib>
#include <iostream>
#include "utf.h"
#include "GameField.h"
#include "Goblin.h"
#include "Oak.h"
#include "Slim.h"
#include "Dragon.h"
#include "UIHelper.h"
#include "AsciiArt.h"
#include "Inventory.h"
#include "ItemEnum.h" 

void GameField::Enter(Player* player)
{
    UIHelper::UpdateTop(AsciiArt::Hero);

    if (player->GetLevel() == 10)
    {
        UIHelper::UpdateBot("이제 일반 몬스터는 상대도 안 된다!!! ", 1);
        BossBattle = true;
    }

    if (BossBattle) {

        UIHelper::UpdateBot("**!** 보스의 서식지에 입장했습니다! **!**", 1);
    }

    else
    {

        UIHelper::UpdateBot("+++ 몬스터 서식지에 입장했습니다! +++", 1);
    }
    StartBattle(player);
}

// 추가함
Monster* GameField::CreateRandomMonster(Player& player)
{
    int RandNum = rand() % 3 + 1;

    switch (RandNum)
    {
    case 1:
        return new Goblin(player);
    case 2:
        return new Slim(player);
    case 3:
        return new Oak(player);
    default:
        return new Goblin(player);
    }
}

Monster* GameField::CreateBossMonster(Player& player)
{
    return new Dragon(player);
}

void GameField::StartBattle(Player* player)
{
    Monster* monster = nullptr;

    // 레벨 10이면 보스 등장
    if (BossBattle)
    {
        UIHelper::UpdateBot("드래곤이(가) 나타났다! ", 1);
        monster = CreateBossMonster(*player);
        UIHelper::UpdateTop(AsciiArt::HeroVsDragon);
    }
    else
    {
    monster = CreateRandomMonster(*player);

    if (monster->GetName() == "슬라임")
        UIHelper::UpdateTop(AsciiArt::HeroVsSlime);
    else if (monster->GetName() == "고블린")
        UIHelper::UpdateTop(AsciiArt::HeroVsGoblin);
    else if (monster->GetName() == "오크")
        UIHelper::UpdateTop(AsciiArt::HeroVsOrc);

    UIHelper::UpdateBot(monster->GetName() + "이(가) 나타났다! ", 1);
    }
    
    // 턴 기반 전투
    while (1)
    {         
        // 플레이어 턴
        ProcessPlayerTurn(player, monster);
        UIHelper::UpdateStatus(player);

        // 몬스터 사망 체크
        if (monster->GetHP() <= 0)
        {
            Victory(player, monster);
            break;
        }

        // 몬스터 턴
        ProcessMonsterTurn(player, monster);
        UIHelper::UpdateStatus(player);

        // 플레이어 사망 체크
        if (player->GetHP() <= 0)
        {
            
            Defeat(player);
            break;
        }
    }

    delete monster;
}

void GameField::ProcessPlayerTurn(Player* player, Monster* monster)
{
    UIHelper::UpdateBot("[ 플레이어 턴 ]", 1);

    //inventory 사용
    Inventory* inventory = player->GetInventory();
    int tempATK = player->GetATK();
    
    if (inventory->GetItemCount(ItemType::Potion, (int)PotionID::HPPotion) > 0
        && player->GetHP() < (player->GetMaxHP() / 2))
    {
        // 해당 아이템이 있는 슬롯을 찾아서 사용
        int slot = inventory->FindSameItemSlot(ItemType::Potion, (int)PotionID::HPPotion);
        if (slot != -1)
            inventory->Use(slot + 1, player);  // displaySlot은 1부터 시작
    }

    if (inventory->GetItemCount(ItemType::Potion, (int)PotionID::ATKPotion) > 0)
    {
        int slot = inventory->FindSameItemSlot(ItemType::Potion, (int)PotionID::ATKPotion);
        if (slot != -1)
            inventory->Use(slot + 1, player);
    }
    
    UIHelper::UpdateStatus(player);

    // 공격 처리
    UIHelper::PlaySlashEffect();
    if (monster->GetName() == "슬라임")
        UIHelper::UpdateTop(AsciiArt::HeroVsSlime);
    else if (monster->GetName() == "고블린")
        UIHelper::UpdateTop(AsciiArt::HeroVsGoblin);
    else if (monster->GetName() == "오크")
        UIHelper::UpdateTop(AsciiArt::HeroVsOrc);
    else if (monster->GetName() == "드래곤")
        UIHelper::UpdateTop(AsciiArt::HeroVsDragon);
    
    int damage = player->CalcDamage(player->GetATK());
    
    std::string CriticalMessage;
    if (player->IsCritical())
    {
        CriticalMessage = "치명적인";
        damage *= 1.3;
    }
    
    monster->TakeDamage(damage);

    // Log 처리
    std::string PromptEnemyHP;
    if (monster->GetHP() > 0) {
        PromptEnemyHP = "적 현재 체력 : " + std::to_string(monster->GetHP());
    }
    
    else {
        UIHelper::PlayMonsterDeathEffect();
        PromptEnemyHP = monster->GetName() + "은(는) 쓰러졌다!";
    }
    UIHelper::UpdateBot({
        player->GetName() + "의 " + CriticalMessage+ " 공격!",
        monster->GetName() + "에게 " + std::to_string(damage) + " 데미지!",
        PromptEnemyHP
        }, 2);
    
    player->SetATK(tempATK);
    UIHelper::UpdateStatus(player);
}

void GameField::ProcessMonsterTurn(Player* player, Monster* monster)
{
    UIHelper::UpdateBot("[ 몬스터 턴 ]" , 1);

    // 공격처리 
    if (monster->GetName() == "슬라임") {
        UIHelper::PlayFireEffect();
        UIHelper::UpdateTop(AsciiArt::HeroVsSlime);
    }
    else if (monster->GetName() == "고블린") {
        UIHelper::PlaySlashEffectReverse();
        UIHelper::UpdateTop(AsciiArt::HeroVsGoblin);
    }
    else if (monster->GetName() == "오크") {
        UIHelper::PlaySlashEffectReverse();
        UIHelper::UpdateTop(AsciiArt::HeroVsOrc);
    }
    else if (monster->GetName() == "드래곤") {
        UIHelper::PlayFireEffect();
        UIHelper::UpdateTop(AsciiArt::HeroVsDragon);
    }

    if (player->TryEvade(monster->GetAGI()))
    {
        UIHelper::UpdateBot( monster->GetName() + "의 공격!",0.5);
        UIHelper::UpdateBot( player->GetName() + "은(는) 회피했다!", 0.5);
    }
    else
    {
        int damage = monster->CalcDamage( monster->MonsterATK() );
        std::string CriticalMessage;
        if (monster->IsCritical())
        {
            CriticalMessage = "치명적인";
            damage *= 1.3;
        }
    
        player->TakeDamage(damage);

        // Log 처리
        std::string PromptPlayerHP;
        if (monster->GetHP() > 0) {
            PromptPlayerHP = "내 현재 체력 : " + std::to_string(player->GetHP());
        }

        else {
            UIHelper::PlayHeroDeathEffect();
            PromptPlayerHP = player->GetName() + "은(는) 쓰러졌다!";
        }

        UIHelper::UpdateBot({
        monster->GetName() + "의 " + CriticalMessage+ " 공격!",
        player->GetName() + "에게 " + std::to_string(damage) + " 데미지!",
        PromptPlayerHP
        }, 2);
    }
}

void GameField::Victory(Player* player, Monster* monster)
{
    GameIsOver = false;
    // 보스 처치 시 엔딩
    if (BossBattle)
    {
        GameIsOver = true;
    
        if (monster->GetName() == "드래곤")
        KillScore[3]++;
        
        UIHelper::UpdateBot({
            "*** 축하합니다 "+player->GetName()+ "! ***",
            "당신이 보스를 물리치고 세계를 구했습니다!"
        }, 3);
    }
    else
    {
        UIHelper::UpdateBot("*** 전투에서 승리했습니다! ***", 3);

        // 골드와 경험치 보상
        int goldReward = monster->GetGold();

        player->AddGold(goldReward);
        player->AddExp(50);
    
        UIHelper::UpdateStatus(player);
        UIHelper::UpdateBot({
            "획득 골드: " + std::to_string(goldReward) + " G",
            "획득 경험치: " + std::to_string(50) + " EXP"
            }, 1);

        int NumHealthPotion = rand() % 3;
        int NumAttackHealthPotion = rand() % 3;

        // 아이템 보상
        if (rand() % 100 < 30) 
        {
            Inventory* inventory = player->GetInventory();
            inventory->AddItem(ItemType::Potion, (int)PotionID::HPPotion, NumHealthPotion);
        }

        if (rand() % 100 < 30)
        {
            Inventory* inventory = player->GetInventory();
            inventory->AddItem(ItemType::Potion, (int)PotionID::ATKPotion, NumAttackHealthPotion);
        }

        if (monster->GetName() == "슬라임")
            KillScore[0]++;
        else if (monster->GetName() == "고블린")
            KillScore[1]++;
        else if (monster->GetName() == "오크")
            KillScore[2]++;
    }

}

void GameField::Defeat(Player* player)
{
    GameIsOver = true;

    UIHelper::UpdateBot("전투 패배 : " + player->GetName() + " 이(가) 사망했습니다... ", 1);
}

void GameField::ShowLog() {
    UIHelper::UpdateBot({ "현재까지 처치한 적 " ,
        "슬라임 : " + std::to_string(KillScore[0]),
        "고블린 : " + std::to_string(KillScore[1]),
        "오크 : " + std::to_string(KillScore[2]),
        "드래곤 : " + std::to_string(KillScore[3]),
    }, 2);
}