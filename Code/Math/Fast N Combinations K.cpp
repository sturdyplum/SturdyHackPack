/*
 Set the size of the factorial array to be larger than what you would think you need (try 300%)
*/


long long MOD = 1000000007;

long long factorial[100010];

long long Pow(long long n,long long e)
{
    long long ans=1;
    while(e)
    {
        if(e&1)
        {
            e--;
            ans= (ans*n)%MOD;
        }
        else
        {
            e/= 2;
            n= (n* n)%MOD;
        }
    }
    return ans;
}

long long inv(long n,long i)
{
    return (Pow(factorial[i]* factorial[n-i]%MOD,MOD-2))%MOD;
}

long long nCr(long long n,long i)
{
    return (factorial[n]*inv(n,i))%MOD;
}

int main()
{
    factorial[0] =1;
    for(int i = 1; i <= 100000; i++)
    {
        factorial[i] = (factorial[i-1]*i)%1000000007;
    }
}
