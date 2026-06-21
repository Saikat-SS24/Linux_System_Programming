/*

function call will create a SF

int fact(n)
{
    if(n<=1)
        return 1;
    
    return n * fact(n-1);
}

int main()
{
    int ret = fact(3)=>SF_01;
    int ret = 6 =>  is getting return value from SF_01;
    cout<<ret<<endl;
}

n=3
SF_01, n=3
if(n<=1) (3<=1) -> F
    return 1;
    
return 3 * fact(3-1)=>SF_02;
return 3 * 2; => 2 is returned value from SF_02
return 6 to the called function i.e main function

SF_02, n=2
if(n<=1) (2<=1) -> F
    return 1;
    
return 2 * fact(2-1)=>SF_03
return 2 * 1 => 1 is returned from SF_03
return 2 to the called function => return to SF_01 with 2 value

SF_03, n=1
if(n<=1) (1<=1) -> T
    return 1; return 1 => return called func => return SF_02
    
return 1 * fact(1-1); => this line is not executed

*/