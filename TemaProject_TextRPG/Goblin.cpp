#include "Goblin.h"

Goblin::Goblin(const Player& player)
	:
{
	RandHp = rand() % 11 + 20;
	RandATK = rand() % 6 + 5;
	RandGold = rand() % 11 + 10;
	RandItem = rand() 10;

	int Level = player.GetLevel();

	"고블린"
	SetMaxHp(Level* RandHp);
	SetATK(Level* RandATK);
	SetGold(RandGold);

	//if (RandItem > 6)
	//{
	//	// 아이템 보유
	//}
}

Goblin::~Goblin()
	:
{
	std::cout << "고블린(를)을 처치하셨습니다!" << std::endl;
	std::cout << "경험치(EXP) 50을 획득했습니다!" << std::endl;
	std::cout << "골드" << GetGold() << "를 획득하셨습니다!" << std::endl;

	// 아이템 획득 시 실행될 코드(포인터로 받을 예정)
}



void Goblin::InitRandom()
{
	RandMaxHp = RandomInRange(10, 20);
}