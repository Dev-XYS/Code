// Problem Name: Raising Modulo Numbers
// Source: CTU Open 1999

#include <cstdio>

using namespace std;

int qpow(int x, int y, int mod)
{
	if (y == 0) return 1;
	int h = qpow(x * x % mod, y >> 1, mod);
	if ((y & 1) == 0) return h;
	else return h * x % mod;
}

int main()
{
	int Z;
	scanf("%d", &Z);
	while (Z--)
	{
		int M, H, ans = 0;
		scanf("%d%d", &M, &H);
		for (int i = 0; i < H; i++)
		{
			int A, B;
			scanf("%d%d", &A, &B);
			ans = (ans + qpow(A % M, B, M)) % M;
		}
		printf("%d\n", ans);
	}
	return 0;
}
