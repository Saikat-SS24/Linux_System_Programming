#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    vector<int> v1;
    cout<<"Size \t Cap"<<endl;
    cout<<v1.size()<<"\t"<<v1.capacity()<<endl;
    v1.push_back(10);
    cout<<v1.size()<<"\t"<<v1.capacity()<<endl;
    v1.push_back(20);
    cout<<v1.size()<<"\t"<<v1.capacity()<<endl;
    v1.push_back(30);
    cout<<v1.size()<<"\t"<<v1.capacity()<<endl;
    v1.push_back(40);
    cout<<v1.size()<<"\t"<<v1.capacity()<<endl;
    v1.push_back(50);
    cout<<v1.size()<<"\t"<<v1.capacity()<<endl;
    
    for(int i : v1)
        cout<<i<<endl;

    vector<int> v2(10);
    cout<<v2.size()<<"\t"<<v2.capacity()<<endl;

    for (int i=101,count=0;i<=110;i++,count++)
        v2[count] = i;

    for(int i : v2)
        cout<<i<<endl;

    v2.push_back(10);
    cout<<v2.size()<<"\t"<<v2.capacity()<<endl;

    for(int i : v2)
        cout<<i<<endl;


    vector <int>v3(1);

    v3[0] = 201;
    //v3[1] = 202;
    v3.push_back(202);
    cout<<v3.size()<<"\t"<<v3.capacity()<<endl;

    for(int i : v3)
        cout<<i<<endl;

    
    
    sort(v2.rbegin(),v2.rend());

    for(auto e: v2)
        cout<<e<<endl;

    sort(v2.begin(),v2.end(),less<int>());

    for(auto e: v2)
        cout<<e<<endl;


    return 0;

}
