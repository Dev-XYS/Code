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

vector<complex> dft(vector<complex> a)
{
	if (a.size() == 1) return a;
	vector<complex> a0, a1, res;
	for (int i = 0; i < a.size(); i += 2)
	{
		a0.push_back(a[i]);
		a1.push_back(a[i + 1]);
	}
	vector<complex> b0 = dft(a0);
	vector<complex> b1 = dft(a1);
	complex w0 = complex(cos(PI * 2.0f / (double)a.size()), sin(PI * 2.0f / (double)a.size()));
	complex w = complex(1.0f, 0);
	res.resize(a.size());
	for (int i = 0; i < (a.size() >> 1); i++)
	{
		res[i] = b0[i] + b1[i] * w;
		res[i + (a.size() >> 1)] = b0[i] - b1[i] * w;
		w = w * w0;
	}
	return res;
}

vector<complex> dft_1(vector<complex> a)
{
	int n = a.size();
	if (n == 1) return a;
	vector<complex> a0, a1, res;
	for (int i = 0; i < a.size(); i += 2)
	{
		a0.push_back(a[i]);
		a1.push_back(a[i + 1]);
	}
	vector<complex> b0 = dft_1(a0);
	vector<complex> b1 = dft_1(a1);
	complex w0 = complex(cos(PI * 2.0f / a.size()), -sin(PI * 2.0f / a.size()));
	complex w = complex(1.0f, 0);
	res.resize(a.size());
	for (int i = 0; i < (a.size() >> 1); i++)
	{
		res[i] = (b0[i] + b1[i] * w);
		res[i + (a.size() >> 1)] = (b0[i] - b1[i] * w);
		w = w * w0;
	}
	return res;
}

char sa[100010], sb[100010], s[1000010];

int main()
{
	int n, x;
	vector<complex> a, b;
	scanf("%s%s", sa, sb);
	int la = strlen(sa), lb = strlen(sb);
	int l = la + lb;
	int k = 0;
	while (l > 0)
	{
		k++;
		l >>= 1;
	}
	n = 1 << k;
	a.resize(n);
	b.resize(n);
	for (int i = 0; i < la; i++)
	{
		a[la - i - 1] = complex((double)(sa[i] - '0'), 0);
	}
	for (int i = 0; i < lb; i++)
	{
		b[lb - i - 1] = complex((double)(sb[i] - '0'), 0);
	}
	vector<complex> ra = dft(a), rb = dft(b);
	for (int i = n - 1; i >= 0; i--)
	{
		ra[i] = ra[i] * rb[i];
	}
	vector<complex> res = dft_1(ra);
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		temp += (int)((res[i].re / (double)n) + 0.5f);
		s[i] = temp % 10 + '0';
		temp /= 10;
	}
	int p;
	for (p = n - 1; p >= 0; p--)
	{
		if (s[p] != '0')
		{
			break;
		}
	}
	if (p == -1)
	{
		printf("0");
	}
	for (; p >= 0; p--)
	{
		printf("%c", s[p]);
	}
	return 0;
}
