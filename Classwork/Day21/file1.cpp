#include <iostream>

using namespace std;

class Engine{
private:
    string e_type; // desiel / petrol /electric
public:
    Engine(){
        cout<<"\nDef Cnstr of Engine"<<endl;
        e_type = "Petrol";}
    Engine(string et): e_type(et) {
        cout<<"\nPara Cnstr of Engine"<<endl;
    }
    ~Engine() {
        cout<<"\nDestr of Engine"<<endl;
    }
    void printEngine(){ cout<<"Engine Type: "<<e_type<<endl;}
};

class Car: public Engine{
private:
    string brand;
public:
    Car() { 
        cout<<"\nDef Cnstr of Car"<<endl;
        brand = "Unknown"; }
    Car(string b, string et): Engine(et), brand(b){
        cout<<"\nPara Cnstr of Car"<<endl;
    }
    ~Car(){
        cout<<"\nDestr of Car"<<endl;
    }

    void printCar() { 
        
        cout<<"Brand: "<<brand<<endl;
        printEngine(); 
    }
};


class Bike
{
private:
    string brand;
    Engine *e;
public:
    Bike() { 
        cout<<"\nDef Cnstr of Bike"<<endl;
        brand = "Unknown";
        e = new Engine("Electric");
    }
    Bike(string b, string et){
      cout<<"\nPara Cnstr of Bike"<<endl;
      e = new Engine(et);
      brand = b;  
    }
    ~Bike()
    {
        delete e;
        cout<<"\nDestr of Bike"<<endl;
    }

    void printBike() { 
        
        cout<<"Brand: "<<brand<<endl;
        e->printEngine(); 
    }

};


class ElectricCycle{
private:
    string brand;
    Engine *e;
public:
    ElectricCycle(){
        cout<<"\nDef Cnstr of Electric Cycle"<<endl;
        brand = "Unknown";
        e = nullptr;
    }
    ElectricCycle(string b, Engine &obj)
    {
        cout<<"\nPara Cnstr of Electric Cycle"<<endl;
        brand = b;
        e = &obj;
    }

    ~ElectricCycle(){
        cout<<"\nDestr of Electric Cycle"<<endl;
    }

    void printElectricCycle()
    {
        cout<<"Brand: "<<brand<<endl;
        e->printEngine();
    }
};


int main()
{
    // cout<<"\n======================="<<endl;
    // Car obj("Tata", "Petrol");
    // obj.printCar();

    // cout<<"\n======================="<<endl;
    // Bike b("Ola", "ELECTRIC");
    // b.printBike();
    // cout<<"\n======================="<<endl;


    cout<<"\n======================="<<endl;
    Engine e("Maruti");
    ElectricCycle ec("Dragon", e);
    ec.printElectricCycle();
    cout<<"\n======================="<<endl;

    cout<<"\n======================="<<endl;
    //Engine e("Maruti");
    ElectricCycle ec1("Hyrculus", e);
    ec1.printElectricCycle();
    cout<<"\n======================="<<endl;


    return 0;
}

