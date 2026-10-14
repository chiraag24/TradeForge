#include <iostream>
#include <string>
#include <vector>
#include <random> //used for the RNG

//Rarity uses an enum because every item should have
// One value ONLY from a fixed set of valid rarity levels

enum Rarity {
    COMMON, //0
    UNCOMMON, //1
    RARE, //2
    EPIC, //3
    LEGENDARY //4
};
// Collectible item information
class Item {
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

//V0.3
//Generates a pack by randomly selecting Items
//From the existing loot pool
//
//const reference is used so the entire vector is not copied,
// while also preventing this function from modifying the pool

// Chooses a rarity using weighted probabilities
Rarity chooseRarity(std::mt19937& generator) {
    std::discrete_distribution<int> rarityDistribution({
        50, //COMMON
        25, //UNCOMMON
        15, //RARE
        8, //EPIC
        2 //Legendary
    });
    int rarityIndex = rarityDistribution(generator);

    return static_cast<Rarity>(rarityIndex);

}

const Item& getRandomItemByRarity(
    const std::vector<Item>& itemPool,
    Rarity targetRarity,
    std::mt19937& generator
){
    //Stores the indexes of every item
    // that matches the rarity we are looking for

    std::vector<int> matchingIndexes;

    for(int i = 0; i < itemPool.size(); i++){

        if (itemPool[i].rarity == targetRarity){
            matchingIndexes.push_back(i);
        }
    }

//If no items exist in that rarity
// randomly choose from the entire item pool instead
if (matchingIndexes.empty()){
  std::uniform_int_distribution<int> fallbackDistribution(
    0,
    itemPool.size() - 1
  );
 return itemPool[fallbackDistribution(generator)];
}
// Randomly chooses one position from matchingIndexes.
    std::uniform_int_distribution<int> itemDistribution(
        0,
        matchingIndexes.size() - 1
    );

    int selectedPosition = itemDistribution(generator);

    // Gets the actual index of the Item inside itemPool.
    int itemIndex = matchingIndexes[selectedPosition];

    // Returns the original matching Item without copying it.
    return itemPool[itemIndex];
}


std::vector<Item> openPack(
    const std::vector<Item>& itemPool,
    std::mt19937& generator
){
    const int PACK_SIZE = 3;

    // Stores the actual items that are pulled
    std::vector<Item> pack;

    //Prevents random selection from an empty item pool
     if (itemPool.empty()) {
        std::cout << "No items are available to generate a pack.\n";
        return pack;
    }
    //Runs once for each slot in the pack
    for(int i = 0; i < PACK_SIZE; i++){
    // Step 1: choose the rarity for this pack slot.
     Rarity selectedRarity = chooseRarity(generator);

   // Step 2: choose an actual Item with that rarity
           const Item& pulledItem =
            getRandomItemByRarity(
                itemPool,
                selectedRarity,
                generator
            );

        // Step 3: store the pulled Item in the pack.
        pack.push_back(pulledItem);

    }
    //Sends completed pack back to main()
    return pack;
}


int main() {

// Seeds the random number generator once when the program starts.
// Using the current time helps produce different results for each run.
std::random_device randomDevice;
std::mt19937 generator(randomDevice());

    Item item1;
    item1.name = "Ember Blade";
    item1.rarity = RARE;
    item1.category = "Weapon";
    item1.value = 75;

    Item item2;
    item2.name = "Tide Crystal";
    item2.rarity = COMMON;
    item2.category = "Crystal";
    item2.value = 15;

    Item item3;
    item3.name = "Void Crown";
    item3.rarity = LEGENDARY;
    item3.category = "Artifact";
    item3.value = 250;

    Item item4;
item4.name = "Silver Crest";
item4.rarity = UNCOMMON;
item4.category = "Artifact";
item4.value = 35;

Item item5;
item5.name = "Storm Relic";
item5.rarity = EPIC;
item5.category = "Artifact";
item5.value = 140;

// itemPool represents every Item that can currently
// be selected when generating a TradeForge pack
    std::vector<Item> itemPool;

//Adds each item to the end of the vector 
    itemPool.push_back(item1);
    itemPool.push_back(item2);
    itemPool.push_back(item3);
    itemPool.push_back(item4);
    itemPool.push_back(item5);

// Stores the completed pack returned by openPack().
std::vector<Item> pack = openPack(itemPool, generator);
std::cout << "===== PACK OPENED =====\n\n";

// Displays every Item that was stored inside the pack.
for (const Item& item : pack) {
    item.display();
}

    return 0;
}