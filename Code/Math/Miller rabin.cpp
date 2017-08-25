Miller-Rabin Prime test
-----------------------------------------------------------------------------------------

#include random
#include time

Bool isPrime(int n, int k)
{
	if(n <= 3)
	{
		Return (n==2 or n==3);
	}
	if(n % 2 == 0) return false;

	Int temp = n-1;
Int r = 1;
	while(temp % 2 == 0)
	{
		Temp /= 2;
		r++;
	}
	Int d = (n-1) / (1 << r);

	for(int i =- 0; i < k; i++)
	{
		if(!millerTest(n, d))
		{
			Return false;
		}
	}
	Return true;
}

Bool millerTest(int n, int d)
{
	Int a = (rand()%(n-1)) + 1;
	Int x = pow(a, d) % n;
	if(x == 1 or x == n-1) return true;
	while(x != n-1)
	{
		X = (x*x) % n;
		if(x == 1) return false;
if(x == n-1) return true;
	}
	
}

