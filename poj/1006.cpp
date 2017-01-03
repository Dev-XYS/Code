#include <cstdio>

using namespace std;

int main()
{
	int a, b, c, d, casen = 0;

	while (true)
	{
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if (a == -1)
		{
			break;
		}
	
		a = a % 23;
		b = b % 28;
		c = c % 33;
	
		for (int i = d + 1; i <= 100000; i++)
		{
			if ((i - a) % 23 == 0 && (i - b) % 28 == 0 && (i - c) % 33 == 0)
			{
				printf("Case %d: the next triple peak occurs in %d days.\n", ++casen, i - d);
				break;
			}
		}
	}
	
	return 0;
}
