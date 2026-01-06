#include "Inventory.h"
#include "PotionItem.h"
#include "EquipItem.h"
#include "IngredItem.h"
#include "ItemDatabase.h"
#include <iostream>
#include "ItemEnum.h"
#include "Item.h"
#include "Player.h"
#include "UIHelper.h"
#include "utf.h"

Inventory::Inventory(const ItemDatabase& db)
    : db_(db)
{
    slots_.assign(MAX_SLOT, Slot());

    itemData_.emplace(
        ItemKey{ ItemType::Potion, (int)PotionID::HPPotion },
        std::make_unique<PotionItem>(PotionID::HPPotion, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Potion, (int)PotionID::HPPotion2 },
        std::make_unique<PotionItem>(PotionID::HPPotion2, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Potion, (int)PotionID::ATKPotion },
        std::make_unique<PotionItem>(PotionID::ATKPotion, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Potion, (int)PotionID::ATKPotion2 },
        std::make_unique<PotionItem>(PotionID::ATKPotion2, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::RustyArmor },
        std::make_unique<EquipItem>(EquipID::RustyArmor, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalArmor },
        std::make_unique<EquipItem>(EquipID::NormalArmor, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SturdyArmor },
        std::make_unique<EquipItem>(EquipID::SturdyArmor, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::OldGloves },
        std::make_unique<EquipItem>(EquipID::OldGloves, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalGloves },
        std::make_unique<EquipItem>(EquipID::NormalGloves, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SturdyGloves },
        std::make_unique<EquipItem>(EquipID::SturdyGloves, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::OldShoes },
        std::make_unique<EquipItem>(EquipID::OldShoes, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalShoes },
        std::make_unique<EquipItem>(EquipID::NormalShoes, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SturdyShoes },
        std::make_unique<EquipItem>(EquipID::SturdyShoes, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::RustySword },
        std::make_unique<EquipItem>(EquipID::RustySword, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalSword },
        std::make_unique<EquipItem>(EquipID::NormalSword, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SharpSword },
        std::make_unique<EquipItem>(EquipID::SharpSword, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::OldBow },
        std::make_unique<EquipItem>(EquipID::OldBow, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalBow },
        std::make_unique<EquipItem>(EquipID::NormalBow, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SturdyBow },
        std::make_unique<EquipItem>(EquipID::SturdyBow, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::OldStaff },
        std::make_unique<EquipItem>(EquipID::OldStaff, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalStaff },
        std::make_unique<EquipItem>(EquipID::NormalStaff, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SturdyStaff },
        std::make_unique<EquipItem>(EquipID::SturdyStaff, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::RustySpear },
        std::make_unique<EquipItem>(EquipID::RustySpear, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalSpear },
        std::make_unique<EquipItem>(EquipID::NormalSpear, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SharpSpear },
        std::make_unique<EquipItem>(EquipID::SharpSpear, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::RustyAxe },
        std::make_unique<EquipItem>(EquipID::RustyAxe, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalAxe },
        std::make_unique<EquipItem>(EquipID::NormalAxe, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SturdyAxe },
        std::make_unique<EquipItem>(EquipID::SturdyAxe, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::RustyDagger },
        std::make_unique<EquipItem>(EquipID::RustyDagger, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::NormalDagger },
        std::make_unique<EquipItem>(EquipID::NormalDagger, db_)
    );
    itemData_.emplace(
        ItemKey{ ItemType::Equipment, (int)EquipID::SharpDagger },
        std::make_unique<EquipItem>(EquipID::SharpDagger, db_)
    );
}


Inventory::~Inventory()
{}

bool Inventory::IsEmpty() const            // 맵이 아예 통째로 비여있는지 모든 아이템이 없으면 true 아이템이 하나라도 있으면 false
{
    for (const Slot& slot : slots_)
    {
        if (!slot.IsEmpty())
            return false;
    }
    return true;
}

bool Inventory::IsAvailable(int displaySlot) const
{
    int index = displaySlot - 1;
    if (index < 0 || index >= MAX_SLOT)
    {
        return false;
    }
    return !slots_[index].IsEmpty();
}

int Inventory::FindSameItemSlot(ItemType type, int id) const
{
    for (int index = 0; index < MAX_SLOT; ++index)
    {
        if (!slots_[index].IsEmpty() &&
            slots_[index].type == type &&
            slots_[index].id == id)
        {
            return index;
        }
    }
    return -1;
}

int Inventory::GetSize() const
{
    int size = 0;
    for (const Slot& slot : slots_)
    {
        if (!slot.IsEmpty())
        {
            size++;
        }
    }
    return size;
}

int Inventory::FindEmptySlot() const
{
    for (int index = 0; index < MAX_SLOT; ++index)
    {
        if (slots_[index].IsEmpty())
            return index;
    }
    return -1;
}

void Inventory::AddItem(ItemType type, int id, int count)
{
    int sameSlot = FindSameItemSlot(type, id);
    if (sameSlot != -1)
    {
        slots_[sameSlot].count += count;
        UIHelper::UpdateBot("아이템 수량이 증가했습니다.", 1);
        return;
    }

    int emptySlot = FindEmptySlot();
    if (emptySlot == -1)
    {
        UIHelper::UpdateBot("인벤토리가 가득 찼습니다.", 1);
        return;
    }

    slots_[emptySlot].type = type;
    slots_[emptySlot].id = id;
    slots_[emptySlot].count = count;

    UIHelper::UpdateBot("아이템을 획득했습니다.", 1);
}

void Inventory::RemoveItem(ItemType type, int id, int count)
{
    int remaining = count;

    if (count <= 0) return;

    for (int index = 0; index < MAX_SLOT && remaining > 0; ++index)
    {
        Slot& slot = slots_[index];

        if (!slot.IsEmpty() &&
            slot.type == type &&
            slot.id == id)
        {
            if (slot.count > remaining)
            {
                slot.count -= remaining;
                remaining = 0;
            }
            else
            {
                remaining -= slot.count;
                slot.Clear();
            }
        }
    }

    if (remaining > 0)
        UIHelper::UpdateBot("제거할 아이템 수량이 부족합니다.", 1);
}

bool Inventory::Use(int displaySlot, Player* player)
{
    if (!player) return false;

    int index = displaySlot - 1;
    if (index < 0 || index >= MAX_SLOT || slots_[index].IsEmpty())
    {
        UIHelper::UpdateBot("비어있는 슬롯입니다.", 1);
        return false;
    }

    Slot& slot = slots_[index];

    ItemKey key{ slot.type, slot.id };

    Item* findItem = nullptr;

    for (const auto& it : itemData_)
    {
        Item* item_ = it.second.get();   // 밸류값
        ItemType type_ = it.first.type;  // 키값에 있는 아이템 타입(아이템 구분을 위한 타입)
        int id_ = it.first.id;           // 키값에 있는 아이템 아이디(인덱스 번호)

        if (type_ == key.type && id_ == key.id)
        {
            findItem = item_;
            break;
        }
    }

    if (findItem == nullptr)
    {
        UIHelper::UpdateBot("아이템 데이터가 없습니다.", 1);
        return false;
    }
    
    if (!findItem->Use(player))
    {
        UIHelper::UpdateBot("아이템을 사용할 수 없습니다.", 1);
        return false;
    }

    if (--slot.count <= 0)
        slot.Clear();
    UIHelper::UpdateStatus(player);
    return true;
}

int Inventory::GetItemCount(ItemType type, int id) const
{
    int total = 0;

    for (const auto& slot : slots_)
    {
        if (!slot.IsEmpty() &&
            slot.type == type &&
            slot.id == id)
        {
            total += slot.count;
        }
    }
    return total;
}

void Inventory::ShowInventory() const
{
    std::vector<std::string> displayLines;

    if (IsEmpty())
    {
        displayLines.push_back("인벤토리가 비어 있습니다.");
    }
    else
    {
        for (int i = 1; i <= MAX_SLOT; ++i)
        {
            if (IsAvailable(i))
            {
                const Slot& slot = slots_[i - 1];
                std::string itemName = "알 수 없는 아이템";

                // 타입에 따른 이름 추출 로직
                try {
                    switch (slot.type)
                    {
                    case ItemType::Potion:
                        itemName = db_.GetPotionItems((PotionID)slot.id)[0].Name;
                        break;
                    case ItemType::Equipment:
                        itemName = db_.GetEquipItems((EquipID)slot.id)[0].Name;
                        break;
                    case ItemType::Ingredient:
                        itemName = db_.GetIngredItems((IngredID)slot.id)[0].Name;
                        break;
                    }
                }
                catch (...) {
                    itemName = "데이터 없음(ID:" + std::to_string(slot.id) + ")";
                }

                // 가독성을 위해 [슬롯번호] 이름 x수량 형식으로 구성
                std::string line = "[" + std::to_string(i) + "] " + itemName + " (x" + std::to_string(slot.count) + ")";
                displayLines.push_back(line);
            }
        }
    }

    UIHelper::UpdateTopList(displayLines, "플레이어 인벤토리");
    UIHelper::UpdateBot("인벤토리를 닫으려면 [Enter]를 눌러주세요.");
    GetEnterInput(); // utf.h 등에 정의된 입력 대기 함수 호출
}
