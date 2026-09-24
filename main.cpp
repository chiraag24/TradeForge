#include <iostream>
#include <string>
#include <vector>

//Rarity uses an enum because every item should have
// One value ONLY from a fixed set of valid rarity levels

enum Rarity {
    COMMON,
    UNCOMMON,
    RARE,
    EPIC,
    LEGENDARY
};
// Collectible item information
class item {
public:
std::string name;
Rarity rarity;
//Category = Groups item by type Ex: Weapon, Crystal, or Artifact
std::string category;
//Value = The worth of it for "TradeForge" internal value score
int value;

// Displays items information in a consistent format
void display() const {
    std::cout << "Name: " << name << '\n';
    std::cout << "Category: " << category << '\n';
    std::cout << "Value: " << value << '\n';
    std::cout << "Rarity: ";

//Converts the rarity enum value into readable text

    switch(rarity){
       case COMMON: std::cout << "Common";
       break;

       case UNCOMMON: std::cout << "Uncommon";
       break;
        
       case RARE: std::cout << "Rare";
       break;
        
       case EPIC: std::cout << "Epic";
       break;
        
       case LEGENDARY: std::cout << "Legendary";
       break;
        
        
    }
    
    std::cout << "\n\n";
}
};



int main() {

    item item1;
    item1.name = "Ember Blade";
    item1.rarity = RARE;
    item1.category = "Weapon";
    item1.value = 75.0;

    item item2;
    item2.name = "Tide Crystal";
    item2.rarity = COMMON;
    item2.category = "Crystal";
    item2.value = 15.0;

    item item3;
    item3.name = "Void Crown";
    item3.rarity = LEGENDARY;
    item3.category = "Artifact";
    item3.value = 250.0;

//Stores item into a dynamic collection
//Needed as more items will be added
//Keeping items togther will make searching, sorting, 
//pack generation, and inventory management later easier.
    std::vector<item> items;

//Adds each item to the end of the vector 
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);

  //Loops through each Item without copying or modifying it
    for(const item& item : items){
        item.display();
    }
     // REMOVED:
    // item1.display();
    // item2.display();
    // item3.display();

    return 0;
}