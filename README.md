TeamProject_7 - Text RPG

## 📖 프로젝트 소개

C++ 객체지향 프로그래밍(OOP)을 기반으로 제작한 콘솔 RPG 프로젝트입니다.

플레이어는 전투, 상점, 제작 시스템을 이용하여 성장하며 다양한 아이템을 획득하고 장비를 관리할 수 있습니다.

본 프로젝트에서는 **인벤토리 시스템 설계 및 구현**을 담당하였습니다.

---

# 👨‍💻 개발 기간

2025.12 ~ 2026.01 (2개월)

---

# 👥 팀 구성

7인 팀 프로젝트

---

# 🙋 담당 역할

- Inventory System 설계 및 구현
- ItemDatabase 연동
- Item 객체 관리 구조 설계
- Equipment 시스템
- Item 사용 시스템

---

# 🛠 개발 환경

| Category | Tech |
| --- | --- |
| Language | C++17 |
| IDE | Visual Studio 2022 |
| Version Control | Git / GitHub |

---

# 📂 프로젝트 구조

```
Player
│
├── Inventory
│      │
│      ├── Slot
│      ├── Item
│      ├── Equipment
│      ├── Potion
│      └── Ingredient
│
├── ItemDatabase
│
├── Shop
│
└── Battle
```

---

# ✨ 주요 기능

## 1. 슬롯 기반 인벤토리 시스템

30칸 고정 슬롯 기반 인벤토리를 구현하였습니다.

아이템 획득 시

- 동일 아이템이면 Stack
- 새로운 아이템이면 빈 슬롯 추가

방식으로 동작하도록 설계하였습니다.

사용 완료된 아이템은 자동으로 제거되며 빈 슬롯으로 관리됩니다.

---

## 2. 객체지향 기반 아이템 시스템

Item 클래스를 부모 클래스로 설계하고

- Potion
- Equipment
- Ingredient

가 상속받도록 구현하였습니다.

아이템마다

```cpp
virtual Use();
```

를 Override하여

동일한 인터페이스로 서로 다른 기능을 수행하도록 구현하였습니다.

---

## 3. ItemDatabase 기반 데이터 관리

아이템 정보를 코드에서 직접 관리하지 않고

ItemDatabase에서 조회하도록 구현하였습니다.

이를 통해

- 이름
- 설명
- 능력치
- 가격

등을 코드 수정 없이 변경할 수 있도록 설계하였습니다.

---

## 4. STL 기반 아이템 관리

ItemType과 ItemID를 조합한 ItemKey를 생성하여

std::map 기반으로 아이템 객체를 관리하였습니다.

std::map은 **Red-Black Tree 기반 연관 컨테이너**로,

아이템 검색 및 삽입을 O(logN)에 수행할 수 있도록 구성하였습니다.

또한

```cpp
std::unique_ptr<Item>
```

를 사용하여

객체의 소유권을 명확하게 관리하고

메모리 누수를 방지하였습니다.

---

# ⚙ 시스템 흐름

```
아이템 획득

↓

ItemDatabase 조회

↓

Inventory

↓

ItemKey 생성

↓

std::map 검색

↓

Stack 여부 확인

↓

추가 또는 수량 증가
```

---

# 💡 구현하면서 고민한 점

기존에는 Item을 직접 생성하고 관리하면

아이템 종류가 늘어날수록

if / else 문이 계속 증가하는 문제가 있었습니다.

이를 해결하기 위해

- Item 부모 클래스
- Virtual Function
- ItemDatabase
- std::map
- unique_ptr

를 적용하여

새로운 아이템이 추가되어도

기존 Inventory 로직을 수정하지 않도록 구조를 개선하였습니다.

---

# 📚 주요 클래스

- Player
- Inventory
- Item
- EquipItem
- PotionItem
- IngredItem
- ItemDatabase

---

# 🖥 실행 화면

> Console RPG
> 
- 플레이어 생성
- 전투
- 상점
- 인벤토리
- 장비 장착
- 제작 시스템

---

# 📌 담당 구현 요약

✔ 슬롯 기반 Inventory

✔ ItemDatabase

✔ 객체지향 Item 구조

✔ Equipment 관리

✔ Item 사용 시스템

✔ std::map 기반 Item 관리

✔ std::unique_ptr 메모리 관리

---

# 📖 프로젝트를 통해 배운 점

객체지향 설계가 단순히 상속을 사용하는 것이 아니라

기능이 추가되어도 기존 코드를 수정하지 않는 구조를 만드는 것이라는 점을 경험했습니다.

또한 STL 컨테이너와 스마트 포인터를 활용하여

메모리 관리와 데이터 관리의 중요성을 배울 수 있었으며,

Inventory와 ItemDatabase를 분리하여 유지보수성과 확장성을 고려한 구조를 설계하는 경험을 얻었습니다.

# TeamProject_7 - Text RPG

## 📖 프로젝트 소개

C++ 객체지향 프로그래밍(OOP)을 기반으로 제작한 콘솔 RPG 프로젝트입니다.

플레이어는 전투, 상점, 제작 시스템을 통해 성장하며, 다양한 아이템을 획득하고 장비를 관리할 수 있습니다.

본 프로젝트에서 **인벤토리 시스템 설계 및 구현**을 담당했습니다.

---

# 👨‍💻 개발 기간

2025.12 ~ 2026.01 (2개월)

---

# 👥 팀 구성

4인 팀 프로젝트

---

# 🙋 담당 역할

- Inventory System 설계 및 구현
- ItemDatabase 연동
- Item 객체 관리 구조 설계
- Equipment 시스템
- Item 사용 시스템

---

# 🛠 개발 환경

| Category | Tech |
| --- | --- |
| Language | C++17 |
| IDE | Visual Studio 2022 |
| Version Control | Git / GitHub |

---

# 📂 프로젝트 구조

```
Player
│
├── Inventory
│      │
│      ├── Slot
│      ├── Item
│      ├── Equipment
│      ├── Potion
│      └── Ingredient
│
├── ItemDatabase
│
├── Shop
│
└── Battle
```

---

# ✨ 주요 기능

## 1. 슬롯 기반 인벤토리 시스템

30칸 고정 슬롯 기반 인벤토리를 구현했습니다.

아이템 획득 시

- 동일 아이템이면 Stack
- 새로운 아이템이면 빈 슬롯 추가

방식으로 동작하도록 설계했습니다.

사용이 완료된 아이템은 자동으로 제거되며, 빈 슬롯으로 관리됩니다.

---

## 2. 객체지향 기반 아이템 시스템

Item 클래스를 부모 클래스로 설계하고

- Potion
- Equipment
- Ingredient

가 상속받도록 구현했습니다.

각 아이템은

```cpp
virtual Use();
```

를 Override하여, 동일한 인터페이스로 서로 다른 기능을 수행하도록 구성했습니다.

---

## 3. ItemDatabase 기반 데이터 관리

아이템 정보를 코드에서 직접 관리하지 않고, ItemDatabase에서 조회하도록 구현했습니다.

이를 통해

- 이름
- 설명
- 능력치
- 가격

등을 코드 수정 없이 변경할 수 있도록 설계했습니다.

---

## 4. STL 기반 아이템 관리

ItemType과 ItemID를 조합한 ItemKey를 생성하고, std::map 기반으로 아이템 객체를 관리했습니다.

std::map은 **Red-Black Tree 기반 연관 컨테이너**로, 아이템 검색 및 삽입을 O(logN)에 수행할 수 있도록 구성했습니다.

또한

```cpp
std::unique_ptr<Item>
```

를 사용해 객체의 소유권을 명확히 관리하고, 메모리 누수를 방지했습니다.

---

# ⚙ 시스템 흐름

```
아이템 획득

↓

ItemDatabase 조회

↓

Inventory

↓

ItemKey 생성

↓

std::map 검색

↓

Stack 여부 확인

↓

추가 또는 수량 증가
```

---

# 💡 구현하면서 고민한 점

기존에는 Item을 직접 생성하고 관리할 경우, 아이템 종류가 늘어날수록 if / else 문이 계속 증가하는 문제가 있었습니다.

이를 해결하기 위해

- Item 부모 클래스
- Virtual Function
- ItemDatabase
- std::map
- unique_ptr

를 적용하여, 새로운 아이템이 추가되어도 기존 Inventory 로직을 수정하지 않도록 구조를 개선했습니다.

---

# 📚 주요 클래스

- Player
- Inventory
- Item
- EquipItem
- PotionItem
- IngredItem
- ItemDatabase

---

# 🖥 실행 화면

> Console RPG
> 
- 플레이어 생성
- 전투
- 상점
- 인벤토리
- 장비 장착
- 제작 시스템

---

# 📌 담당 구현 요약

✔ 슬롯 기반 Inventory

✔ ItemDatabase

✔ 객체지향 Item 구조

✔ Equipment 관리

✔ Item 사용 시스템

✔ std::map 기반 Item 관리

✔ std::unique_ptr 메모리 관리

---

# 📖 프로젝트를 통해 배운 점

객체지향 설계는 단순히 상속을 사용하는 것이 아니라, 기능이 추가되어도 기존 코드를 수정하지 않는 구조를 만드는 것임을 경험했습니다.

또한 STL 컨테이너와 스마트 포인터를 활용하며 메모리 관리와 데이터 관리의 중요성을 체감했고,

Inventory와 ItemDatabase를 분리해 유지보수성과 확장성을 고려한 구조를 설계하는 경험을 얻었습니다.