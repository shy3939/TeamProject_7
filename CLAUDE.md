# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

This is a Visual Studio 2022 C++ console application (v143 toolset, Windows 10 SDK).

**Using Visual Studio:**
- Open `TeamProject_7.sln`
- Build: `Ctrl+Shift+B` or Build → Build Solution
- Run: `F5` (debug) or `Ctrl+F5` (run without debugging)

**Using MSBuild (command line):**
```batch
msbuild TeamProject_7.sln /p:Configuration=Debug /p:Platform=x64
```

**Output:** Console executable in `x64/Debug/` or `x64/Release/`

## Architecture Overview

This is a text-based RPG game with Korean UI, featuring turn-based combat, inventory management, and a crafting system.

### Core Game Loop (main.cpp)
1. Title screen animation → Player name input
2. Main loop: `GameField::Enter()` → optional `ShopField::Enter()` → repeat until game over

### Class Hierarchy

**Field System** (polymorphic scene management):
- `Field` (abstract base) - defines `Enter(Player*)` interface
- `GameField` - combat encounters, monster spawning, battle logic
- `ShopField` - buy/sell items, random stock with price variation

**Monster System**:
- `Monster` (abstract base) - stats (HP/ATK/STR/AGI/VIT/INT/LUK), pure virtual `MonsterATK()`, `TakeDamage()`, `InitRandom()`
- `Goblin` - standard monster with randomized stats based on player level
- `BossMonster` - decorator pattern, wraps a base monster with enhanced stats

**Item System**:
- `Item` (abstract base) - `Use(Player*)` interface, holds `ItemDatabase` reference
- `EquipItem` - equipment with slot types (Weapon/Armor/Gloves/Shoes)
- `PotionItem` - consumables (HP/ATK potions)
- `IngredItem` - crafting materials
- `ItemDatabase` - static item data lookup by enum ID
- `Inventory` - slot-based storage (30 slots), maps `ItemKey` to `Item` instances

**Crafting System**:
- `Recipe` / `RecipeInput` / `RecipeOutput` - crafting recipe definitions
- `RecipeDatabase` - recipe lookup

**Player**:
- Stats: level, HP, ATK, gold, and RPG attributes (STR/AGI/VIT/INT/LUK)
- Equipment slots via `EquipmentSlots` struct
- Owns `Inventory` instance

**UI Layer**:
- `UIHelper` namespace - console output management, status display, visual effects
- `AsciiArt.h` - title screen and visual assets
- `utf.h/cpp` - UTF-8 console handling for Korean text

### Key Patterns

- **All item types use enum IDs** (`EquipID`, `PotionID`, `IngredID`) for database lookup
- **Console encoding**: `SetConsoleOutputCP(65001)` + `/utf-8` compiler flag for Korean text
- **Stat-based combat**: Damage/evasion/crit calculated from STR/AGI/VIT/INT/LUK attributes

## Language

- Code comments and UI strings are in Korean
- Variable/function names use English