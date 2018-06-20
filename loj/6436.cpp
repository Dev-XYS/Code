// Problem Name: 神仙的游戏
// Source: [PKUSC2018], Day 2, Problem 2

#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

struct complex
{
	double re, im;
	complex(double _re = 0, double _im = 0) : re(_re), im(_im) { }
	complex operator + (const complex &x) { return complex(re + x.re, im + x.im); }
	complex operator - (const complex &x) { return complex(re - x.re, im - x.im); }
	complex operator * (const complex &x) { return complex(re * x.re - im * x.im, re * x.im + im * x.re); }
};

int n, N, k;
char s[1 << 20];
complex a[1 << 20], b[1 << 20], res_a[1 << 20], res_b[1 << 20];
bool ans[1 << 20];

int log2(int x)
{
	int res = -1;
	while (x > 0)
	{
		res++;
		x >>= 1;
	}
	return res;
}

inline int reverse(int x)
{
	int res = 0;
	for (int i = 0; i <= k; i++)
	{
		if ((x & (1 << i)) != 0)
		{
			res |= (1 << (k - i));
		}
	}
	return res;
}

void init(complex *a, complex *res)
{
	for (int i = 0; i < N; i++)
	{
		res[reverse(i)] = a[i];
	}
}

void dft(complex *a, complex *res, int inv)
{
	init(a, res);
	for (int i = 2; i <= N; i <<= 1)
	{
		complex w0(cos(M_PI * 2 / i), inv * sin(M_PI * 2 / i));
		for (int j = 0; j < N; j += i)
		{
			complex w(1, 0);
			for (int k = j; k < j + (i >> 1); k++)
			{
				complex temp = res[k];
				res[k] = temp + res[k + (i >> 1)] * w;
				res[k + (i >> 1)] = temp - res[k + (i >> 1)] * w;
				w = w * w0;
			}
		}
	}
}

void mul()
{
	dft(a, res_a, 1);
	dft(b, res_b, 1);
	for (int i = 0; i < N; i++)
	{
		res_a[i] = res_a[i] * res_b[i];
	}
	dft(res_a, res_b, -1);
	for (int i = 0; i < n; i++)
	{
		if (res_b[i].re / N >= 0.5)
		{
			ans[i] |= true;
		}
	}
}

int main()
{
	scanf("%s", s);
	n = strlen(s);
	k = log2((n << 1) - 2);
	N = 1 << (k + 1);
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '0') a[i] = complex(1, 0);
		else a[i] = complex(0, 0);
		if (s[i] == '1') b[n - 1 - i] = complex(1, 0);
		else b[n - 1 - i] = complex(0, 0);
	}
	mul();
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '1') a[i] = complex(1, 0);
		else a[i] = complex(0, 0);
		if (s[i] == '0') b[n - 1 - i] = complex(1, 0);
		else b[n - 1 - i] = complex(0, 0);
	}
	mul();
	long long ans = 0;
	for (int i = 1; i < n; i++)
	{
		ans ^= (long long)i * i;
		int l = n - i;
		for (int j = i - 1; j >= 0; j -= l)
		{
			if (::ans[j] == true)
			{
				ans ^= (long long)i * i;
				break;
			}
		}
	}
	printf("%lld\n", ans ^= (long long)n * n);
	return 0;
}
