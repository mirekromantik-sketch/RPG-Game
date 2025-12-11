#include "PotionShop.h"
#include <iostream>
#include <vector>

using namespace std;

struct PotionItem {
    string name;
    string description;
    int price;
    ItemType type;
    int value;
};

void openPotionShop(Player& player) {
    vector<PotionItem> potions = {
        {"Minor Health Potion", "Restores 30 HP", 20, ItemType::CONSUMABLE, 30},
        {"Health Potion", "Restores 50 HP", 40, ItemType::CONSUMABLE, 50},
        {"Greater Health Potion", "Restores 100 HP", 80, ItemType::CONSUMABLE, 100},
        {"Superior Health Potion", "Restores 200 HP", 150, ItemType::CONSUMABLE, 200},
        {"Elixir of Strength", "Temporarily increases strength", 100, ItemType::CONSUMABLE, 10},
        {"Elixir of Magic", "Temporarily increases magic", 100, ItemType::CONSUMABLE, 10},
        {"Elixir of Defense", "Temporarily increases defense", 100, ItemType::CONSUMABLE, 10},
        {"XP Elixir x100", "Multiplies XP gain by 100 for next battle", 5000, ItemType::CONSUMABLE, 100}
    };
    
    bool shopping = true;
    while (shopping) {
        cout << "\n=== Potion Shop ===" << endl;
        cout << "Your Gold: " << player.getGold() << endl;
        cout << "\n--- Available Potions ---" << endl;
        
        for (size_t i = 0; i < potions.size(); i++) {
            cout << (i + 1) << ". " << potions[i].name << " - " << potions[i].price << " gold" << endl;
            cout << "   " << potions[i].description << endl;
        }
        
        cout << "\n" << (potions.size() + 1) << ". Leave Shop" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == (int)potions.size() + 1) {
            shopping = false;
            cout << "Thanks for visiting!" << endl;
        } else if (choice > 0 && choice <= (int)potions.size()) {
            PotionItem& item = potions[choice - 1];
            
            if (player.getGold() >= item.price) {
                player.addGold(-item.price);
                player.getInventory().addItem(Item(item.name, item.description, item.type, item.value));
                cout << "Purchased " << item.name << "!" << endl;
            } else {
                cout << "Not enough gold! You need " << item.price << " gold." << endl;
            }
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
}
