// Problem Name: Big Number
// Source: Dhaka 2002

#include <cstdio>
#include <cmath>

using namespace std;

int _log10_[10000010];

int main()
{
	int T;
	scanf("%d", &T);
	double cur = 0;
	for (int i = 1; i <= 10000000; i++)
	{
		cur += log10(i);
		_log10_[i] = cur;
	}
	while (T--)
	{
		int n;
		scanf("%d", &n);
		printf("%d\n", _log10_[n] + 1);
	}
	return 0;
}
