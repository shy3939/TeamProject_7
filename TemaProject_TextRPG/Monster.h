#pragma once
#include <string>
#include <iostream>
#include <vecotr>
#include <cstdlib>

class Monster
{
public:
	Monster(std::string monstername, int maxhp, int atk, int gold);

	~Monster();


	virtual void MosterAttack() = 0;
	virtual void MosterDie() = 0;

	std::string GetMonsterName();
	int GetMaxHp();
	int GetHp();
	int GetATK();
	int GetGold();
	// 획득한 아이템 출력
	void SetMonsterName(std::string monstername);
	void SetMaxHp(int maxhp);
	void SetHp(int hp);
	void SetATK(int atk);
	void SetGold(int gold);
	// 획득할 아이템 선택
	int RandomInRange(int min, int max);


protected:
	std::string monstername_;
	int maxhp_;
	int hp_;
	int atk_;
	int gold_;
	// 아이템 객체 랜덤으로 생성해야 될듯?
};