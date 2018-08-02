#include <cstdio>

using namespace std;

int main()
{
	int n, m, a;
	scanf("%d%d%d", &n, &m, &a);
	printf("%I64d", (long long)(n % a == 0 ? n / a : n / a + 1) * (long long)(m % a == 0 ? m / a : m / a + 1));
	return 0;
}
