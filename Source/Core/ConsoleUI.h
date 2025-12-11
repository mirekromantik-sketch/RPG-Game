#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>
#include <windows.h>

class ConsoleUI {
public:
    // Color codes for Windows console
    enum Color {
        BLACK = 0,
        DARK_BLUE = 1,
        DARK_GREEN = 2,
        DARK_CYAN = 3,
        DARK_RED = 4,
        DARK_MAGENTA = 5,
        DARK_YELLOW = 6,
        GRAY = 7,
        DARK_GRAY = 8,
        BLUE = 9,
        GREEN = 10,
        CYAN = 11,
        RED = 12,
        MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };

    static void clearScreen();
    static void setColor(Color text, Color background = BLACK);
    static void resetColor();
    static void printHeader(const std::string& title);
    static void printSeparator(char ch = '=', int length = 60);
    static void printBox(const std::string& text);
    static void printColoredText(const std::string& text, Color color);
    static void printSuccess(const std::string& text);
    static void printError(const std::string& text);
    static void printWarning(const std::string& text);
    static void printInfo(const std::string& text);
    static void printStat(const std::string& label, const std::string& value);
    static void waitForEnter();
    
private:
    static HANDLE hConsole;
    static void initConsole();
};

#endif
