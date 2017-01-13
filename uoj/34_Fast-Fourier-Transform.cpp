#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

struct complex
{
	double re, im;
	complex(double _re = 0, double _im = 0) : re(_re), im(_im) { }
};

complex operator + (const complex &x, const complex &y)
{
	return complex(x.re + y.re, x.im + y.im);
}

complex operator - (const complex &x, const complex &y)
{
	return complex(x.re - y.re, x.im - y.im);
}

complex operator * (const complex &x, const complex &y)
{
	return complex(x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re);
}

complex operator / (const complex &x, const int &y)
{
	return complex(x.re / (double)y, x.im / (double)y);
}

const double PI = acos(-1.0);

int n;
complex a[500010], b[500010];

void pre(int l, int r)
{
	if (l < r)
	{
		int mid = (l + r) >> 1;
		static complex dl[500010], dr[500010];
		for (int i = l; i < r; i += 2)
		{
			dl[(i - l) >> 1] = a[i];
			dr[(i - l) >> 1] = a[i + 1];
		}
		memcpy(a + l, dl, (mid - l + 1) * sizeof(a[0]));
		memcpy(a + mid + 1, dr, (r - mid) * sizeof(a[0]));
		for (int i = l; i < r; i += 2)
		{
			dl[(i - l) >> 1] = b[i];
			dr[(i - l) >> 1] = b[i + 1];
		}
		memcpy(b + l, dl, (mid - l + 1) * sizeof(b[0]));
		memcpy(b + mid + 1, dr, (r - mid) * sizeof(b[0]));
		pre(l, mid);
		pre(mid + 1, r);
	}
}

void dft()
{
	for (int i = 2; i <= n; i <<= 1)
	{
		complex w0 = complex(cos(PI * 2 / (double)i), sin(PI * 2 / (double)i));
		for (int j = 0; j < n; j += i)
		{
			int mid = j + (i >> 1);
			complex w = complex(1.0f, 0);
			for (int k = j; k < mid; k++)
			{
				complex temp = a[k];
				a[k] = a[k] + w * a[k + (i >> 1)];
				a[k + (i >> 1)] = temp - w * a[k + (i >> 1)];
				temp = b[k];
				b[k] = b[k] + w * b[k + (i >> 1)];
				b[k + (i >> 1)] = temp - w * b[k + (i >> 1)];
				w = w * w0;
			}
		}
	}
}

void idft()
{
	for (int i = 2; i <= n; i <<= 1)
	{
		complex w0 = complex(cos(PI * 2 / (double)i), -sin(PI * 2 / (double)i));
		for (int j = 0; j < n; j += i)
		{
			int mid = j + (i >> 1);
			complex w = complex(1.0f, 0);
			for (int k = j; k < mid; k++)
			{
				complex temp = a[k];
				a[k] = a[k] + w * a[k + (i >> 1)];
				a[k + (i >> 1)] = temp - w * a[k + (i >> 1)];
				w = w * w0;
			}
		}
	}
}

int main()
{
	int x, la, lb;
	scanf("%d%d", &la, &lb);
	int l = la + lb + 2;
	int k = 0;
	while (l > 0)
	{
		k++;
		l >>= 1;
	}
	n = 1 << k;
	for (int i = 0; i <= la; i++)
	{
		scanf("%d", &x);
		a[i] = complex((double)x, 0.0f);
	}
	for (int i = 0; i <= lb; i++)
	{
		scanf("%d", &x);
		b[i] = complex((double)x, 0.0f);
	}
	pre(0, n - 1);
	dft();//for (int i = 0; i < n; i++) printf("a[%d] = %.2f + %.2fi; b[%d] = %.2f + %.2fi.\n", i, a[i].re, a[i].im, i, b[i].re, b[i].im);
	for (int i = 0; i < n; i++)
	{
		a[i] = a[i] * b[i];
	}
	pre(0, n - 1);
	idft();
	for (int i = 0; i <= la + lb; i++)
	{
		printf("%d ", (int)(a[i].re / (double)n + 0.5f));
	}
	return 0;
}
