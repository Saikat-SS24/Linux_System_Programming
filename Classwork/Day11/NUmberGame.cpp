/* Implement a game where user guesses a random number */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // Makes the number different every time
    int secret = rand() % 10 + 1; // Pick a number between 1 and 10
    int guess = 0;

    cout << "Guess a number between 1 and 10!" << endl;

    // Loop until the guess matches the secret
    while (guess != secret) {
        cout << "Your guess: ";
        cin >> guess;

        if (guess < secret) {
            cout << "Higher!" << endl;
        } 
        else if (guess > secret) {
            cout << "Lower!" << endl;
        }
    }

    cout << "You got it! The number was " << secret << endl;

    return 0;
}
