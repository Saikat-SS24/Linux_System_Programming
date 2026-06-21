/*

cmd line args

*/

#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
	/*
	./app 10 20
	*/
	int v1,v2;
	int res=0;
	char op;

	if(argc != 4)
		exit(1);
	v1 = atoi(argv[1]);
	v2 = atoi(argv[2]);
	op = argv[3][0];

	switch(op)
	{
		case '+':
			res = v1+ v2;
			cout<<"\nresult = "<<res<<endl;
			break;

		case '-':
			res = v1- v2;
			cout<<"\nresult = "<<res<<endl;
			break;

		case '*':
			res = v1* v2;
			cout<<"\nresult = "<<res<<endl;
			break;
		
		default:
			cout<<"\nenter the correct operator"<<endl;
	}
    return 0;
}
