#include <iostream> 
#include <cstdio>
#include <cstdlib>
#include <cmath> 
#include <ctime>
#include <vector>

using namespace std;

int extEuclidean(int p, int q, int e);
int QuickMod(int privateKey, int g, int n);
void GeneratePrime(int prime[]);
bool fun(int x, int y);
/*
int gcdEx(int a, int b, int *x, int *y){
    if(b == 0){
        *x = 1, *y = 0;
        return a;
    }
    else{
        int r = gcdEx(b, a%b, x, y);
        int t = *x;
        *x = *y;
        *y = t - a/b * *y;
        return r;
    }
}
*/
int main()
{
	int prime[25];
	int p, q, e, d;
	srand((time(NULL) + rand()));
    GeneratePrime(prime);
    while(1){
        p = prime[rand() % 24 + 1];
        do{
            q = prime[rand() % 24 + 1];
        }while(p == q);
        int t = (q - 1) * (p - 1);
	    do{
		    e = rand() % 0x000000ff;
		    if(0 == e % 2){
                e++;
            } 
	    }while(fun(e, t) == false);//(fun(e,p-1)==false||fun(e,q-1)==false);
        cout << "p = " << p << " q = " << q << " e = " << e << endl;
	    d = extEuclidean(p, q, e);
        if(d > 0){
            break;
        }
    }
    //int x, y;
    //gcdEx(e, t, &x, &y);
    cout << "d = " << d << endl;
    int val;
    cout << "Enter a number: " << endl;
    cin >> val;
    int c = QuickMod(e, val, p * q);
    cout << c << endl;
    cout << QuickMod(d, c, p * q) << endl;
}

int extEuclidean(int p, int q, int e){
    int t = (p - 1) * (q - 1);
    int flag = 1;
    vector<int> eList;
    vector<int> tList;
    eList.push_back(e);
    tList.push_back(t);
    while(1 != e && 1 != t){
        if(1 == flag){
            t %= e;
            flag = 0;
        }
        else{
            e %= t;
            flag = 1;
        }
        eList.push_back(e);
        tList.push_back(t);
    }
    int k, d;
    if(1 == e){
        d = 1;
        flag = 1;
    }
    else{
        k = -1;
        flag = 0;
    }
    eList.pop_back();
    tList.pop_back();
    while(!eList.empty()){
        e = eList.back();
        eList.pop_back();
        t = tList.back();
        tList.pop_back();
        if(0 == flag){
            d = (1 + t * k) / e;
            flag = 1;
        }
        else{
            k = (d * e - 1) / t;
            flag = 0;
        }
    }
    return d;
}

bool fun(int x, int y)
{
	int t;
	while(y)
	{
		t = x;
		x = y;
		y = t % y;
	}
	if(x==1)
		return true;
	else
		return false;
}

void GeneratePrime(int prime[])
{
    int i = 0;
    int a, b;
    for (a = 2; a <= 100; a++)
    {
        if (2 != a && 0 == (a & 0x01))
        {
            continue;
        }
        for (b = 2; b <= sqrt(a); b++)
        {
            if (a % b == 0)
            {
                break;
            }
        }
        if (b > sqrt(a))
        {
            prime[i++] = a;
        }
    }
}

int QuickMod(int privateKey, int g, int n)
{
    int mod = 1;
    while (privateKey)
    {
        if (privateKey & 0x01)
        {
            mod = (mod * g) % n;
        }
        g = (g * g) % n;
        privateKey >>= 1;
    }
    return mod;
}
