@echo off
cd /d "C:\Users\micah\OneDrive\Desktop\DSA Fall 2025\Snake"
g++ -std=c++17 main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o snake_game.exe
if %errorlevel% equ 0 (
    echo Compilation successful! Starting game...
    snake_game.exe
) else (
    echo Compilation failed!
    pause
)