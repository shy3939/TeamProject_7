#pragma once

enum class ItemType
{
	Equipment,
	Potion,
	Ingredient
};

enum class EquipID
{
	// --- 검 ---
	RustySword,
	NormalSword,
	SharpSword,
	// --- 활 ---
	WornBow,
	NormalBow,
	SturdyBow,
	// --- 지팡이 ---
	OldStaff,
	NormalStaff,
	SturdyStaff,
	// --- 창 ---
	RustySpear,
	NormalSpear,
	SharpSpear,
	// --- 도끼 ---
	RustyAxe,
	NormalAxe,
	SturdyAxe,
	// --- 단검 ---
	RustyDagger,
	NormalDagger,
	SharpDagger,
	// --- 흉갑 ---
	RustyArmor,
	NormalArmor,
	SturdyArmor,
	// --- 장갑 ---
	OldGloves,
	NormalGloves,
	SturdyGloves,
	// --- 신발 ---
	OldShoes,
	NormalShoes,
	SturdyShoes
};

enum class PotionID
{
	HPPotion,
	MPPotion,
	ATKPotion
};

enum class IngredID
{
	// --- 동물 및 몬스터 부산물 ---
	ToughLeather,      // 질긴 가죽
	SoftFeather,       // 부드러운 깃털
	SlimyFluid,        // 끈적이는 액체 (슬라임)
	InsectShell,       // 곤충 껍질
	SharpFang,         // 날카로운 이빨
	BrokenBone,        // 부서진 뼛조각
	GoblinEar,         // 고블린 귀
	SpiderWeb,         // 거미줄
	BoarTusk,          // 멧돼지 엄니
	AnimalTendon,      // 동물 힘줄

	// --- 광물 및 무기물 ---
	RustyIronPiece,    // 녹슨 철 조각
	CopperOre,         // 구리 광석
	Flint,             // 부싯돌
	QuartzPiece,       // 석영 조각
	GlassShard,        // 유리 파편
	ShinySand,         // 반짝이는 모래
	SaltCrystal,       // 소금 결정
	MuddyCrystal,      // 탁한 수정 조각
	MagicDust,         // 마법 가루

	// --- 식물 및 채집물 ---
	DryVine,           // 마른 덩굴
	DampMoss,          // 축축한 이끼
	HardShell,         // 단단한 조개껍데기
	DryHerbStem,       // 말린 약초 줄기
	BlueLeaf,          // 푸른 이파리
	DryMushroom,       // 말린 버섯
	DryTwig,           // 마른 나뭇가지

	// --- 기타 잡동사니 ---
	RoughFabric,       // 거친 천 조각
	OldCarpetPiece,    // 낡은 양탄자 조각
	OldPaperBundle,    // 낡은 종이 뭉치
	RustyArrowhead,    // 녹슨 화살촉
	LinenThread,       // 실
	EmptyGlassBottle,  // 빈 유리병
	MonsterOil,        // 가공된 기름
	Whetstone,         // 숫돌
};