#include<iostream>
#include<cstdlib>
using namespace std;
int ReverseGCD(int a, int b,int& t)
{
    int n,i;
    n = min(a,b);
    for(i = n;i >= 1;i--)
    {
        t++;
        if(a % i == 0 && b % i == 0)
            return i;
    }
	return 1;
}
                                                                
int FilterGCD(int a, int b, int &t)
{
    int i, minimum = min(a, b);
    for(i = 2; i <= minimum; i++)
    {
        t++;
        if(a % i == 0 && b % i == 0)
            return i * FilterGCD(a / i, b / i, t);
    }
    return 1;
}

int FilterfasterGCD(int a, int b, int s, int &t)
{
    int i, minimum = min(a, b);
    for(i = s; i <= minimum; i++)
    {
        t++;
        if(a % i == 0 && b % i == 0)
            return i * FilterfasterGCD(a / i, b / i, i, t);
    }
    return 1;
}

int BinaryGCD(int a, int b,int& t)
{
    int m,n,ans = 1,temp;
    n = min(a, b);
    m = max(a, b);       
    while(n != 0 && m != 0)
    {
        t++;
        if(n % 2 == 0 && m % 2 == 0)
        {
            ans *= 2;
            n /= 2;
            m /= 2;
        }
        else if (n % 2 == 0)
            n /= 2;
        else if (m % 2 == 0) 
            m /= 2;
        if(n > m)
        { 
            temp = n; 
            n = m;
            m = temp;
        }                                                                                       
        m = m - n;  
    }                            
    return n * ans;
}

int EuclidGCD(int a, int b,int &t)
{
    int m, n, temp;
    n = min(a, b);
    m = max(a, b);
    while(m % n != 0)
    {
        t++;
        temp = n;
        n = m % n;
        m = temp;
    }
    return n;
}

int main()
{
    int a, b, t1, t2, t3, t4, t5;
    while(cin>>a)
    {
        if(a == 0)
            return 0;
        cin>>b;
        t1 = 0;
        t2 = 0;
        t3 = 0;
        t4 = 0;
        t5 = 0;
        cout<<"Case ("<<a<<", "<<b<<"): GCD-By-Reverse-Search = "<<ReverseGCD(a, b, t1);
        cout<<", taking "<<t1<<" iterations"<<endl;
        cout<<"Case ("<<a<<", "<<b<<"): GCD-By-Filter = "<<FilterGCD(a, b, t2);
        cout<<", taking "<<t2<<" iterations"<<endl;
        cout<<"Case ("<<a<<", "<<b<<"): GCD-By-Filter-Faster = "<<FilterfasterGCD(a, b, 2, t3);
        cout<<", taking "<<t3<<" iterations"<<endl;
        cout<<"Case ("<<a<<", "<<b<<"): GCD-By-Binary = "<<BinaryGCD(a, b, t4);
        cout<<", taking "<<t4<<" iterations"<<endl;
        cout<<"Case ("<<a<<", "<<b<<"): GCD-By-Euclid = "<<EuclidGCD(a, b, t5);
        cout<<", taking "<<t5<<" iterations"<<endl;
    }
}

