// GameField.cpp
#include <cstdlib>
#include <iostream>
#include "GameField.h"

void GameField::Enter(Player* player)
{
    if (player->GetLevel() == 10)
    {
        std::cout << " 이제 일반 몬스터는 상대도 안 된다!!! " << std::endl;
        BossBattle = true;
    }

    if (BossBattle) {
        std::cout << "========================================" << std::endl;
        std::cout << "   ⚔️  보스의 서식지에 입장했습니다!  ⚔️" << std::endl;
        std::cout << "========================================" << std::endl;
    }

    else
    {
        std::cout << "========================================" << std::endl;
        std::cout << " ⚔️ 일반 전투 필드에 입장했습니다! ⚔️ " << std::endl;
        std::cout << "========================================" << std::endl;
    }
    StartBattle(player);
}

void GameField::StartBattle(Player* player)
{
    Monster* monster = nullptr;

    // 레벨 10이면 보스 등장
    if (BossBattle)
    {
        std::cout << " 보스 몬스터가 나타났다! " << std::endl;
        monster = CreateBossMonster();
    }
    else
    {
        monster = CreateRandomMonster(player->GetLevel());
        std::cout << monster->GetName() << "이(가) 나타났다! " << std::endl;
    }

    // 턴 기반 전투
    while (1)
    {         
        //플레이어 상태 확인 (player에서 구현됐나 확인)
        player->ShowStatus();

        // 플레이어 턴
        ProcessPlayerTurn(player, monster);

        // 몬스터 사망 체크
        if (monster->GetHP() <= 0)
        {
            Victory(player, monster);
            break;
        }

        // 몬스터 턴
        ProcessMonsterTurn(player, monster);

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
    std::cout << "--- 플레이어 턴 ---" << std::endl;

    //inventory 사용
    Inventory* inventory = player->GetInventory();

    if (inventory->isAvailable("HealthPotion") && player->GetHP() < (player->GetMaxHP() / 2))
    {
        inventory->Use("AttackPotion");
    }

    if (inventory->isAvailable("AttackPotion"))
    {
        inventory->Use("AttackPotion");
    }

    int damage = player->GetAttack();
    monster->TakeDamage(damage);

    std::cout << player->GetName() << "의 공격! " << std::endl;
    std::cout << monster->GetName() << "에게 " << damage << " 데미지! " << std::endl;
    if (monster->GetHP() > 0) {
        std::cout << " 적 현재 체력 : " << monster->GetHP() << std::endl;
    }
}

void GameField::ProcessMonsterTurn(Player* player, Monster* monster)
{
    std::cout << "--- 몬스터 턴 ---" << std::endl;

    int damage = monster->GetAttack();
    player->TakeDamage(damage);

    std::cout << monster->GetName() << "의 공격! ";
    std::cout << player->GetName() << "에게 " << damage << " 데미지! " << std::endl;
    if (player->GetHP() > 0) {
        std::cout << " 내 현재 체력 : " << player->GetHP() << std::endl;
    }
}

// 몬스터 생성자 확인 이름, HP, ATK, Gold 
Monster* GameField::CreateRandomMonster(int level)
{
    int monsterType = rand() % 3;
    int Gold = 10 + rand() % 11;
    int RandomHP = 20 + rand() % 11;
    int RandomATK = 5 + rand() % 6;

    switch (monsterType)
    {
    case 0:
        return new Monster("슬라임", level * RandomHP, level * RandomATK, Gold);
    case 1:
        return new Monster("고블린", level * RandomHP, level * RandomATK, Gold);
    case 2:
        return new Monster("오크", level * RandomHP, level * RandomATK, Gold);
    default:
        return new Monster("슬라임", level * RandomHP, level * RandomATK, Gold);
    }
}

Monster* GameField::CreateBossMonster()
{
    int RandomHp = 30 + rand() % 16;
    int RandomATK = 10 + rand() % 6;
    return new Monster("드래곤", 10 * RandomHp, 10 * RandomATK, 0);
}

void GameField::Victory(Player* player, Monster* monster)
{
    GameIsOver = true;
    // 보스 처치 시 엔딩
    if (BossBattle)
    {
        std::cout << "========================================" << std::endl;
        std::cout << "    🏆 축하합니다! 게임 클리어! 🏆    " << std::endl;
        std::cout << "  드래곤을 물리치고 세계를 구했습니다!  " << std::endl;
        std::cout << "========================================" << std::endl;
        return;
    }

    // 일반 전투 승리 로그
    std::cout << "=======================================" << std::endl;
    std::cout << "    🎉 전투에서 승리했습니다! 🎉     " << std::endl;
    std::cout << "=======================================" << std::endl;

    // 골드와 경험치 보상
    int goldReward = monster->GetGoldReward();
    int expReward = monster->GetExpReward(); // 50 고정

    player->AddGold(goldReward);
    player->AddExp(expReward);

    std::cout << "획득 골드: " << goldReward << " G" << std::endl;
    std::cout << "획득 경험치: " << expReward << " EXP" << std::endl;


    int NumHealthPotion = rand() % 5;
    int NumAttackHealthPotion = rand() % 5;
    // 아이템 보상
    if (rand() % 100 < 30) 
    {
        Inventory* inventory = player->GetInventory();
        inventory->AddItem("HealthPotion", NumHealthPotion);
        inventory->AddItem("AttackPotion", NumAttackHealthPotion);
    }

    if (monster->GetName() == "슬라임")
        KillScore[0]++;
    else if (monster->GetName() == "고블린")
        KillScore[1]++;
    else if (monster->GetName() == "오크")
        KillScore[2]++;
    else if (monster->GetName() == "드래곤")
        KillScore[3]++;

}

void GameField::Defeat(Player* player)
{
    GameIsOver = true;

    std::cout << " 전투 패배 : " << player->GetName() << " 이(가) 사망했습니다... " << std::endl;

}

void GameField::ShowLog() {
    std::cout << " 현재까지 처치한 적 " << std::endl;
    std::cout << " 슬라임 : " << KillScore[0] << std::endl;
    std::cout << " 고블린 : " << KillScore[1] << std::endl;
    std::cout << " 오크 : " << KillScore[2] << std::endl;
    std::cout << " 드래곤 : " << KillScore[3] << std::endl;
}