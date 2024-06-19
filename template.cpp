#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

const int MAX_PARTY_SIZE = 6;

struct Pokemon {
    std::string name;
    int attack;
    int defense;
    int hp;
};

struct Player {
    Pokemon party[MAX_PARTY_SIZE];
    int partySize;
    int pokeCurrency;
    std::string items[12];
    int itemCount;

    Player() {
        partySize = 0;
        pokeCurrency = 100;
        itemCount = 0;
    }
};

void addPokemon(Player &player, Pokemon pokemon) {
    if (player.partySize < MAX_PARTY_SIZE) {
        player.party[player.partySize] = pokemon;
        player.partySize++;
    } else {
        for (int i = 1; i < MAX_PARTY_SIZE; ++i) {
            player.party[i-1] = player.party[i];
        }
        player.party[MAX_PARTY_SIZE - 1] = pokemon;
    }
}

void displayParty(const Player &player) {
    for (int i = 0; i < player.partySize; ++i) {
        std::cout << i + 1 << ". " << player.party[i].name << " (HP: " << player.party[i].hp << ")\n";
    }
}

void battle(Player &player) {
    Pokemon opponent = {"Wild Rattata", 56, 35, 30};

    std::cout << "A wild " << opponent.name << " appeared!\n";
    std::cout << "Go! " << player.party[0].name << "!\n";

    while (player.party[0].hp > 0 && opponent.hp > 0) {
        int damageToOpponent = (player.party[0].attack - opponent.defense);
        int damageToPlayer = (opponent.attack - player.party[0].defense);

        if (damageToOpponent < 1) damageToOpponent = 1;
        if (damageToPlayer < 1) damageToPlayer = 1;

        opponent.hp -= damageToOpponent;
        player.party[0].hp -= damageToPlayer;

        std::cout << player.party[0].name << " dealt " << damageToOpponent << " damage!\n";
        std::cout << opponent.name << " dealt " << damageToPlayer << " damage!\n";
    }

    if (player.party[0].hp > 0) {
        std::cout << "You defeated " << opponent.name << "!\n";
        player.pokeCurrency += 50;
        player.items[player.itemCount] = "Potion";
        player.itemCount++;
        std::cout << "You received a Potion!\n";
        std::cout << "You earned 50 Poke!\n";
    } else {
        std::cout << player.party[0].name << " fainted!\n";
    }
}

void buyPokemon(Player &player) {
    Pokemon shop[] = {
        {"Bulbasaur", 49, 49, 45},
        {"Charmander", 52, 43, 39},
        {"Squirtle", 48, 65, 44},
        {"Pikachu", 55, 40, 35},
        {"Eevee", 55, 50, 55},
        {"Jigglypuff", 45, 20, 115}
    };

    std::cout << "Welcome to the Pokemon Shop!\n";
    for (int i = 0; i < 6; ++i) {
        std::cout << i + 1 << ". " << shop[i].name << " (HP: " << shop[i].hp << ")\n";
    }

    int choice;
    std::cout << "Choose a Pokemon to buy (1-6): ";
    std::cin >> choice;

    if (choice >= 1 && choice <= 6 && player.pokeCurrency >= 100) {
        addPokemon(player, shop[choice - 1]);
        player.pokeCurrency -= 100;
        std::cout << "You bought " << shop[choice - 1].name << "!\n";
    } else {
        std::cout << "Invalid choice or not enough Poke.\n";
    }
}

int main() {
    srand(time(0));
    Player player;
    addPokemon(player, {"Pikachu", 55, 40, 35});

    while (true) {
        std::cout << "1. Battle\n";
        std::cout << "2. Buy Pokemon\n";
        std::cout << "3. View Party\n";
        std::cout << "4. View Items\n";
        std::cout << "5. Exit\n";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            battle(player);
        } else if (choice == 2) {
            buyPokemon(player);
        } else if (choice == 3) {
            displayParty(player);
        } else if (choice == 4) {
            std::cout << "Items:\n";
            for (int i = 0; i < player.itemCount; ++i) {
                std::cout << "- " << player.items[i] << "\n";
            }
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
