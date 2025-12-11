@echo off
echo Compiling RPG Game...

g++ -std=c++11 ^
    Source/main.cpp ^
    Source/Core/Game.cpp ^
    Source/Entities/Player/Player.cpp ^
    Source/Entities/Enemies/Enemy.cpp ^
    Source/Entities/Enemies/boss.cpp ^
    Source/Systems/Inventory/Item.cpp ^
    Source/Systems/Inventory/Inventory.cpp ^
    Source/Systems/Quest/Quest.cpp ^
    Source/Systems/Quest/QuestManager.cpp ^
    -o Build/Output/RPGGame.exe

if %errorlevel% equ 0 (
    echo.
    echo Build successful! Run the game with: Build\Output\RPGGame.exe
) else (
    echo.
    echo Build failed! Make sure g++ is installed and in your PATH.
)

pause
