#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long u_int_64;

u_int_64 QuickMod(u_int_64 privateKey, u_int_64 g, u_int_64 n);
u_int_64 GenerateKey(int person, int personIndex, u_int_64 *privateKey, u_int_64 g, u_int_64 n);

int main(int argc, const char * argv[]) {
    u_int_64 *privateKey, g, n, key;
    int total;
    srand((unsigned)time(NULL));
    scanf("%lld%lld%d", &g, &n, &total);
    privateKey = (u_int_64*)malloc(total * sizeof(u_int_64));
    for (int i = 0; i < total; i++)
    {
        privateKey[i] = rand();
    }
    for (int i = 0; i < total; i++)
    {
        key = GenerateKey(total, i, privateKey, g, n);
        printf("%llu ", key);
    }
    for (int i = 0; i < total; i++)
    {
        printf("%llu ", privateKey[i]);
    }
    return 0;
}

u_int_64 QuickMod(u_int_64 privateKey, u_int_64 g, u_int_64 n)
{
    u_int_64 mod = 1;
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

u_int_64 GenerateKey(int total, int personIndex, u_int_64 *privateKey, u_int_64 g, u_int_64 n)
{
    u_int_64 key = g;
    for (int i = (personIndex + 1) % total; ; i = (i + 1) % total)
    {
        key = QuickMod(privateKey[i], key, n);
        if (i == personIndex)
        {
            break;
        }
    }
    return key;
}
