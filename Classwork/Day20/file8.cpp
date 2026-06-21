#include <stdio.h>

class Shape {
public:
    // virtual: enables polymorphism (runtime dispatch)
    // = 0: makes this a PURE VIRTUAL function (abstract)
    //      Shape cannot be instantiated directly
    virtual float area() = 0;
    virtual void  print() = 0;

    // Non-virtual: shared behavior (not overridable)
    void describe() {
        printf("I am a shape. My area is %.2f\n", area());
    }
};

class Circle : public Shape {
    float radius;
public:
    Circle(float r) : radius(r) {}

    float area() override {
        return 3.14159f * radius * radius;
    }

    void print() override {
        printf("Circle (radius=%.1f) area=%.2f\n", radius, area());
    }
};

class Rectangle : public Shape {
    float width, height;
public:
    Rectangle(float w, float h) : width(w), height(h) {}

    float area() override {
        return width * height;
    }

    void print() override {
        printf("Rectangle (%.1f x %.1f) area=%.2f\n", width, height, area());
    }
};

class Triangle : public Shape {
    float base, height;
public:
    Triangle(float b, float h) : base(b), height(h) {}

    float area() override { return 0.5f * base * height; }

    void print() override {
        printf("Triangle (base=%.1f, h=%.1f) area=%.2f\n",
               base, height, area());
    }
};

int main() {
    // Polymorphism: array of Shape pointers, each holding a different type
    Shape* shapes[3];
    shapes[0] = new Circle(5.0f);
    shapes[1] = new Rectangle(4.0f, 6.0f);
    shapes[2] = new Triangle(3.0f, 8.0f);

    printf("=== Polymorphism Demo ===\n\n");

    for (int i = 0; i < 3; i++) {
        shapes[i]->print();     // Different behavior, same call
        shapes[i]->describe();  // Calls area() polymorphically too
        printf("\n");
    }

    // Find total area — works for ANY shape!
    float total = 0;
    for (int i = 0; i < 3; i++)
        total += shapes[i]->area();
    printf("Total area: %.2f\n", total);

    // Cleanup
    for (int i = 0; i < 3; i++) delete shapes[i];

    return 0;
}