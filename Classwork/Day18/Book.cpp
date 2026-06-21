/* Write a class for a book without driver code
*/

#include<iostream>
#include<string>
using namespace std;

class Book
{
    private:
        string tittle;
        string author;
        double price;
        int pages;
    
    public:
        // constructor to initialize the book
        Book(string t, string a, double p, int pg)
        {
            tittle = t;
            author = a;
            price = p;
            pages = pg;
        }

        void displayDetails()
        {
            cout << "Tittle: " << tittle << endl;
            cout << "Author: " << author << endl;
            cout << "Price: " << price << endl;
            cout << "Pages: " << pages << endl;
            cout << "---------------------- " << endl;
        }

        double getPrice()
        {
            return price;
        }
        void setPrice(double newPrice)
        {
            if (newPrice > 0)
            {
                price = newPrice;
            }
        }
};