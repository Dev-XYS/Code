// Problem Name: Maximize!
// Source: Codeforces Round #464 (Div. 2), Problem E

#include <cstdio>

using namespace std;

int Q, s[500010], sc = -1, p;
long long sum;
double ans;

int main()
{
	scanf("%d", &Q);
	int op, x;
	while (Q--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d", &x);
			s[++sc] = x;
		}
		else
		{
			ans = s[sc] - (double)(sum + s[sc]) / (p + 1);
			while (p < sc)
			{
				double newans = s[sc] - (double)(sum + s[p] + s[sc]) / (p + 2);
				if (newans > ans)
				{
					sum += s[p++];
					ans = newans;
				}
				else
				{
					break;
				}
			}
			printf("%.10lf\n", ans);
		}
	}
	return 0;
}
