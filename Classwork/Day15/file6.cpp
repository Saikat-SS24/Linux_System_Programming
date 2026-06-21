#include <iostream>
using namespace std;


enum DAYS_WEEK
{
    MONDAY=1,
    TUESDAY,
    WEDNSDAY=101,
    THRUSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

enum status
{
    SUCCESS=0,
    FAILED=-1

};


int func()
{
    cout<<"\nfrom the function"<<endl;
    return FAILED;
}
int main()
{
    enum DAYS_WEEK day1=TUESDAY;
    cout<<"day1: "<<day1<<endl;
    enum DAYS_WEEK day2=FRIDAY;
    cout<<"day2: "<<day2<<endl;

    cout<<func()<<endl;
    return 0;

}