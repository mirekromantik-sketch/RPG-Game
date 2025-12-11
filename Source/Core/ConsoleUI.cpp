#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

using namespace std;

HANDLE ConsoleUI::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleUI::initConsole() {
    if (hConsole == NULL) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }
}

void ConsoleUI::clearScreen() {
    initConsole();
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void ConsoleUI::setColor(Color text, Color background) {
    initConsole();
    SetConsoleTextAttribute(hConsole, (background << 4) | text);
}

void ConsoleUI::resetColor() {
    setColor(GRAY, BLACK);
}

void ConsoleUI::printHeader(const string& title) {
    clearScreen();
    printSeparator('=', 70);
    setColor(CYAN, BLACK);
    cout << "                    ";
    setColor(YELLOW, BLACK);
    cout << title;
    resetColor();
    cout << endl;
    printSeparator('=', 70);
    cout << endl;
}

void ConsoleUI::printSeparator(char ch, int length) {
    setColor(DARK_CYAN, BLACK);
    for (int i = 0; i < length; i++) {
        cout << ch;
    }
    resetColor();
    cout << endl;
}

void ConsoleUI::printBox(const string& text) {
    int width = 60;
    printSeparator('-', width);
    setColor(WHITE, BLACK);
    cout << "  " << text << endl;
    resetColor();
    printSeparator('-', width);
}

void ConsoleUI::printColoredText(const string& text, Color color) {
    setColor(color, BLACK);
    cout << text;
    resetColor();
}

void ConsoleUI::printSuccess(const string& text) {
    setColor(GREEN, BLACK);
    cout << "[SUCCESS] ";
    resetColor();
    cout << text << endl;
}

void ConsoleUI::printError(const string& text) {
    setColor(RED, BLACK);
    cout << "[ERROR] ";
    resetColor();
    cout << text << endl;
}

void ConsoleUI::printWarning(const string& text) {
    setColor(YELLOW, BLACK);
    cout << "[WARNING] ";
    resetColor();
    cout << text << endl;
}

void ConsoleUI::printInfo(const string& text) {
    setColor(CYAN, BLACK);
    cout << "[INFO] ";
    resetColor();
    cout << text << endl;
}

void ConsoleUI::printStat(const string& label, const string& value) {
    setColor(YELLOW, BLACK);
    cout << left << setw(25) << label << ": ";
    setColor(WHITE, BLACK);
    cout << value << endl;
    resetColor();
}

void ConsoleUI::waitForEnter() {
    setColor(DARK_GRAY, BLACK);
    cout << "\nPress Enter to continue...";
    resetColor();
    cin.ignore();
    cin.get();
}
