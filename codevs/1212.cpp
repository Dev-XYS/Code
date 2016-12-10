#include <cstdio>

using namespace std;

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d", gcd(a, b));
	return 0;
}
