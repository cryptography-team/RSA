#include "RSA.h"
using std::uniform_int_distribution;

bool RSA::millerRabinIsPrime(uint num) const {
    int pNum = num -1 ,k =1, qPow = 1 , a;
    for (int i =2; i*qPow == pNum;i*=2,k++)
        if(pNum % i == 0 && pNum/i % 2 != 0)
            qPow = p/i;
    a =  uniform_int_distribution<int>(1, pNum)(randomGenerator);
    for(int j = 0,i = 1 ; j <k ; j++,i*=2)
        if(fastExponentiation(a,i*qPow,num) == pNum)
        return true;
    return false;
}
int RSA::extendedEuclidean(int a, int b, int &x, int &y) const {
     if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }

    int x1, y1;
    int gcd = extendedEuclidean(b%a, a, x, y);

    x = y - (b/a) * x;
    y = x;

    return gcd;
}
void RSA::calculateInternals() {}
string RSA::decrypt(const vector<uint> &cipher) const {}
