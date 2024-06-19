#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

using namespace std;

class Pokemon {
public:
    string name;
    string type;
    int level;
    int hp;
    int maxHp;
    int attackPower;

    Pokemon(string n, string t, int l, int h, int ap)
        : name(n), type(t), level(l), maxHp(h), hp(h), attackPower(ap) {}

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
    }

    void heal(int amount) {
        hp += amount;
        if (hp > maxHp) hp = maxHp;
    }

    bool isFainted() {
        return hp == 0;
    }
};

void displayPokemon(const Pokemon& p) {
    cout << p.name << " (Type: " << p.type << ", Level: " << p.level << ", HP: " << p.hp << "/" << p.maxHp << ")" << endl;
}

vector<Pokemon> generateRandomPlayerPokemon() {
    vector<Pokemon> allPokemon = {
        Pokemon("Charmander", "Fire", 5, 39, 52),
        Pokemon("Squirtle", "Water", 5, 44, 48),
        Pokemon("Bulbasaur", "Grass", 5, 45, 49),
        Pokemon("Pikachu", "Electric", 5, 35, 55),
        Pokemon("Geodude", "Rock", 5, 40, 45),
        Pokemon("Pidgey", "Flying", 5, 40, 45),
        Pokemon("Rattata", "Normal", 5, 30, 56),
        Pokemon("Zubat", "Poison", 5, 40, 45),
        Pokemon("Machop", "Fighting", 5, 45, 50),
        Pokemon("Abra", "Psychic", 5, 25, 20),
        Pokemon("Magnemite", "Steel", 5, 25, 20),
        Pokemon("Diglett", "Ground", 5, 10, 55),
        Pokemon("Vulpix", "Fire", 5, 38, 41),
        Pokemon("Jigglypuff", "Fairy", 5, 115, 45),
        Pokemon("Oddish", "Grass", 5, 45, 50)
    };

    vector<Pokemon> playerPokemon;
    unordered_set<string> chosenTypes;

    while (playerPokemon.size() < 3) {
        int index = rand() % allPokemon.size();
        Pokemon p = allPokemon[index];
        if (chosenTypes.find(p.type) == chosenTypes.end()) {
            playerPokemon.push_back(p);
            chosenTypes.insert(p.type);
        }
    }

    return playerPokemon;
}

int main() {
    srand(time(0));
    string options;
    string finalChoice;

    vector<string> itemHealing = {"Potion"};
    vector<string> itemRevives = {"Revive", "Max Revive"};
    vector<string> itemStatBoosters = {"X Attack", "X Defense", "X Speed"};
    vector<string> itemThrowables = {"Poke Ball", "Great Ball", "Ultra Ball", "Master Ball"};

    vector<Pokemon> playerPokemon = generateRandomPlayerPokemon();
    vector<Pokemon> enemyPokemon = {
        Pokemon("Pidgey", "Flying", 3, 40, 45),
        Pokemon("Rattata", "Normal", 4, 30, 56)
    };

    Pokemon* currentPlayerPokemon = &playerPokemon[0];
    Pokemon* currentEnemyPokemon = &enemyPokemon[0];

    while (finalChoice != "yes") {
        cout << "Pokemon Game v1.0 \nA. Start Game \nB. Options \nC. Exit \nChoice: ";
        cin >> options;
        cout << "You picked " << options << endl;

        if (options == "A" || options == "a") {
            finalChoice = "yes";
            string battleChoice;

            cout << "Starting game now" << endl;
            cout << "Enter Trainer Name: ";
            string TrainerName;
            cin >> TrainerName;

            cout << "A wild " << currentEnemyPokemon->name << " appears!" << endl;

            while (!currentPlayerPokemon->isFainted() && !currentEnemyPokemon->isFainted()) {
                cout << "\nYour Pokemon: ";
                displayPokemon(*currentPlayerPokemon);
                cout << "Enemy Pokemon: ";
                displayPokemon(*currentEnemyPokemon);

                cout << "\nChoose an action: \nF. FIGHT \nI. ITEM \nP. POKE \nR. RUN \nChoice: ";
                cin >> battleChoice;

                if (battleChoice == "F" || battleChoice == "f") {
                    cout << currentPlayerPokemon->name << " attacks!" << endl;
                    currentEnemyPokemon->takeDamage(currentPlayerPokemon->attackPower);
                    if (!currentEnemyPokemon->isFainted()) {
                        cout << currentEnemyPokemon->name << " attacks back!" << endl;
                        currentPlayerPokemon->takeDamage(currentEnemyPokemon->attackPower);
                    }
                } else if (battleChoice == "I" || battleChoice == "i") {
                    cout << "Available items: " << endl;
                    for (const string &item : itemHealing) {
                        cout << item << " ";
                    }
                    cout << endl;

                    cout << "Choose an item to use: ";
                    string itemChoice;
                    cin >> itemChoice;

                    if (itemChoice == "Potion") {
                        int healAmount = 20; // Simplified healing amount
                        cout << "You used " << itemChoice << "!" << endl;
                        currentPlayerPokemon->heal(healAmount);
                    } else {
                        cout << "Invalid item choice." << endl;
                    }
                } else if (battleChoice == "P" || battleChoice == "p") {
                    cout << "Choose a Pokemon to swap: " << endl;
                    for (size_t i = 0; i < playerPokemon.size(); ++i) {
                        cout << i + 1 << ". ";
                        displayPokemon(playerPokemon[i]);
                    }

                    int swapChoice;
                    cin >> swapChoice;

                    if (swapChoice > 0 && swapChoice <= playerPokemon.size()) {
                        currentPlayerPokemon = &playerPokemon[swapChoice - 1];
                        cout << "Go, " << currentPlayerPokemon->name << "!" << endl;
                    } else {
                        cout << "Invalid choice." << endl;
                    }
                } else if (battleChoice == "R" || battleChoice == "r") {
                    if (rand() % 10 < 1 || currentPlayerPokemon->level >= currentEnemyPokemon->level) {
                        cout << "You successfully ran away!" << endl;
                        break;
                    } else {
                        cout << "You failed to run away!" << endl;
                        currentPlayerPokemon->takeDamage(currentEnemyPokemon->attackPower);
                    }
                } else {
                    cout << "Invalid choice. Please choose F, I, P, or R." << endl;
                }

                if (currentPlayerPokemon->isFainted()) {
                    cout << currentPlayerPokemon->name << " fainted!" << endl;
                    bool allFainted = true;
                    for (Pokemon& p : playerPokemon) {
                        if (!p.isFainted()) {
                            allFainted = false;
                            break;
                        }
                    }
                    if (allFainted) {
                        cout << "All your Pokemon have fainted! Game Over." << endl;
                        break;
                    } else {
                        cout << "Choose another Pokemon!" << endl;
                        for (size_t i = 0; i < playerPokemon.size(); ++i) {
                            cout << i + 1 << ". ";
                            displayPokemon(playerPokemon[i]);
                        }

                        int swapChoice;
                        cin >> swapChoice;

                        if (swapChoice > 0 && swapChoice <= playerPokemon.size()) {
                            currentPlayerPokemon = &playerPokemon[swapChoice - 1];
                            cout << "Go, " << currentPlayerPokemon->name << "!" << endl;
                        } else {
                            cout << "Invalid choice." << endl;
                        }
                    }
                }
            }

            if (currentEnemyPokemon->isFainted()) {
                cout << "You defeated " << currentEnemyPokemon->name << "!" << endl;
            }

        } else if (options == "B" || options == "b") {
            cout << "Options menu not implemented yet." << endl;
        } else if (options == "C" || options == "c") {
            cout << "Exiting..." << endl;
            return 0;
        } else {
            cout << "Invalid option. Please choose A, B, or C." << endl;
        }
    }

    return 0;
}
