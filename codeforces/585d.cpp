#include <cstdio>
#include <map>

using namespace std;

struct del
{
	int d1, d2;
	del(int _d1 = 0, int _d2 = 0) : d1(_d1), d2(_d2) { }
};

struct sum
{
	int l, m, w, step;
	sum(int _l = 0, int _m = 0, int _w = 0, int _step = 0) : l(_l), m(_m), w(_w), step(_step) { }
	int getsum() { return l + m + w; }
};

int n, al[30], am[30], aw[30];
map<del, sum> M;
sum s1 = sum(0, 0, 0, -1), s2 = sum(0, 0, 0, -1);

bool operator < (del x, del y)
{
	if (x.d1 != y.d1) return x.d1 < y.d1;
	return x.d2 < y.d2;
}

int pow3(int x)
{
	int res = 1;
	for (int i = 0; i < x; i++)
	{
		res *= 3;
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d", &al[i], &am[i], &aw[i]);
	}
	for (int i = pow3(n / 2) - 1; i >= 0; i--)
	{
		int x = i;
		sum s;
		for (int j = 0; j < n / 2; j++)
		{
			if (x % 3 == 0)
			{
				s.m += am[j];
				s.w += aw[j];
			}
			else if (x % 3 == 1)
			{
				s.l += al[j];
				s.w += aw[j];
			}
			else
			{
				s.l += al[j];
				s.m += am[j];
			}
			x /= 3;
		}
		s.step = i;
		del d = del(s.m - s.l, s.w - s.m);
		if (M.count(d) > 0)
		{
			if (s.getsum() > M[d].getsum())
			{
				M[d] = s;
			}
		}
		else
		{
			M[d] = s;
		}
	}
	for (int i = pow3(n - n / 2) - 1; i >= 0; i--)
	{
		int x = i;
		sum s;
		for (int j = n / 2; j < n; j++)
		{
			if (x % 3 == 0)
			{
				s.m += am[j];
				s.w += aw[j];
			}
			else if (x % 3 == 1)
			{
				s.l += al[j];
				s.w += aw[j];
			}
			else
			{
				s.l += al[j];
				s.m += am[j];
			}
			x /= 3;
		}
		s.step = i;
		del d = del(s.l - s.m, s.m - s.w);
		if (M.count(d) > 0)
		{
			if (s1.step == -1)
			{
				s1 = M[d];
				s2 = s;
			}
			else if (M[d].getsum() + s.getsum() > s1.getsum() + s2.getsum())
			{
				s1 = M[d];
				s2 = s;
			}
		}
	}
	if (s1.step == -1)
	{
		printf("Impossible");
	}
	else
	{
		for (int i = 0; i < n / 2; i++)
		{
			if (s1.step % 3 == 0)
			{
				printf("MW\n");
			}
			else if (s1.step % 3 == 1)
			{
				printf("LW\n");
			}
			else
			{
				printf("LM\n");
			}
			s1.step /= 3;
		}
		for (int i = n / 2; i < n; i++)
		{
			if (s2.step % 3 == 0)
			{
				printf("MW\n");
			}
			else if (s2.step % 3 == 1)
			{
				printf("LW\n");
			}
			else
			{
				printf("LM\n");
			}
			s2.step /= 3;
		}
	}
	return 0;
}
