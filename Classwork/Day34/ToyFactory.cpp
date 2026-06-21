#include <iostream>
#include <string>
using namespace std;

// Base Class
class Toy {
public:
    string typeName;

    void prepare() {
        cout << "[System] Preparing the " << typeName << "..." << endl;
        buildSteps();
    }

    // This will be specialized by the child classes
    virtual void buildSteps() = 0;
    
    void pack() {
        cout << "[System] Packing " << typeName << " into its box." << endl;
    }
};

// Toy: Car
class Car : public Toy {
public:
    Car() { typeName = "Race Car"; }
    
    void buildSteps() override {
        cout << " -> Attaching wheels." << endl;
        cout << " -> Painting body red." << endl;
    }
};

//  Toy: Doll
class Doll : public Toy {
public:
    Doll() { typeName = "Fashion Doll"; }

    void buildSteps() override {
        cout << " -> Adding hair." << endl;
        cout << " -> Fitting the dress." << endl;
    }
};

class ToyFactory {
public:
    // creating static versions of the toys inside the factory
    static Car toyCar;
    static Doll toyDoll;

    static Toy& getToy(int choice) {
        if (choice == 1) {
            return toyCar;
        } else {
            return toyDoll;
        }
    }
};

// Initializing the static members
Car ToyFactory::toyCar;
Doll ToyFactory::toyDoll;

// Main Program
int main() {
    cout << "--- SIMPLE TOY FACTORY---" << endl;
    cout << "Press 1 for Car, 2 for Doll: ";
    int choice;
    cin >> choice;

    // using a reference (&) to catch the toy from the factory
    Toy& myToy = ToyFactory::getToy(choice);

    myToy.prepare();
    myToy.pack();

    cout << "\nProduction complete!" << endl;

    return 0;
}