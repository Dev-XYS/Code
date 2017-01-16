#include <cstdio>

using namespace std;

int n;
double x[15][15], a[15][15], s[15];

inline double abs(double x)
{
	return x < 0 ? -x : x;
}

inline void swap(double *x, double *y)
{
	double temp;
	for (int i = 0; i < 15; i++)
	{
		temp = x[i];
		x[i] = y[i];
		y[i] = temp;
	}
}

void gaussian_elimination()
{
	for (int i = 0; i < n; i++)
	{
		int maxabso = i;
		for (int j = i; j < n; j++)
		{
			if (abs(a[j][i]) > abs(a[maxabso][i]))
			{
				maxabso = j;
			}
		}
		swap(a[i], a[maxabso]);
		for (int j = i + 1; j < n; j++)
		{
			for (int k = n; k >= i; k--)
			{
				a[j][k] -= a[i][k] * (a[j][i] / a[i][i]);
			}
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		double b = a[i][n];
		for (int j = n - 1; j > i; j--)
		{
			b -= a[i][j] * s[j];
		}
		s[i] = b / a[i][i];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%lf", &x[i][j]);
		}
	}
	for (int i = 0; i < n; i++)
	{
		double b = 0.0f;
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 2 * (x[i + 1][j] - x[i][j]);
			b += x[i + 1][j] * x[i + 1][j] - x[i][j] * x[i][j];
		}
		a[i][n] = b;
	}
	gaussian_elimination();
	printf("%.3lf", s[0]);
	for (int i = 1; i < n; i++)
	{
		printf(" %.3lf", s[i]);
	}
	return 0;
}
