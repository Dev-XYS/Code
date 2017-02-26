// Problem Name: [SCOI2009] 生日快乐

#include <cstdio>

using namespace std;

inline double max(double x, double y)
{
	return x > y ? x : y;
}

inline double min(double x, double y)
{
	return x < y ? x : y;
}

double dfs(double x, double y, int c)
{
	if (c == 1)
	{
		return max(x, y) / min(x, y);
	}
	double result = 1e5;
	for (int i = 1; i <= c / 2; i++)
	{
		result = min(result, max(dfs(x / (double)c * (double)i, y, i), dfs(x - x / (double)c * (double)i, y, c - i)));
		result = min(result, max(dfs(x, y / (double)c * (double)i, i), dfs(x, y - y / (double)c * (double)i, c - i)));
	}
	return result;
}

int main()
{
	int x, y, n;
	scanf("%d%d%d", &x, &y, &n);
	printf("%.6lf", dfs(x, y, n));
	return 0;
}
