// Problem Name: 不重复数字
// Source: [JLOI2011]

#include <cstdio>
#include <set>

using namespace std;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n, x;
		set<int> S;
		scanf("%d%d", &n, &x);
		S.insert(x);
		printf("%d", x);
		for (int i = 1; i < n; i++)
		{
			scanf("%d", &x);
			if (S.count(x) == 0) printf(" %d", x), S.insert(x);
		}
		printf("\n");
	}
	return 0;
}
