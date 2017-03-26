#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE -1
#define BOOL int
#define MAX 100
typedef unsigned long long u_int_64;

void GeneratePrivateKey(u_int_64 *privateKey, int total);
u_int_64 QuickMod(u_int_64 privateKey, u_int_64 g, u_int_64 n);
u_int_64 GenerateKey(int person, int personIndex, u_int_64 *privateKey, u_int_64 g, u_int_64 n);
void GeneratePrime(unsigned int prime[]);
BOOL Miller(unsigned int p);
unsigned int GenerateN(unsigned int prime[]);
unsigned int GenerateG(unsigned int n);

int main(int argc, const char * argv[]) {
    u_int_64 privateKey[MAX], key, midAttKey[MAX], makFormer[MAX], makLatter[MAX];
    unsigned int n, g;
    int total, midAttFlag;
    unsigned int prime[1229];
    
    srand((unsigned)time(NULL) + rand());
    printf("Enter the total number of persons in the group:\n");
    scanf("%d", &total);
    GeneratePrime(prime);
    
    n = (unsigned int)GenerateN(prime);
    printf("Public Key n is %u\n", n);
    g = GenerateG(n);
    printf("Public Key g is %u\n", g);
    
    GeneratePrivateKey(privateKey, total);
    printf("Private Keys for each person are generated\n");
    printf("1 : man_in_the_middle attack mode. 0 : normal mode.\n");
    scanf("%d",&midAttFlag);
    
    if (1 == midAttFlag)
    {
        for (int i = 0; i < total; i++)
        {
            midAttKey[i] = rand();
        }
        for (int i = 0; i < total; i++)
        {
            int j = i;
            for (int k = 0; k < total - 1; k++)
            {
                j = (j + 1) % total;
            }
            makFormer[j] = GenerateKey(total - 2, i, privateKey, g, n);
        }
        printf("Final result of the user + attacker:\n");
        for(int i = 0; i < total; i++)
        {
            u_int_64 finalKey;
            makLatter[i] = QuickMod(privateKey[i], makFormer[i], n);
            makFormer[i] = QuickMod(midAttKey[i], makFormer[i], n);
            midAttKey[i] = QuickMod(midAttKey[i], makLatter[i], n);
            finalKey = QuickMod(privateKey[i], makFormer[i], n);
            printf("%llu + %llu\n", finalKey, midAttKey[i]);
        }
    }
    else
    {
        printf("The Keys each person finally gets are as follows\n");
        for (int i = 0; i < total; i++)
        {
            key = GenerateKey(total, i, privateKey, g, n);
            printf("%llu ", key);
        }
        putchar('\n');
    }
    printf("The Private Keys for each person are as follows\n");
    for (int i = 0; i < total; i++)
    {
        printf("%llu ", privateKey[i]);
    }
    return 0;
}

void GeneratePrivateKey(u_int_64 privateKey[], int total)
{
    //privateKey = (u_int_64*)malloc(total * sizeof(u_int_64));
    
    for (int i = 0; i < total; i++)
    {
        privateKey[i] = rand() + 1;
    }
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
    int count = total;
    for (int i = (personIndex + 1) % total; count != 0; i = (i + 1) % total)
    {
        key = QuickMod(privateKey[i], key, n);
        count--;
    }
    return key;
}


void GeneratePrime(unsigned int prime[])
{
    int i = 0;
    unsigned int a, b;
    for (a = 2; a <= 10000; a++)
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

BOOL Miller(unsigned int p)
{
    unsigned int n = p - 1;
    unsigned int s = 0, d, a;
    int i;
    int r;
    while (0 == (n & 0x01))
    {
        n >>= 1;
        s++;
    }
    d = n;
    for (i = 0; i < 5; i++)
    {
        a = rand() % n + 1;
        if (1 == QuickMod(d, a, p))
        {
            continue;
        }
        for (r = 0; r < s; r++)
        {
            if (QuickMod(pow(2, r) * d, a, p) == n)
            {
                break;
            }
        }
        if (r >= s)
        {
            break;
        }
    }
    if (5 == i)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

unsigned int GenerateN(unsigned int prime[])
{
    int i;
    unsigned int p;
    while (1)
    {
        p = rand() % (0x7fffffff) + 0x80000000;
        if (0 == (p & 0x01))
        {
            p++;
        }
        for (i = 0; i < 1229; i++)
        {
            if (0 == p % prime[i])
            {
                break;
            }
        }
        if (1229 == i)
        {
            break;
        }
    }
    while (1)
    {
        if (TRUE == Miller(p) && TRUE == Miller((p - 1) / 2))
        {
            return p;
        }
        else
        {
            p += 2;
        }
    }
}

unsigned int GenerateG(unsigned int n)
{
    int g;
    do{
        g = rand() % (n - 2) + 2;
    } while(g <= 1);
    return g;
}
