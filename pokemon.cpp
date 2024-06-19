#include <iostream>

using namespace std;

int main() {
    string options;
    int wallLimit = 10;
    string TrainerName;

    // Print the wall
    for (int i = 0; i < wallLimit; i++) {
        cout << "=";
    }
    cout << " " << endl;

    // Menu
    cout << "Pokemon Game v1.0 \nA. Start Game \nB. Options \nC. Exit \nChoice: ";
    cin >> options;
    cout << "You picked " << options << endl;

    // Improved if-else conditions (check for single characters)
    if (options == "A" || options == "a") {
        // Put the whole game here
        cout << "Starting game now" << endl;
    } else if (options == "B" || options == "b") {
        // Difficulty Scaling here
        cout << "Difficulty Setting Available: " << endl;
    } else if (options == "C" || options == "c") {
        cout << "Exiting..." << endl;
        return 0; // Exit the program immediately
    } else {
        cout << "Invalid option. Please choose A, B, or C." << endl;
    }

    // Name Input (only prompted if a valid choice is made)
    cout << "Enter Name: ";
    cin >> TrainerName;

    return 0; // Return 0 to indicate successful program execution
}
