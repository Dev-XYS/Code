// Problem Name: Median on Segments (General Case Edition)
// Source: Codeforces Round #496 (Div. 3), Problem E2

#include <cstdio>

typedef long long ll;

using namespace std;

class array
{
private:
	int data[400010];
public:
	int& operator [] (int index) { return data[index + 200005]; }
}cnt, lazy;

int n, m, a[200010];

void init()
{
	for (int i = -n; i <= n; i++)
	{
		cnt[i] = 0;
		lazy[i] = 0;
	}
	lazy[0] = 1;
}

ll solve(int v)
{
	init();
	ll res = 0;
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] >= v)
		{
			cnt[sum] += lazy[sum];
			lazy[sum + 1] += lazy[sum] + 1;
			lazy[sum++] = 0;
		}
		else
		{
			lazy[--sum]++;
		}
		res += cnt[sum - 1];
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	printf("%I64d\n", solve(m) - solve(m + 1));
	return 0;
}
