#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

using namespace std;

class Dino {
public:
    string name;
    string type;
    int level;
    int hp;
    int maxHp;
    int attackPower;

    Dino(string n, string t, int l, int h, int ap)
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

void displayDino(const Dino& d) {
    cout << d.name << " (Type: " << d.type << ", Level: " << d.level << ", HP: " << d.hp << "/" << d.maxHp << ")" << endl;
}

vector<Dino> generateRandomPlayerDinos() {
    vector<Dino> allDinos = {
        Dino("FlameRex", "Fire", 5, 39, 52),
        Dino("AquaSaur", "Water", 5, 44, 48),
        Dino("LeafZilla", "Grass", 5, 45, 49),
        Dino("Sparky", "Electric", 5, 35, 55),
        Dino("Rocky", "Rock", 5, 40, 45),
        Dino("Windrake", "Flying", 5, 40, 45),
        Dino("Terra", "Ground", 5, 30, 56),
        Dino("Venom", "Poison", 5, 40, 45),
        Dino("Brute", "Fighting", 5, 45, 50),
        Dino("Mystic", "Psychic", 5, 25, 20),
        Dino("Steelus", "Steel", 5, 25, 20),
        Dino("Tremor", "Ground", 5, 10, 55),
        Dino("Inferno", "Fire", 5, 38, 41),
        Dino("Fairydactyl", "Fairy", 5, 115, 45),
        Dino("Foliage", "Grass", 5, 45, 50)
    };

    vector<Dino> playerDinos;
    unordered_set<string> chosenTypes;

    while (playerDinos.size() < 3) {
        int index = rand() % allDinos.size();
        Dino d = allDinos[index];
        if (chosenTypes.find(d.type) == chosenTypes.end()) {
            playerDinos.push_back(d);
            chosenTypes.insert(d.type);
        }
    }

    return playerDinos;
}

int main() {
    srand(time(0));
    string options;
    string finalChoice;

    vector<string> itemHealing = {"Potion"};
    vector<string> itemRevives = {"Revive", "Max Revive"};
    vector<string> itemStatBoosters = {"X Attack", "X Defense", "X Speed"};
    vector<string> itemThrowables = {"Dino Ball", "Great Ball", "Ultra Ball", "Master Ball"};

    vector<Dino> playerDinos = generateRandomPlayerDinos();
    vector<Dino> enemyDinos = {
        Dino("Windrake", "Flying", 3, 40, 45),
        Dino("Terra", "Ground", 4, 30, 56)
    };

    Dino* currentPlayerDino = &playerDinos[0];
    Dino* currentEnemyDino = &enemyDinos[0];

    while (finalChoice != "yes") {
        cout << "DinoBattle v1.0 \nA. Start Game \nB. Options \nC. Exit \nChoice: ";
        cin >> options;
        cout << "You have picked " << options << endl;

        if (options == "A" || options == "a") {
            finalChoice = "yes";
            string battleChoice;

            cout << "Starting your game now" << endl;
            cout << "Enter Your Player Name: ";
            string TrainerName;
            cin >> TrainerName;

            cout << "A wild " << currentEnemyDino->name << " appears!" << endl;

            while (!currentPlayerDino->isFainted() && !currentEnemyDino->isFainted()) {
                cout << "\nYour Dino: ";
                displayDino(*currentPlayerDino);
                cout << "Enemy Dino: ";
                displayDino(*currentEnemyDino);

                cout << "\nChoose an action: \nF. FIGHT \nI. ITEM \nP. POKE \nR. RUN \nChoice: ";
                cin >> battleChoice;

                if (battleChoice == "F" || battleChoice == "f") {
                    cout << currentPlayerDino->name << " attacks!" << endl;
                    currentEnemyDino->takeDamage(currentPlayerDino->attackPower);
                    if (!currentEnemyDino->isFainted()) {
                        cout << currentEnemyDino->name << " attacks back!" << endl;
                        currentPlayerDino->takeDamage(currentEnemyDino->attackPower);
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
                        currentPlayerDino->heal(healAmount);
                    } else {
                        cout << "Invalid item choice." << endl;
                    }
                } else if (battleChoice == "P" || battleChoice == "p") {
                    cout << "Choose a Dino to swap: " << endl;
                    for (size_t i = 0; i < playerDinos.size(); ++i) {
                        cout << i + 1 << ". ";
                        displayDino(playerDinos[i]);
                    }

                    int swapChoice;
                    cin >> swapChoice;

                    if (swapChoice > 0 && swapChoice <= playerDinos.size()) {
                        currentPlayerDino = &playerDinos[swapChoice - 1];
                        cout << "Go, " << currentPlayerDino->name << "!" << endl;
                    } else {
                        cout << "Invalid choice." << endl;
                    }
                } else if (battleChoice == "R" || battleChoice == "r") {
                    if (rand() % 10 < 1 || currentPlayerDino->level >= currentEnemyDino->level) {
                        cout << "You successfully ran away!" << endl;
                        break;
                    } else {
                        cout << "You failed to run away!" << endl;
                        currentPlayerDino->takeDamage(currentEnemyDino->attackPower);
                    }
                } else {
                    cout << "Invalid choice. Please choose F, I, P, or R." << endl;
                }

                if (currentPlayerDino->isFainted()) {
                    cout << currentPlayerDino->name << " fainted!" << endl;
                    bool allFainted = true;
                    for (Dino& d : playerDinos) {
                        if (!d.isFainted()) {
                            allFainted = false;
                            break;
                        }
                    }
                    if (allFainted) {
                        cout << "All your Dinos have fainted! Game Over." << endl;
                        break;
                    } else {
                        cout << "Choose another Dino!" << endl;
                        for (size_t i = 0; i < playerDinos.size(); ++i) {
                            cout << i + 1 << ". ";
                            displayDino(playerDinos[i]);
                        }

                        int swapChoice;
                        cin >> swapChoice;

                        if (swapChoice > 0 && swapChoice <= playerDinos.size()) {
                            currentPlayerDino = &playerDinos[swapChoice - 1];
                            cout << "Go, " << currentPlayerDino->name << "!" << endl;
                        } else {
                            cout << "Invalid choice." << endl;
                        }
                    }
                }
            }

            if (currentEnemyDino->isFainted()) {
                cout << "You defeated " << currentEnemyDino->name << "!" << endl;
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
