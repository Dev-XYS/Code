// Problem Name: Factorial
// Source: ACM Central European Programming Contest, Prague 2000

#include <cstdio>

using namespace std;

int pow5[] = { 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125, 9765625, 48828125, 244140625, 1220703125 };

int main()
{
	int q;
	scanf("%d", &q);
	while (q--)
	{
		int x;
		scanf("%d", &x);
		int ans = 0;
		for (int i = 0; pow5[i] <= x; i++)
		{
			ans += x / pow5[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
