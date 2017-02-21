#include <cstdio>

typedef long long ll;

using namespace std;

int n;
ll l, s[50010], dp[50010];
int Q[50010], hp = 0, tp = 0;

inline ll sqr(ll x)
{
	return x * x;
}

inline ll getx(int p)
{
	return (p + s[p]) * 2;
}

inline ll gety(int p)
{
	return dp[p] + sqr(p + s[p]);
}

int main()
{
	scanf("%d%lld", &n, &l);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &s[i]);
		s[i] += s[i - 1];
	}
	dp[1] = sqr(s[1] - l);
	Q[tp++] = 0, Q[tp++] = 1;
	for (int i = 2; i <= n; i++)
	{
		while (tp - hp >= 2 && gety(Q[hp + 1]) - gety(Q[hp]) < (getx(Q[hp + 1]) - getx(Q[hp])) * (i + s[i] - l)) hp++;
		dp[i] = dp[Q[hp]] + sqr(i - Q[hp] - 1 + s[i] - s[Q[hp]] - l);
		while (tp - hp >= 2 && (gety(i) - gety(Q[tp - 1])) * (getx(Q[tp - 1]) - getx(Q[tp - 2])) < (gety(Q[tp - 1]) - gety(Q[tp - 2])) * (getx(i) - getx(Q[tp - 1]))) tp--;
		Q[tp++] = i;
	}
	printf("%lld", dp[n]);
	return 0;
}
