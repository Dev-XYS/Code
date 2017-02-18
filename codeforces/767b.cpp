#include <cstdio>

#define INF 10000000000000000LL

typedef long long ll;

using namespace std;

ll b, e, t, s[100010];
int n;

int main()
{
	scanf("%I64d%I64d%I64d%d", &b, &e, &t, &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%I64d", &s[i]);
	}
	if (s[n - 1] < e - t + 1)
	{
		s[n++] = e - t + 1;
	}
	ll right = b, pos, time = INF;
	for (int i = 0; i < n && right <= e - t; )
	{
		if (s[i] > right)
		{
			printf("%I64d", right);
			return 0;
		}
		if (right - (s[i] - 1) < time)
		{
			pos = s[i] - 1;
			time = right - (s[i] - 1);
		}
		int k = i;
		while (s[i] == s[k] && i < n)
		{
			right += t;
			i++;
		}
	}
	printf("%I64d", pos);
	return 0;
}
