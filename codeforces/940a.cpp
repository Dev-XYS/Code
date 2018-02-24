// Problem Name: Points on the line
// Source: Codeforces Round #466 (Div. 2), Problem A

#include <cstdio>
#include <algorithm>

using namespace std;

int n, d, x[110], max_left;

int main()
{
	scanf("%d%d", &n, &d);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x[i]);
	}
	sort(x, x + n);
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (x[j] - x[i] <= d)
			{
				if (j - i + 1 > max_left)
				{
					max_left = j - i + 1;
				}
			}
		}
	}
	printf("%d\n", n - max_left);
	return 0;
}
