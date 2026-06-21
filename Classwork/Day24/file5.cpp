#include <iostream>
#include <typeinfo>    // typeid, type_info, bad_typeid
#include <string>

// ─── Class hierarchy for RTTI demos ──────────────────────────────────
class Animal {
public:
    std::string name;
    Animal(const std::string& n) : name(n) {}
    virtual ~Animal() = default;
    virtual std::string speak() const = 0;
};

class Dog : public Animal {
public:
    std::string breed;
    Dog(const std::string& n, const std::string& b)
        : Animal(n), breed(b) {}
    std::string speak() const override { return "Woof!"; }
    void fetch() const { std::cout << name << " fetches!\n"; }
};

class Cat : public Animal {
public:
    bool indoor;
    Cat(const std::string& n, bool i) : Animal(n), indoor(i) {}
    std::string speak() const override { return "Meow!"; }
    void purr()  const { std::cout << name << " purrs...\n"; }
};

class GoldenRetriever : public Dog {
public:
    GoldenRetriever(const std::string& n)
        : Dog(n, "Golden Retriever") {}
    std::string speak() const override { return "Woof woof!"; }
};


class Huskie : public Dog {
public:
    Huskie(const std::string& n)
        : Dog(n, "Huskie") {}
    std::string speak() const override { return "Woof1 woof1!"; }
};

// ─── Non-polymorphic class (no virtual functions) ─────────────────────
class Plain {
public:
    int value;
    Plain(int v) : value(v) {}
    // NO virtual functions → not polymorphic → typeid gives static type
};

int main() {
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "║   typeid Operator — Complete Demo        ║\n";
    std::cout << "╚══════════════════════════════════════════╝\n\n";

    // ── 1. typeid on compile-time types ──────────────────────────────
    std::cout << "─── typeid on compile-time types ───\n";
    std::cout << "typeid(int).name()         = " << typeid(int).name()         << "\n";
    std::cout << "typeid(double).name()      = " << typeid(double).name()      << "\n";
    std::cout << "typeid(std::string).name() = " << typeid(std::string).name() << "\n";
    std::cout << "typeid(Dog).name()         = " << typeid(Dog).name()         << "\n";
    std::cout << "(Note: .name() is implementation-defined — may be mangled)\n\n";

    // ── 2. typeid on objects — static vs dynamic type ─────────────────
    std::cout << "─── typeid on objects ───\n";
    Dog         dog("Rex", "Labrador");
    Cat         cat("Whiskers", true);
    GoldenRetriever gr("Buddy");
    Huskie h("h1");

    // On object directly: gives exact (dynamic) type
    std::cout << "dog type: " << typeid(dog).name() << "\n";
    std::cout << "cat type: " << typeid(cat).name() << "\n";
    std::cout << "gr  type: " << typeid(gr).name()  << "\n\n";

    // ── 3. typeid through base-class pointer ──────────────────────────
    std::cout << "─── typeid through base-class pointer ───\n";
    Animal* animals[4];
    animals[0] = &dog;
    animals[1] = &cat;
    animals[2] = &gr;
    animals[3] = &h;

    for (int i = 0; i < 4; i++) {
        // typeid(*ptr) on a POLYMORPHIC class → runtime type
        const std::type_info& ti = typeid(*animals[i]);
        std::cout << "animals[" << i << "] runtime type: "
                  << ti.name() << "\n";
    }
    std::cout << "\n";

    // ── 4. Type comparison with == ────────────────────────────────────
    std::cout << "─── Type comparison ───\n";
    for (int i = 0; i < 4; i++) {
        if (typeid(*animals[i]) == typeid(Dog)) {
            std::cout << animals[i]->name << " is a Dog\n";
        } else if (typeid(*animals[i]) == typeid(Cat)) {
            std::cout << animals[i]->name << " is a Cat\n";
        } else if (typeid(*animals[i]) == typeid(GoldenRetriever)) {
            std::cout << animals[i]->name << " is a GoldenRetriever\n";
        }
    }

    // IMPORTANT: typeid checks EXACT type — NOT hierarchy!
    // typeid(gr) == typeid(Dog) is FALSE even though GoldenRetriever IS-A Dog
    std::cout << "\ntypeid(gr) == typeid(Dog): "
              << (typeid(gr) == typeid(Dog) ? "true" : "false")
              << "  ← exact match only!\n";
    std::cout << "\ntypeid(h) == typeid(gr): "
              << (typeid(h) == typeid(gr) ? "true" : "false")
              << "  ← exact match only!\n";
    std::cout << "typeid(gr) == typeid(GoldenRetriever): "
              << (typeid(gr) == typeid(GoldenRetriever) ? "true" : "false") << "\n\n";

    // ── 5. typeid on non-polymorphic class ────────────────────────────
    std::cout << "─── Non-polymorphic class (static type only) ───\n";
    Plain p1(10);
    Plain* pp = &p1;
    // No virtual → typeid gives DECLARED (static) type, not runtime type
    std::cout << "typeid(*pp).name() = " << typeid(*pp).name()
              << "  (static type — pp has no vtable)\n\n";

    // ── 6. typeid on null pointer → throws bad_typeid ─────────────────
    std::cout << "─── typeid on null pointer ───\n";
    Animal* nullPtr = nullptr;
    try {
        const std::type_info& ti = typeid(*nullPtr);  // THROWS!
        std::cout << ti.name() << "\n";
    } catch (const std::bad_typeid& e) {
        std::cout << "Caught bad_typeid: " << e.what() << "\n";
    }

    // ── 7. Practical: type-based dispatch (logging example) ───────────
    std::cout << "\n─── Practical: runtime type logging ───\n";
    auto logAnimal = [](const Animal* a) {
        std::cout << "Animal '" << a->name << "'"
                  << " | type: " << typeid(*a).name()
                  << " | says: " << a->speak() << "\n";
    };

    for (int i = 0; i < 3; i++) logAnimal(animals[i]);

    return 0;
}