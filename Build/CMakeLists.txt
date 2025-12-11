cmake_minimum_required(VERSION 3.10)
project(RPGGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    ../Source/main.cpp
    ../Source/Core/Game.cpp
    ../Source/Entities/Player/Player.cpp
    ../Source/Entities/Enemies/Enemy.cpp
    ../Source/Entities/Enemies/boss.cpp
    ../Source/Systems/Inventory/Inventory.cpp
    ../Source/Systems/Inventory/Item.cpp
    ../Source/Systems/Quest/Quest.cpp
    ../Source/Systems/Quest/QuestManager.cpp
    ../Source/Systems/Shop/WeaponShop.cpp
    ../Source/Systems/Shop/ArmorShop.cpp
    ../Source/Systems/Shop/PotionShop.cpp
    ../Source/Systems/Talent Points/Points.cpp
    ../Source/Systems/Talent Points/Talents.cpp
)

# Create executable
add_executable(RPGGame ${SOURCES})

# Set output directory
set_target_properties(RPGGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Output"
)
