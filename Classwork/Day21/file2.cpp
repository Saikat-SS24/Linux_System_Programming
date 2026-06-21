/*
Static members and static method

*/
#include <iostream>
#define InitValue 1000

using namespace std;

class Bank
{
    private:
        int accountNo;
        string name;
        static int noOfAccount;
    public:
        Bank(){
            noOfAccount++;
            accountNo = noOfAccount;
        }

    void setAccount(string n) {name = n;}
    void displayAccount(){ 
        cout<<"\nAccount Details\n";
        cout<<"\nName: "<<name<<endl;
        cout<<"\nAccount Number: "<<accountNo<<endl;
    }
    static int getNoOfAccounts(){
        return noOfAccount;
    }
};

int Bank::noOfAccount = InitValue;

int main()
{
    Bank c1,c2,c3;
    c1.setAccount("abc1");
    c2.setAccount("abc2");
    c3.setAccount("abc3");

    c1.displayAccount();
    c2.displayAccount();
    c3.displayAccount();

    cout<<"No of Bank Account Objects: "<<(Bank::getNoOfAccounts()-InitValue)<<endl;

    return 0;
       
}
