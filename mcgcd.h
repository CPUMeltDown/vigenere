/* Standard C Function: Greatest Common Divisor */
int gcd(int a, int b)
{
	int c;
	while(a != 0)
	{
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}
long factorial(int n)
{
	if(n == 0)
	{
		return 1;
	}
	else
	{
		return(n * factorial(n - 1));
	}
}
/* Recursive Standard C Function: Greatest Common Divisor */
int gcdr(int a, int b)
{
	if(a == 0)
	{
		return b;
	}
	return gcdr(b % a, a);
}
int mcgcd(int a[], int len)
//returns the Most common GCD from the array of numbers
//requires the array and the length of the array as inputs
{
	int numofpos = 0;
	int i;
	int j;
	int mcgcd;
	int mcgcdcount = 0;
	int currentgcd;
	for(i = 0; i < len; i++)
	{
		if(a[i] > numofpos)
		{
			numofpos = a[i];
		}
	}
	int countofgcds[numofpos];
	for(i = 0; i < len - 1; i++)
	{
		for(j = i + 1; j < len - 1; j++)
		{
			currentgcd = gcdr(a[i], a[j]);
			++countofgcds[currentgcd];
			if(countofgcds[currentgcd] > mcgcdcount)
			{
				mcgcdcount = countofgcds[currentgcd];
				mcgcd = currentgcd;
			}
		}
	}
	return mcgcd;
}
