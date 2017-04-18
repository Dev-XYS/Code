// Problem Name: Odd sum
// Source: Educational Codeforces Round 19

#include <iostream>

#define INF 1000000000

typedef long long ll;

using namespace std;

int n;

int main()
{
	cin >> n;
	int poddc = 0, minpodd = INF, maxnodd = -INF, x;
	ll podds = 0, ans = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		if ((x & 1) == 0)
		{
			if (x > 0) ans += x;
		}
		else
		{
			if (x > 0)
			{
				poddc++;
				podds += x;
				if (x < minpodd) minpodd = x;
			}
			else
			{
				if (x > maxnodd) maxnodd = x;
			}
		}
	}
	if ((poddc & 1) == 1) ans += podds;
	else
	{
		if (minpodd == INF) ans += maxnodd;
		else
		{
			ans += podds - minpodd;
			if (maxnodd != -INF && maxnodd + minpodd > 0) ans += maxnodd + minpodd;
		}
	}
	cout << ans << endl;
	return 0;
}
