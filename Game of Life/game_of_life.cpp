#include "game_of_life.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifdef _WIN32
#include <windows.h> // for Windows
#else
#include <unistd.h> // for Linux/Unix
#endif

using namespace std;

#ifdef _WIN32
void clear_screen() {
    system("cls");
}
#else
void clear_screen() {
    system("clear");
}
#endif

game_of_life::game_of_life() {
    // Initialize the random number generator
    srand(time(nullptr));

    // Initialize the game board with random values
    for (int i = 0; i < REDAKA; ++i) {
        for (int j = 0; j < STUPACA; ++j) {
            _generacija[i][j] = slucajna_vrijednost();
        }
    }
}

bool game_of_life::slucajna_vrijednost() {
    // Generate a random value (0 or 1)
    return rand() % 2 == 0;
}

bool game_of_life::celija_zauzeta(int i, int j) {
    // Check if cell at position (i, j) is occupied
    return _generacija[i][j];
}

void game_of_life::sljedeca_generacija() {
    // Create a vector for the next generation
    vector<vector<bool>> nova_generacija(REDAKA, vector<bool>(STUPACA, false));

    // Implement the logic for calculating the next generation
    // Iterate through each cell
    for (int i = 0; i < REDAKA; ++i) {
        for (int j = 0; j < STUPACA; ++j) {
            int susjedi = 0;

            // Count the number of alive neighbors
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    if (!(x == 0 && y == 0) && (i + x >= 0 && i + x < REDAKA) && (j + y >= 0 && j + y < STUPACA)) {
                        if (_generacija[i + x][j + y]) {
                            ++susjedi;
                        }
                    }
                }
            }

            // Apply the rules of the game
            if (_generacija[i][j]) {
                nova_generacija[i][j] = (susjedi == 2 || susjedi == 3);
            }
            else {
                nova_generacija[i][j] = (susjedi == 3);
            }
        }
    }

    // Update the current generation with the next generation
    for (int i = 0; i < REDAKA; ++i) {
        for (int j = 0; j < STUPACA; ++j) {
            _generacija[i][j] = nova_generacija[i][j];
        }
    }
}

void game_of_life::iscrtaj() {
    // Clear the screen
    clear_screen();

    // Display the current state of the game board
    for (int i = 0; i < REDAKA; ++i) {
        for (int j = 0; j < STUPACA; ++j) {
            if (_generacija[i][j]) {
                cout << "*"; // Print alive cell
            }
            else {
                cout << "-"; // Print dead cell
            }
        }
        cout << endl;
    }
}
