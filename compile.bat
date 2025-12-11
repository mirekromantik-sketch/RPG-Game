@echo off
echo Compiling RPG Game...

REM ====== SET YOUR MINGW PATH HERE ======
set MINGW=C:\msys64\mingw64\bin
REM ======================================

"%MINGW%\g++" -std=c++11 ^
    Source/main.cpp ^
    Source/Core/Game.cpp ^
    Source/Core/ConsoleUI.cpp ^
    Source/Core/SaveManager.cpp ^
    Source/Entities/Player/Player.cpp ^
    Source/Entities/Enemies/Enemy.cpp ^
    Source/Entities/Enemies/boss.cpp ^
    Source/Systems/Inventory/Item.cpp ^
    Source/Systems/Inventory/Inventory.cpp ^
    Source/Systems/Quest/Quest.cpp ^
    Source/Systems/Quest/QuestManager.cpp ^
    Source/Systems/Shop/WeaponShop.cpp ^
    Source/Systems/Shop/ArmorShop.cpp ^
    Source/Systems/Shop/PotionShop.cpp ^
    Source/Systems/Shop/BackpackShop.cpp ^
    Source/Systems/NPC/NPC.cpp ^
    Source/Systems/Town/Town.cpp ^
    Source/Systems/Boss/BossManager.cpp ^
    Source/Systems/"Talent Points"/Points.cpp ^
    Source/Systems/"Talent Points"/Talents.cpp ^
    -static -static-libgcc -static-libstdc++ ^
    -o Build/Output/RPGGame.exe


if %errorlevel% equ 0 (
    echo.
    echo Build successful! Standalone EXE created:
    echo   Build\Output\RPGGame.exe
) else (
    echo.
    echo Build failed! Check error messages and MinGW path.
)

pause
