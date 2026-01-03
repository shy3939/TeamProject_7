#include "ItemDatabase.h"
#include <vector>
#include <map>


static std::map<EquipID, std::vector<EquipData>> EquipDB = {
    // --- 검 (Sword) ---
    { EquipID::RustySword,   { 
        EquipData("녹슨 검", 2, 1, 0, 0, 0, 0),
        EquipData("녹슨 검", 1, 2, 0, 0, 0, 0),
        EquipData("녹슨 검", 2, 2, 1, 0, 0, 0)
}},
    { EquipID::NormalSword,  { 
        EquipData("평범한 검", 15, 4, 1, 0, 0, 0), 
        EquipData("평범한 검", 15, 3, 3, 0, 0, 0) 
}},
    { EquipID::SharpSword,   { 
        EquipData("예리한 검", 35, 7, 2, 0, 0, 0), 
        EquipData("예리한 검", 35, 6, 4, 0, 0, 0) 
}},

    // --- 활 (Bow) ---
    { EquipID::WornBow,      { EquipData("낡은 활", 5, 0, 2, 0, 0, 1) }},
    { EquipID::NormalBow,     { EquipData("사냥꾼의 활", 15, 0, 5, 0, 0, 2) }},
    { EquipID::SturdyBow,     { EquipData("강화된 복합궁", 40, 0, 8, 1, 0, 3) }},

    // --- 지팡이 (Staff) ---
    { EquipID::OldStaff,      { EquipData("낡은 지팡이", 5, 0, 0, 0, 2, 0) }},
    { EquipID::NormalStaff,   { EquipData("마법사의 지팡이", 20, 0, 0, 0, 6, 1) }},
    { EquipID::SturdyStaff,   { EquipData("수정 지팡이", 45, 0, 0, 0, 10, 2) }},

    // --- 창 (Spear) ---
    { EquipID::RustySpear,    { EquipData("녹슨 창", 7, 3, 0, 1, 0, 0) }},
    { EquipID::NormalSpear,   { EquipData("병사의 창", 18, 5, 1, 2, 0, 0) }},
    { EquipID::SharpSpear,    { EquipData("날카로운 트라이던트", 40, 9, 2, 2, 0, 0) }},

    // --- 도끼 (Axe) ---
    { EquipID::RustyAxe,      { EquipData("낡은 벌목도끼", 8, 4, -1, 0, 0, 0) }},
    { EquipID::NormalAxe,     { EquipData("철제 전투도끼", 20, 7, 0, 1, 0, 0) }},
    { EquipID::SturdyAxe,     { EquipData("강철 양날도끼", 45, 11, -1, 3, 0, 0) }},

    // --- 단검 (Dagger) ---
    { EquipID::RustyDagger,   { EquipData("녹슨 단검", 4, 1, 2, 0, 0, 1) }},
    { EquipID::NormalDagger,  { EquipData("무법자의 단검", 12, 2, 4, 0, 0, 3) }},
    { EquipID::SharpDagger,   { EquipData("암살자의 비수", 30, 3, 7, 0, 0, 5) }},

    // --- 방어구 (Armor/Gloves/Shoes) ---
    { EquipID::RustyArmor,    { EquipData("녹슨 흉갑", 10, 0, 0, 2, 0, 0) }},
    { EquipID::NormalArmor,   { EquipData("강철 흉갑", 30, 0, -1, 6, 0, 0) }},
    { EquipID::SturdyArmor,   { EquipData("기사의 갑옷", 60, 1, -2, 12, 0, 0) }},
    { EquipID::OldGloves,     { EquipData("낡은 장갑", 5, 0, 1, 1, 0, 0) }},
    { EquipID::NormalGloves,  { EquipData("가죽 장갑", 15, 1, 2, 2, 0, 0) }},
    { EquipID::SturdyGloves,  { EquipData("판금 장갑", 35, 2, 1, 5, 0, 0) }},
    { EquipID::OldShoes,      { EquipData("낡은 신발", 5, 0, 1, 0, 0, 0) }},
    { EquipID::NormalShoes,   { EquipData("여행자의 장화", 15, 0, 3, 1, 0, 0) }},
    { EquipID::SturdyShoes,   { EquipData("강철 군화", 35, 0, 1, 4, 0, 0) }}
};

static std::map<PotionID, std::vector<PotionData>> PotionDB = {
    { PotionID::HPPotion, { PotionData("하급 HP 포션", 10, 30, 0), PotionData("중급 HP 포션", 50, 100, 0) }},
    { PotionID::MPPotion, { PotionData("하급 MP 포션", 15, 0, 20), PotionData("중급 MP 포션", 60, 0, 80) }},
    { PotionID::ATKPotion, { PotionData("힘의 비약", 100, 0, 0) }}
};

static std::map<IngredID, std::vector<IngredData>> IngredDB = {
    // 몬스터 부산물
    { IngredID::ToughLeather,    { IngredData("질긴 가죽", 10) } },
    { IngredID::SoftFeather,     { IngredData("부드러운 깃털", 5) } },
    { IngredID::SlimyFluid,      { IngredData("끈적이는 액체", 3) } },
    { IngredID::InsectShell,     { IngredData("곤충 껍질", 8) } },
    { IngredID::SharpFang,       { IngredData("날카로운 이빨", 12) } },
    { IngredID::BrokenBone,      { IngredData("부서진 뼛조각", 4) } },
    { IngredID::GoblinEar,       { IngredData("고블린 귀", 2) } },
    { IngredID::SpiderWeb,       { IngredData("거미줄", 6) } },
    { IngredID::BoarTusk,        { IngredData("멧돼지 엄니", 15) } },
    { IngredID::AnimalTendon,    { IngredData("동물 힘줄", 7) } },

    // 광물/무기물
    { IngredID::RustyIronPiece,  { IngredData("녹슨 철 조각", 5) } },
    { IngredID::CopperOre,       { IngredData("구리 광석", 20) } },
    { IngredID::Flint,           { IngredData("부싯돌", 3) } },
    { IngredID::QuartzPiece,     { IngredData("석영 조각", 15) } },
    { IngredID::GlassShard,      { IngredData("유리 파편", 2) } },
    { IngredID::ShinySand,       { IngredData("반짝이는 모래", 5) } },
    { IngredID::SaltCrystal,     { IngredData("소금 결정", 10) } },
    { IngredID::MuddyCrystal,    { IngredData("탁한 수정 조각", 25) } },
    { IngredID::MagicDust,       { IngredData("마법 가루", 40) } },

    // 식물/채집물
    { IngredID::DryVine,         { IngredData("마른 덩굴", 3) } },
    { IngredID::DampMoss,        { IngredData("축축한 이끼", 2) } },
    { IngredID::HardShell,       { IngredData("단단한 조개껍데기", 5) } },
    { IngredID::DryHerbStem,     { IngredData("말린 약초 줄기", 4) } },
    { IngredID::BlueLeaf,        { IngredData("푸른 이파리", 6) } },
    { IngredID::DryMushroom,     { IngredData("말린 버섯", 8) } },
    { IngredID::DryTwig,         { IngredData("마른 나뭇가지", 1) } },

    // 가공 재료/잡동사니
    { IngredID::RoughFabric,     { IngredData("거친 천 조각", 5) } },
    { IngredID::OldCarpetPiece,  { IngredData("낡은 양탄자 조각", 12) } },
    { IngredID::OldPaperBundle,  { IngredData("낡은 종이 뭉치", 2) } },
    { IngredID::RustyArrowhead,  { IngredData("녹슨 화살촉", 3) } },
    { IngredID::LinenThread,     { IngredData("무명실", 8) } },
    { IngredID::EmptyGlassBottle, { IngredData("빈 유리병", 15) } },
    { IngredID::MonsterOil,      { IngredData("가공된 기름", 25) } },
    { IngredID::Whetstone,       { IngredData("거친 숫돌", 20) } }
};


const std::vector<EquipData>& ItemDatabase::GetEquipItems(EquipID eid) const {
    return EquipDB.at(eid);
}

const std::vector<PotionData>& ItemDatabase::GetPotionItems(PotionID pid) const {
    return PotionDB.at(pid);
}

const std::vector<IngredData>& ItemDatabase::GetIngredItems(IngredID gid) const {
    return IngredDB.at(gid);
}