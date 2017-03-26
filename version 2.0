#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long u_int_64;

u_int_64 QuickMod(u_int_64 privateKey, u_int_64 g, u_int_64 n);
u_int_64 GenerateKey(int person, int personIndex, u_int_64 *privateKey, u_int_64 g, u_int_64 n);

int main(int argc, const char * argv[]) {
    u_int_64 *privateKey, g, n, key, *mid_att_key,*mak_former,*mak_latter;
    int total,mid_att_flag;
    srand((unsigned)time(NULL));
    printf("Enter g,n and total number of people:\n");
    scanf("%lld%lld%d", &g, &n, &total);
    privateKey = (u_int_64*)malloc(total * sizeof(u_int_64));
    for (int i = 0; i < total; i++)
    {
        privateKey[i] = rand();
    }
    printf("1 : man_in_the_middle attack mode. 0 : normal mode.\n");
    scanf("%d",&mid_att_flag);

/*
 * one test result for middle man attack :
 * 10001 23
 */

    if(mid_att_flag==1)
    {
        mid_att_key = (u_int_64*)malloc((total) * sizeof(u_int_64));
        for (int i = 0; i < total; i++)
        {
            mid_att_key[i] = rand();
        }
        mak_former = (u_int_64*)malloc((total) * sizeof(u_int_64));
        mak_latter = (u_int_64*)malloc((total) * sizeof(u_int_64));
        for (int i = 0; i < total; i++)
        {
            int j=i;
            for(int k=0;k<total-1;j=(j+1)%total,k++);
            mak_former[j] = GenerateKey(total-2 , i, privateKey, g, n);
        }
        printf("Final result of the user + attacker:\n");
        for(int i=0;i<total;i++)
        {
            u_int_64 final_key;
            mak_latter[i]=QuickMod(privateKey[i],mak_former[i],n);
            mak_former[i]=QuickMod(mid_att_key[i],mak_former[i],n);
            mid_att_key[i]=QuickMod(mid_att_key[i],mak_latter[i],n);
            final_key=QuickMod(privateKey[i],mak_former[i],n);
            printf("%llu + %llu\n",final_key,mid_att_key[i]);
        }

        printf("The random private key of each person:\n");
        for (int i = 0; i < total; i++)
        {
            printf("%llu \n", privateKey[i]);
        }
        return 0;
    }
    else
    {
        printf("The shared common key of each person at last:\n");
        for (int i = 0; i < total; i++)
        {
            key = GenerateKey(total, i, privateKey, g, n);
            printf("%llu \n", key);
        }
        printf("The random private key of each person:\n");
        for (int i = 0; i < total; i++)
        {
            printf("%llu \n", privateKey[i]);
        }
        return 0;
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
    int cnt = total;
    for (int i = (personIndex + 1) % total; cnt!=0; i = (i + 1) % total)
    {
        key = QuickMod(privateKey[i], key, n);
        cnt--;
    }
    return key;
}
