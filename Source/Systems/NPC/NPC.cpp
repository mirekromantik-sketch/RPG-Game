#include "NPC.h"
#include "../../Core/ConsoleUI.h"
#include <iostream>

using namespace std;

NPC::NPC(string name, NPCType type, string location)
    : name(name), type(type), location(location), dialogueState(0), hasQuest(false) {}

void NPC::addDialogue(const string& option, const string& response) {
    dialogueOptions.push_back(option);
    responses.push_back(response);
}

void NPC::setQuest(const string& questId) {
    hasQuest = true;
    this->questId = questId;
}

void NPC::talk() {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("=== TALKING WITH " + name + " ===");
    
    string typeStr;
    switch (type) {
        case NPCType::MERCHANT: typeStr = "Merchant"; break;
        case NPCType::QUEST_GIVER: typeStr = "Quest Giver"; break;
        case NPCType::INNKEEPER: typeStr = "Innkeeper"; break;
        case NPCType::GUARD: typeStr = "Guard"; break;
        case NPCType::VILLAGER: typeStr = "Villager"; break;
        case NPCType::SAGE: typeStr = "Sage"; break;
    }
    
    ConsoleUI::setColor(ConsoleUI::Color::CYAN, ConsoleUI::Color::BLACK);
    cout << "\n[" << name << " - " << typeStr << " in " << location << "]" << endl;
    ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    
    if (hasQuest) {
        ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
        cout << "(!)" << endl;
        ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
    }
    
    showDialogueMenu();
}

void NPC::showDialogueMenu() {
    ConsoleUI::printSeparator();
    
    if (dialogueOptions.empty()) {
        cout << "\n" << name << ": \"Greetings, traveler.\"" << endl;
        cout << "\n1. Goodbye" << endl;
        cout << "\nChoice: ";
        int choice;
        cin >> choice;
        return;
    }
    
    bool talking = true;
    while (talking) {
        cout << "\nWhat do you want to talk about?" << endl;
        
        for (size_t i = 0; i < dialogueOptions.size(); i++) {
            cout << (i + 1) << ". " << dialogueOptions[i] << endl;
        }
        cout << "0. Goodbye" << endl;
        
        cout << "\nChoice: ";
        int choice;
        cin >> choice;
        
        if (choice == 0) {
            ConsoleUI::printInfo(name + ": \"Farewell, traveler.\"");
            talking = false;
        } else if (choice > 0 && choice <= (int)dialogueOptions.size()) {
            cout << "\n";
            ConsoleUI::setColor(ConsoleUI::Color::YELLOW, ConsoleUI::Color::BLACK);
            cout << name << ": ";
            ConsoleUI::setColor(ConsoleUI::Color::WHITE, ConsoleUI::Color::BLACK);
            cout << "\"" << responses[choice - 1] << "\"" << endl;
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        } else {
            ConsoleUI::printError("Invalid choice!");
        }
    }
}
