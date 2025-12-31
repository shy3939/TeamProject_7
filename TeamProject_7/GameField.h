// GameField.h
#pragma once
#include "Field.h"
#include "Player.h"
#include "Monster.h"


class GameField : public Field
{
public:
    GameField() {};

    void Enter(Player* player) override;
    bool GetGameIsOver() const { return GameIsOver; }
    void ShowLog();

private:
    void StartBattle(Player* player);
    void ProcessPlayerTurn(Player* player, Monster* monster);
    void ProcessMonsterTurn(Player* player, Monster* monster);
    Monster* CreateRandomMonster(int playerLevel);
    Monster* CreateBossMonster();
    void Victory(Player* player, Monster* monster);
    void Defeat(Player* player);

    bool GameIsOver = false;
    bool BossBattle = false;
    int  KillScore[4] = {0,};
};