#include <iostream>
#include <vector>

using namespace std;
//自己写的非递归解法，用于解决RSA算法中求解私钥的问题
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
//维基百科上的递归解法，用于验证程序的正确性
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
//测试程序
int main(){
    int x, y;
    gcdEx(79, 3220, &x, &y);
    cout << extEuclidean(47, 71, 79) << " " << x << endl;
    gcdEx(101, 2760, &x, &y);
    cout << extEuclidean(31, 93, 101) << " " << x << endl;
    gcdEx(101, 4, &x, &y);
    cout << extEuclidean(2, 5, 101) << " " << x << endl;
    gcdEx(193, 40600, &x, &y);
    cout << extEuclidean(101, 407, 193) << " " << x << endl;
}
