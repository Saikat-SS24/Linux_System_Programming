/*

without iterator
- algo must know container internal
for(int i=-;i<vec.size();i++)
    process(vec[i])

by using iterators
- one algo works for any container
for(auto it = c.begin();it!=c.end();it++);

operations:
*it -> dereferencing of it value
++it -> advances to the next elem
it++ -> advance, return the old position
--it
it+n -> advaning by n steps (random access)
it1 == it2 => are both iterators at same pos



*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


using namespace std;

int main()
{
    vector<int> v1 = {10,20,30,40,50};

    vector<int>::iterator it;

    for(it = v1.begin();it!=v1.end();it++)
        cout<<*it<<endl;

    return 0;
}