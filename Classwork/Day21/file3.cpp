#include <iostream>

using namespace std;

class Box
{
    int volume;
    public:
        Box(int v): volume(v) {}
        int getVolume(){ return volume; }
        friend class PrintBox;
};

class PrintBox
{
    public:
        void SetBox(Box &b)
        {
            b.volume = 10;
        }
        void dispBox(Box &b)
        {
            cout<<b.getVolume()<<endl;
        }
};


int main()
{

    Box b(10);

    PrintBox pb;
    pb.SetBox(b);
    pb.dispBox(b);

    return 0;

}